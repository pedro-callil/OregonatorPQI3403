# include "definitions_and_headers.h"

int main ( int argc, char **argv ) {

	workspace snapshots;
	info data;
	char filename[MAX_FILENAME_SIZE];
	char logfilename[MAX_FILENAME_SIZE];
	int iteration, interval, state_index, centers_used;
	unsigned long long number_of_steps;

	getargs ( argc, argv, &data, &interval, filename, logfilename );

	srand ((unsigned int)time(NULL));

	erase_previous_file ( filename, logfilename );

	if ( data.simple == FALSE ) {
		initialize ( &snapshots, data );
		centers_used = 0;
		number_of_steps = (int) ((double) data.time_to_simulate/data.h);
		for ( iteration = 0; iteration < number_of_steps; iteration++ ) {
			if ( iteration % interval == 0 ) {
				if ( ( iteration / interval ) % 10 == 0 &&
				centers_used < (double) data.number_of_centers ) {
					reseed ( &snapshots, data );
					centers_used++;
				}
				write_to_file ( snapshots, data, filename );
				log_info ( snapshots, data, FALSE,
						logfilename, filename, interval );
			}
			iterate ( &snapshots, data );
		}
		for ( state_index = 0; state_index < WORKSPACE_SIZE; state_index++ ) {
			free(snapshots.states[state_index].cells);
		}
	} else {
		initialize_simple ( &snapshots, data );
		number_of_steps = (unsigned long long)
			((double) data.time_to_simulate/data.h);
		for ( iteration = 0; iteration < number_of_steps; iteration++ ) {
			if ( iteration % interval == 0 ) {
				write_to_file_simple ( snapshots, data, filename );
				log_info ( snapshots, data, FALSE,
						logfilename, filename, interval );
			}
			iterate_simple ( &snapshots, data );
		}
	}

	log_info ( snapshots, data, TRUE, logfilename, filename, interval );


	return 0;

}
