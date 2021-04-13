# include "definitions_and_headers.h"

void erase_previous_file (char *filename, char *logfilename) {

	FILE *simulation_results;
	FILE *simulation_log;

	simulation_results = fopen(filename,"w");
	fclose(simulation_results);

	simulation_log = fopen(logfilename,"w");
	fclose(simulation_log);

}


void write_to_file ( workspace snapshot, info data, char *filename ) {

	int i, j, size;
	double time;
	FILE *simulation_results;

	simulation_results = fopen(filename,"a");
	size = data.mesh_size;
	time = snapshot.time;

	fprintf ( simulation_results, "%f\n", time );
	for ( i = 0 ; i < size ; i++ ) {
		for ( j = 0; j < size; j++ ) {
			if ( j != size - 1 ) {
				fprintf ( simulation_results,"%1.9f,",
					snapshot.states[0].cells[i][j].conc_X );
			} else {
				fprintf ( simulation_results,"%1.9f",
					snapshot.states[0].cells[i][j].conc_X );
			}
		}
		fprintf ( simulation_results, "\n" );
		for ( j = 0; j < size; j++ ) {
			if ( j != size - 1 ) {
				fprintf ( simulation_results,"%1.9f,",
					snapshot.states[0].cells[i][j].conc_Y );
			} else {
				fprintf ( simulation_results,"%1.9f",
					snapshot.states[0].cells[i][j].conc_Y );
			}
		}
		fprintf ( simulation_results, "\n" );
		for ( j = 0; j < size; j++ ) {
			if ( j != size - 1 ) {
				fprintf ( simulation_results,"%1.9f,",
					snapshot.states[0].cells[i][j].conc_Z );
			} else {
				fprintf ( simulation_results,"%1.9f",
					snapshot.states[0].cells[i][j].conc_Z );
			}
		}
		fprintf ( simulation_results, "\n" );
	}

	fclose(simulation_results);
}

void write_to_file_simple ( workspace snapshot, info data, char *filename ) {

	int i, j, size;
	FILE *simulation_results;

	simulation_results = fopen(filename,"a");
	size = data.mesh_size;

	if ( snapshot.time == 0.0 ) {
		fprintf ( simulation_results, "t,x,y,z\n" );
	}
	for ( i = 0 ; i < size ; i++ ) {
		for ( j = 0; j < size; j++ ) {
			fprintf ( simulation_results,"%1.3f,%1.12f,%1.12f,%1.12f\n",
					snapshot.time,
					snapshot.states[0].cells[i][j].conc_X,
					snapshot.states[0].cells[i][j].conc_Y,
					snapshot.states[0].cells[i][j].conc_Z );
		}
	}

	fclose(simulation_results);
}

