# include "definitions_and_headers.h"

/*
 * This function implements the differential equation given by the
 * Oregonator, returning the values of [X]', [Y]' and [Z]'.
 */
void differential ( double A, double B, double P, double X, double Y,
		double Z, double k1, double k2, double k3, double k4,
		double k5, double f, double *dXdt, double *dYdt, double *dZdt) {

	/*double alpha = 6.666667;
	double beta = 13.33333;
	double gamma = 1;
	double delta = 1;
	*dXdt = alpha*X - beta*X*Y;
	*dYdt = delta*X*Y - gamma*Y;*/
	*dXdt = k1*A*Y - k2*X*Y + k3*A*X - 2*k4*X*X;
	*dYdt = -k1*A*Y - k2*X*Y + 0.5*f*k5*B*Z;
	*dZdt = 2*k3*A*X - k5*B*Z;

}

/*
 * This function updates the values of [X], [Y] and [Z] in a cell, using
 * Runge-Kutta-Gill's method (RKG), accounting only the contribution of
 * the reaction, and not the changes in concentration due to diffusion
 * phenomena.
 */
void reaction_contrib ( double *conc_X_new, double *conc_Y_new, double *conc_Z_new,
				info data, cell past_cell ) {

	double A, B, P, X, Y, Z;
	double h, k1, k2, k3, k4, k5, f;
	double s1X, s2X, s3X, s4X;
	double s1Y, s2Y, s3Y, s4Y;
	double s1Z, s2Z, s3Z, s4Z;

	h = data.h;
	k1 = data.k_1;
	k2 = data.k_2;
	k3 = data.k_3;
	k4 = data.k_4;
	k5 = data.k_5;
	f = data.efficiency;

	A = past_cell.conc_A;
	B = past_cell.conc_B;
	P = past_cell.conc_P;
	X = past_cell.conc_X;
	Y = past_cell.conc_Y;
	Z = past_cell.conc_Z;


	/* Runge-Kutta-Gil implementation */
	differential ( A, B, P, X, Y, Z, k1, k2, k3, k4, k5, f, &s1X, &s1Y, &s1Z);
	s1X *= h;
	s1Y *= h;
	s1Z *= h;
	differential ( A, B, P, X + 0.5*s1X, Y + 0.5*s1Y, Z + 0.5*s1Z,
			k1, k2, k3, k4, k5, f, &s2X, &s2Y, &s2Z);
	s2X *= h;
	s2Y *= h;
	s2Z *= h;
	differential ( A, B, P, X + RKG_A*s1X + RKG_B*s2X, Y + RKG_A*s1Y + RKG_B*s2Y,
			Z + RKG_A*s1Z + RKG_B*s2Z, k1, k2, k3, k4, k5, f,
			&s3X, &s3Y, &s3Z);
	s3X *= h;
	s3Y *= h;
	s3Z *= h;
	differential ( A, B, P, X + RKG_C*s2X + RKG_D*s3X, Y + RKG_C*s2Y + RKG_D*s3Y,
			Z + RKG_C*s2Z + RKG_D*s3Z, k1, k2, k3, k4, k5, f,
			&s4X, &s4Y, &s4Z);
	s4X *= h;
	s4Y *= h;
	s4Z *= h;

	/* now we adopt the value at t = t'+h */
	*conc_X_new = X + (s1X + s4X)/6 + (RKG_B*s2X + RKG_D*s3X)/3;
	*conc_Y_new = Y + (s1Y + s4Y)/6 + (RKG_B*s2Y + RKG_D*s3Y)/3;
	*conc_Z_new = Z + (s1Z + s4Z)/6 + (RKG_B*s2Z + RKG_D*s3Z)/3;

}

/*
 * This function returns the laplacian of some function, using a finite
 * difference method.
 */
double laplacian ( double fxiyi, double fxipyi, double fximyi,
				double fxiyip, double fxiyim,
				double fxipyip, double fxipyim,
				double fximyip, double fximyim, double delta ) {

	double gamma, laplacian;

	gamma = 0.13;

	laplacian = ( 1 - gamma ) * ( ( fxipyi + fximyi + fxiyip + fxiyim )
			- 4*fxiyi ) / ( delta * delta );
	laplacian += gamma * ( 0.5 * ( fxipyip + fximyip + fxipyim + fximyim )
			- 2*fxiyi ) / ( delta * delta );

	return laplacian;

}

/*
 * This function updates the values of the of [X], [Y], and [Z] in a cell due
 * to Fick's 2nd Law, without consideration for the chemical reactions.
 */
