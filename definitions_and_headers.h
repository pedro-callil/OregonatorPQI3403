# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <sys/param.h>
# include <time.h>
# include <getopt.h>

# define TRUE 1
# define FALSE 0

# define PI	3.141592653589793

# define WORKSPACE_SIZE	3

# define MAX_FILENAME_SIZE	256

# define RKG_A	0.20710678118654757
# define RKG_B	0.2928932188134524
# define RKG_C	-0.7071067811865476
# define RKG_D	1.7071067811865475

typedef struct {
	double r_x; /* cell position in x and y axis*/
	double r_y;
	double conc_A; /* concentration of each substance in cell */
	double conc_B;
	double conc_P;
	double conc_X;
	double conc_Y;
	double conc_Z;
} cell; /* each cellular automata */

typedef struct {
	cell **cells;
} state; /* the state of the system at some point is defined by *
	  * the concentration of each component in each cell. */

typedef struct {
	state states[WORKSPACE_SIZE];
	double time;
} workspace; /* not in use, currently; could be useful if
	      * we wanted to use multi-step methods for
	      * solving the ODE.
	      */

typedef struct {
	int mesh_size;
	int number_of_centers;
	int simple;
	int verbose;
	double delta;
	double time_to_simulate;
	double h;
	double drop_radius;
	double conc_A_init;
	double conc_B_init;
	double conc_H_plus;
	double conc_X_in_drop;
	double conc_Y_in_drop;
	double conc_Z_in_drop;
	double A_difus;
	double B_difus;
	double P_difus;
	double X_difus;
	double Y_difus;
	double Z_difus;
	double efficiency;
	double k_1;
	double k_2;
	double k_3;
	double k_4;
	double k_5;
} info; /* all info needed to initialize the system. */

extern void getargs ( int number_of_args, char *the_args[],
		info *data, int *interval, char *filename, char *logfilename );
extern void print_usage ( void );
extern void initialize ( workspace *snapshots, info data );
extern void initialize_simple ( workspace *snapshots, info data );
extern void iterate ( workspace *snapshots, info data );
extern void iterate_simple ( workspace *snapshots, info data );
extern void reseed ( workspace *snapshots, info data );
extern void write_to_file ( workspace snapshots, info data, char *filename );
extern void write_to_file_simple ( workspace snapshots, info data, char *filename );
extern void log_info ( workspace snapshots, info data, int is_final,
		char *logfilename, char *filename, int interval );
extern void erase_previous_file ( char *filename, char *logfilename );
