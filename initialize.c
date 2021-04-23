# include "definitions_and_headers.h"

/* This function introduces uncertainty in the number
 * of reaction centers.
 */
int get_number_of_centers ( int N_given ) {

	double u1, u2, z;
	int N_real;

	u1 = (double) rand() / (double ) RAND_MAX;
	u2 = (double) rand() / (double ) RAND_MAX;

	z = sqrt ( -2 * log (u1) ) * cos ( 2 * PI * u2 );

	N_real = (int) ( (float) N_given/2 + z + 0.5 );

	return N_real;

}

/* This function returns a list of random coordinates for the
 * reaction centers.
 */
void get_centers ( int **centers, int number_of_centers, int size ) {

	int i, j, k;

	for ( k = 0; k < number_of_centers; k++ ) {
		i = rand() % (size - 5);
		i+=4;
		j = rand() % (size - 5);
		j+=4;
		centers[k][0] = i;
		centers[k][1] = j;
	}

}

/* This small function checks if a certain coordinate is
 * a reaction center.
 */
int is_center ( int **centers, int i, int j, int number_of_centers ) {

	int k, result;

	result = FALSE;

	for ( k = 0; k < number_of_centers; k++ ) {
		if ( abs(centers[k][0] - i) <= 0 &&
			abs(centers[k][1] - j) <= 0 ) {
			result = TRUE;
		}
	}

	return result;
}

/* This function initializes the system with small concentrations
 * of X, Y and Z in the centers, using the data informed.
 */
void initialize ( workspace *snapshots, info data ) {

	int i, j, k;
	state init_state[WORKSPACE_SIZE];
	cell **cells;
	int size;

	size = data.mesh_size;
	for ( k = 0; k < WORKSPACE_SIZE; k++ ) {
		cells = malloc (size * sizeof(cell *));
		for ( i = 0; i < size; i++ ) {
			cells[i] = malloc ( size * sizeof(cell));
			for ( j = 0; j < size; j++ ){
				cells[i][j].r_x = ((double) i)/(size - 1);
				cells[i][j].r_y = ((double) j)/(size - 1);
				cells[i][j].conc_A = data.conc_A_init;
				cells[i][j].conc_B = data.conc_B_init;
				cells[i][j].conc_P = 0;
				cells[i][j].conc_X = 0;
				cells[i][j].conc_Y = 0;
				cells[i][j].conc_Z = 0;
			}
		}
		init_state[k].cells = cells;
		snapshots->states[k] = init_state[k];
	}

	snapshots->time = 0;
}

/* This function is similar to the one above, but excludes the reaction
 * centers, for it initializes a well-mixed system in which there is no
 * need for spatial information.
 */
void initialize_simple ( workspace *snapshots, info data ) {

	int i, j, k;
	state init_state[WORKSPACE_SIZE];
	cell **cells;
	int size;

	size = data.mesh_size;
	for ( k = 0; k < WORKSPACE_SIZE; k++ ) {
		cells = malloc (size * sizeof(cell *));
		for ( i = 0; i < size; i++ ) {
			cells[i] = malloc ( size * sizeof(cell));
			for ( j = 0; j < size; j++ ){
				cells[i][j].r_x = ((double) i)/(size - 1);
				cells[i][j].r_y = ((double) j)/(size - 1);
				cells[i][j].conc_A = data.conc_A_init;
				cells[i][j].conc_B = data.conc_B_init;
				cells[i][j].conc_P = 0;
				cells[i][j].conc_X = data.conc_X_in_drop;
				cells[i][j].conc_Y = data.conc_Y_in_drop;
				cells[i][j].conc_Z = data.conc_Z_in_drop;
			}
		}
		init_state[k].cells = cells;
		snapshots->states[k] = init_state[k];
	}

	snapshots->time = 0;
}

/* This function starts more reaction centers to mimic the real
 * reaction behaviour, i.e. several centers evolving separately,
 * unlike one would see by initializing all of them simultaneously.
 */
void reseed ( workspace *snapshots, info data ) {

	int i, j, k;
	int **centers;
	int size, number_of_centers;

	size = data.mesh_size;
	number_of_centers = 1;
	centers = malloc (number_of_centers * sizeof(int *));
	for ( k = 0; k < number_of_centers; k++ ) {
		centers[k] = malloc (2 * sizeof(int));
	}
	get_centers ( centers, number_of_centers, size );
	for ( k = 0; k < WORKSPACE_SIZE; k++ ) {
		for ( i = 0; i < size; i++ ) {
			for ( j = 0; j < size; j++ ){
				if ( is_center ( centers, i, j,
					number_of_centers ) == TRUE ) {
					snapshots->states[k].cells[i][j].conc_X =
						data.conc_X_in_drop;
					snapshots->states[k].cells[i][j].conc_Y =
						data.conc_Y_in_drop;
					snapshots->states[k].cells[i][j].conc_Z =
						data.conc_Z_in_drop;
				}
			}
		}
	}

}