void log_info ( workspace snapshots, info data, int is_final,
		char *logfilename, char *filename, int interval ) {

	double est_len, order;
	FILE *simulation_log;

	simulation_log = fopen(logfilename,"a");
	if ( snapshots.time <= data.h ) {
		fprintf ( simulation_log,
			"==> This is OregonatorSolver 1.0 <==\n" );
		fprintf ( simulation_log, "\n" );
		fprintf ( simulation_log,
				"With options and parameters:\n" );
		fprintf ( simulation_log,
				"Mesh size:    %d\n", data.mesh_size );
		fprintf ( simulation_log,
				"Time:          %f\n", data.time_to_simulate );
		fprintf ( simulation_log,
				"Step:          %f\n", data.h );
		fprintf ( simulation_log,
				"[A]_0:         %e\n", data.conc_A_init );
		fprintf ( simulation_log,
				"[B]_0:         %e\n", data.conc_B_init );
		fprintf ( simulation_log,
				"[X]_0:         %e\n", data.conc_X_in_drop );
		fprintf ( simulation_log,
				"[Y]_0:         %e\n", data.conc_Y_in_drop );
		fprintf ( simulation_log,
				"[Z]_0:         %e\n", data.conc_Z_in_drop );
		fprintf ( simulation_log,
				"D_A:           %e\n", data.A_difus );
		fprintf ( simulation_log,
				"D_B:           %e\n", data.B_difus );
		fprintf ( simulation_log,
				"D_X:           %e\n", data.X_difus );
		fprintf ( simulation_log,
				"D_Y:           %e\n", data.Y_difus );
		fprintf ( simulation_log,
				"D_Z:           %e\n", data.Z_difus );
		fprintf ( simulation_log,
				"Centers:       %d\n", data.number_of_centers );
		fprintf ( simulation_log,
				"k_1:           %e\n", data.k_1 );
		fprintf ( simulation_log,
				"k_2:           %e\n", data.k_2 );
		fprintf ( simulation_log,
				"k_3:           %e\n", data.k_3 );
		fprintf ( simulation_log,
				"k_4:           %e\n", data.k_4 );
		fprintf ( simulation_log,
				"k_5:           %e\n", data.k_5 );
		fprintf ( simulation_log,
				"f:             %f\n", data.efficiency );
		fprintf ( simulation_log, "\n" );

		est_len = 12 *
			( (float) data.time_to_simulate /
			( data.h * (float) interval ) ) *
			pow ( data.mesh_size, 2 ) * 3;
		order = pow ( 10, 3 * (int) (log10 ( est_len ) / 3) );
		if ( order < 1000 ) {
			fprintf ( simulation_log,
				"Size of results file: %3.1f", est_len / order );
			fprintf ( simulation_log,
			". This seems small, are you sure everything is OK?\n" );
		} else if ( order < 1000000 ) {
			fprintf ( simulation_log,
				"Size of results file: %3.1f", est_len / order );
			fprintf ( simulation_log,
			"K. This will be quick.\n" );
		} else if ( order < 1000000000 ) {
			fprintf ( simulation_log,
				"Size of results file: %3.1f", est_len / order );
			fprintf ( simulation_log,
			"M.\n" );
		} else if ( order < 100000000000 ) {
			fprintf ( simulation_log,
				"Size of results file: %3.1f", est_len / order );
			fprintf ( simulation_log,
			"G. This will be slow, go grab a coffee.\n" );
		} else {
			fprintf ( simulation_log,
				"Size of results file: %3.1fG.", est_len / 1000000000 );
			fprintf ( simulation_log,
				"Are you absolutely sure that everything is OK?\n" );
		}
		if ( data.verbose == TRUE ) {
			printf (
				"==> This is OregonatorSolver v0.3 <==\n" );
			printf (
				"\nThe results will be available at %s\n", filename );
			printf (
				"\nThis log will be available at %s\n", logfilename );
			printf ( "\n" );
			printf ( "With options and parameters:\n" );
			printf ( "Mesh size:     %d\n", data.mesh_size );
			printf ( "Time:          %f\n", data.time_to_simulate );
			printf ( "Step:          %f\n", data.h );
			printf ( "[A]_0:         %e\n", data.conc_A_init );
			printf ( "[B]_0:         %e\n", data.conc_B_init );
			printf ( "[X]_0:         %e\n", data.conc_X_in_drop );
			printf ( "[Y]_0:         %e\n", data.conc_Y_in_drop );
			printf ( "[Z]_0:         %e\n", data.conc_Z_in_drop );
			printf ( "D_A:           %e\n", data.A_difus );
			printf ( "D_B:           %e\n", data.B_difus );
			printf ( "D_X:           %e\n", data.X_difus );
			printf ( "D_Y:           %e\n", data.Y_difus );
			printf ( "D_Z:           %e\n", data.Z_difus );
			printf ( "Centers:       %d\n", data.number_of_centers );
			printf ( "k_1:           %e\n", data.k_1 );
			printf ( "k_2:           %e\n", data.k_2 );
			printf ( "k_3:           %e\n", data.k_3 );
			printf ( "k_4:           %e\n", data.k_4 );
			printf ( "k_5:           %e\n", data.k_5 );
			printf ( "f:             %f\n", data.efficiency );
			printf ( "\n" );

			if ( order < 1000 ) {
				printf ( "Size of results file: %3.1f",
						est_len / order );
				printf ( ". This seems small, are you sure everything is OK?\n" );
			} else if ( order < 1000000 ) {
				printf ( "Size of results file: %3.1f",
						est_len / order );
				printf ( "K. This will be quick.\n" );
			} else if ( order < 1000000000 ) {
				printf ( "Size of results file: %3.1f",
						est_len / order );
				printf ( "M.\n" );
			} else if ( order < 100000000000 ) {
				printf ( "Size of results file: %3.1f",
						est_len / order );
				printf ( "G. This will be slow, go grab a coffee.\n" );
			} else {
				printf ( "Size of results file: %3.1fG.",
						est_len / 1000000000 );
				printf ( "Are you absolutely sure that everything is OK?\n" );
			}

		}

	}

	fprintf ( simulation_log, "%f%% completed;\n",
			100 * snapshots.time / data.time_to_simulate );

	if ( data.verbose == TRUE ) {
		printf ( "%f%% completed;\n",
			100 * snapshots.time / data.time_to_simulate );
	}

	if ( is_final == TRUE ) {
		fprintf ( simulation_log, "Simulation complete\n" );
		if ( data.verbose == TRUE ) {
			printf ( "Simulation complete\n" );
		}
	}

	fclose ( simulation_log );

}