void diffusion_contrib ( double *conc_X_new, double *conc_Y_new, double *conc_Z_new,
					info data,
					cell past_cell,
					cell north_past_cell,
					cell east_past_cell,
					cell south_past_cell,
					cell west_past_cell,
					cell ne_past_cell,
					cell nw_past_cell,
					cell se_past_cell,
					cell sw_past_cell ) {

	double delta, h;
	double Xxiyi, Xxipyi, Xximyi, Xxiyip, Xxiyim;
	double Xxipyip, Xxipyim, Xximyip, Xximyim;
	double Yxiyi, Yxipyi, Yximyi, Yxiyip, Yxiyim;
	double Yxipyip, Yxipyim, Yximyip, Yximyim;
	double Zxiyi, Zxipyi, Zximyi, Zxiyip, Zxiyim;
	double Zxipyip, Zxipyim, Zximyip, Zximyim;
	double dXdt, dYdt, dZdt;

	delta = data.delta;
	h = data.h;

	Xxiyi = past_cell.conc_X;
	Xxipyi = east_past_cell.conc_X;
	Xxipyip = se_past_cell.conc_X;
	Xximyi = west_past_cell.conc_X;
	Xxipyim = sw_past_cell.conc_X;
	Xxiyip = south_past_cell.conc_X;
	Xximyip = ne_past_cell.conc_X;
	Xxiyim = north_past_cell.conc_X;
	Xximyim = nw_past_cell.conc_X;

	Yxiyi = past_cell.conc_Y;
	Yxipyi = east_past_cell.conc_Y;
	Yxipyip = se_past_cell.conc_Y;
	Yximyi = west_past_cell.conc_Y;
	Yxipyim = sw_past_cell.conc_Y;
	Yxiyip = south_past_cell.conc_Y;
	Yximyip = ne_past_cell.conc_Y;
	Yxiyim = north_past_cell.conc_Y;
	Yximyim = nw_past_cell.conc_Y;

	Zxiyi = past_cell.conc_Z;
	Zxipyi = east_past_cell.conc_Z;
	Zxipyip = se_past_cell.conc_Z;
	Zximyi = west_past_cell.conc_Z;
	Zxipyim = sw_past_cell.conc_Z;
	Zxiyip = south_past_cell.conc_Z;
	Zximyip = ne_past_cell.conc_Z;
	Zxiyim = north_past_cell.conc_Z;
	Zximyim = nw_past_cell.conc_Z;

	dXdt = data.X_difus * laplacian ( Xxiyi, Xxipyi, Xximyi,
						Xxiyip, Xxiyim,
						Xxipyip, Xxipyim,
						Xximyip, Xximyim, delta );
	dYdt = data.Y_difus * laplacian ( Yxiyi, Yxipyi, Yximyi,
						Yxiyip, Yxiyim,
						Yxipyip, Yxipyim,
						Yximyip, Yximyim, delta );
	dZdt = data.Z_difus * laplacian ( Zxiyi, Zxipyi, Zximyi,
						Zxiyip, Zxiyim,
						Zxipyip, Zxipyim,
						Zximyip, Zximyim, delta );

	*conc_X_new = Xxiyi + h * dXdt;
	*conc_Y_new = Yxiyi + h * dYdt;
	*conc_Z_new = Zxiyi + h * dZdt;

}

/* Update the concentrations globally using Fick's 2nd Law through
 * several applications of the previous function.
 */
void diffuse ( info data, state past_state, state *diff_state ) {

	cell past_cell, north_cell, west_cell, south_cell, east_cell,
			se_cell, sw_cell, ne_cell, nw_cell;
	int i, j, size;
	double conc_X, conc_Y, conc_Z;

	size = data.mesh_size;

	for ( i = 1; i < size - 1; i++ ) {
		for ( j = 1; j < size - 1; j++ ) {
			past_cell = past_state.cells[i][j];
			north_cell = past_state.cells[i+1][j];
			west_cell = past_state.cells[i][j+1];
			south_cell = past_state.cells[i-1][j];
			east_cell = past_state.cells[i][j-1];
			sw_cell = past_state.cells[i+1][j-1];
			ne_cell = past_state.cells[i-1][j+1];
			nw_cell = past_state.cells[i-1][j-1];
			se_cell = past_state.cells[i+1][j+1];
			diffusion_contrib ( &conc_X, &conc_Y, &conc_Z,
					data, past_cell,
						north_cell,
						east_cell,
						south_cell,
						west_cell,
						sw_cell,
						ne_cell,
						nw_cell,
						se_cell );
			diff_state->cells[i][j].conc_X = conc_X;
			diff_state->cells[i][j].conc_Y = conc_Y;
			diff_state->cells[i][j].conc_Z = conc_Z;
		}
	}

	for ( i = 0; i < size; i++ ) {
		diff_state->cells[i][0] = diff_state->cells[i][1];
		diff_state->cells[i][size-1] = diff_state->cells[i][size-2];
		diff_state->cells[0][i] = diff_state->cells[1][i];
		diff_state->cells[size-1][i] = diff_state->cells[size-2][i];
	}

}

/* Updates the concentrations globally through calls to
 * 'reaction_contrib'.
 */
void react ( info data, state diff_state, state *reac_state ) {

	cell past_cell;
	int i, j, size;
	double conc_X, conc_Y, conc_Z;

	size = data.mesh_size;

	for ( i = 0; i < size; i++ ) {
		for ( j = 0; j < size; j++ ) {
			past_cell = diff_state.cells[i][j];
			reaction_contrib ( &conc_X, &conc_Y, &conc_Z,
					data, past_cell );
			reac_state->cells[i][j].conc_X = conc_X;
			reac_state->cells[i][j].conc_Y = conc_Y;
			reac_state->cells[i][j].conc_Z = conc_Z;
		}
	}

}

void iterate ( workspace *snapshots, info data ) {

	state state_past, state_diff, state_reac;
	double h;

	h = data.h;

	state_past = snapshots->states[0];
	state_diff = snapshots->states[1];
	state_reac = snapshots->states[2];

	react ( data, state_past, &state_reac );
	diffuse ( data, state_reac, &state_diff );

	snapshots->states[0] = state_diff;
	snapshots->states[1] = state_past;
	snapshots->states[2] = state_reac;

	snapshots->time += h;

}

/* Same as previous function but assuming diffusion zero.
 */
void iterate_simple ( workspace *snapshots, info data ) {

	state state_past, state_reac;
	double h;

	h = data.h;

	state_past = snapshots->states[0];
	state_reac = snapshots->states[2];

	react ( data, state_past, &state_reac );

	snapshots->states[0] = state_reac;
	snapshots->states[1] = state_past;

	snapshots->time += h;

}
