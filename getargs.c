# include "definitions_and_headers.h"

/* This function reads the arguments specified by the user and stores
 * it for future system initialization and iteration.
*/
void getargs ( int number_of_args, char **the_args,
	info *data, int *interval, char *filename, char *logfilename ) {

	int opt;

	if ( number_of_args < 2 ) {
		printf ( "For help, OregonatorSolve -h\n" );
		exit (32); /* without arguments specified, halt. */
	}

	*interval = 300;
	strcpy (filename, "simulation_results.csv");
	strcpy (logfilename, "simulation_results.log");

	data->simple = FALSE;
	data->verbose = TRUE;
	data->mesh_size = 300;
	data->delta = 0.1 * pow ( (double) data->mesh_size, -1 );
	data->time_to_simulate = 300;
	data->h = 0.001;
	data->conc_A_init = 0.06;
	data->conc_B_init = 0.02;
	data->conc_H_plus = 0.8;
	data->A_difus = 1e-9;
	data->B_difus = 1e-9;
	data->P_difus = 1e-9;
	data->X_difus = 1e-9;
	data->Y_difus = 1e-9;
	data->Z_difus = 1e-9;
	data->efficiency = 1.0;
	data->k_1 = 2.0*0.8*0.8;
	data->k_2 = 3e6*0.8;
	data->k_3 = 42.0*0.8;
	data->k_4 = 3000*0.8;
	data->k_5 = 1.0;
	data->number_of_centers = 16;
	data->conc_X_in_drop = 9.911e-6;
	data->conc_Y_in_drop = 3.732e-9;
	data->conc_Z_in_drop = 5.968e-5;
	/* default values */

	while ((opt = getopt (number_of_args, the_args,
		":hs:N:T:t:d:Da:b:A:B:P:X:Y:Z:f:i:j:k:l:L:m:I:x:y:z:H:S:Uq")) != -1) {
		switch (opt) {
			case 'q':
				data->verbose = FALSE;
				break;
			case 'h':
				print_usage ();
				exit (31);
				break;
			case 'U':
				data->simple = TRUE;
				data->mesh_size = 1;
				break;
			case 's':
				data->mesh_size = (int) strtod (optarg, NULL);
				data->delta = 0.1 *
					pow ( (double) data->mesh_size, -1 );
				break;
			case 'N':
				data->number_of_centers = (int) strtod (optarg, NULL);
				break;
			case 'T':
				data->time_to_simulate = strtod (optarg, NULL);
				break;
			case 't':
				data->h = strtod (optarg, NULL);
				break;
			case 'd':
				data->drop_radius = strtod (optarg, NULL);
				break;
			case 'D':
				printf ( "Using default options...\n" );
				break;
			case 'a':
				data->conc_A_init = strtod (optarg, NULL);
				break;
			case 'b':
				data->conc_B_init = strtod (optarg, NULL);
				break;
			case 'H':
				data->conc_H_plus = strtod (optarg, NULL);
				data->k_1 *= (data->conc_H_plus)/0.8;
				data->k_1 *= (data->conc_H_plus)/0.8;
				data->k_2 *= (data->conc_H_plus)/0.8;
				data->k_3 *= (data->conc_H_plus)/0.8;
				data->k_4 *= (data->conc_H_plus)/0.8;
				break;
				/* change ki's if pH informed */
			case 'A':
				data->A_difus = strtod (optarg, NULL);
				break;
			case 'B':
				data->B_difus = strtod (optarg, NULL);
				break;
			case 'P':
				data->P_difus = strtod (optarg, NULL);
				break;
			case 'X':
				data->X_difus = strtod (optarg, NULL);
				break;
			case 'Y':
				data->Y_difus = strtod (optarg, NULL);
				break;
			case 'Z':
				data->Z_difus = strtod (optarg, NULL);
				break;
			case 'f':
				data->efficiency = strtod (optarg, NULL);
				break;
			case 'i':
				data->k_1 = strtod (optarg, NULL);
				break;
			case 'j':
				data->k_2 = strtod (optarg, NULL);
				break;
			case 'k':
				data->k_3 = strtod (optarg, NULL);
				break;
			case 'l':
				data->k_4 = strtod (optarg, NULL);
				break;
			case 'm':
				data->k_5 = strtod (optarg, NULL);
				break;
			case 'x':
				data->conc_X_in_drop = strtod (optarg, NULL);
				break;
			case 'y':
				data->conc_Y_in_drop = strtod (optarg, NULL);
				break;
			case 'z':
				data->conc_Z_in_drop = strtod (optarg, NULL);
				break;
			case 'I':
				*interval = (int) strtod (optarg, NULL);
				break;
			case 'S':
				strcpy (filename, optarg);
				break;
			case 'L':
				strcpy (logfilename, optarg);
				break;
		}
	}

}
