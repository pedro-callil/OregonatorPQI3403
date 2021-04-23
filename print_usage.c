# include "definitions_and_headers.h"

/* This function prints a small manual. There should be a fancier
 * way to do this, but here we are.
 */
void print_usage ( void ) {

	printf ( "Usage: OregonatorSolve [OPTIONS]\n" );
	printf ( "Simulate the Belousov-Zhabotinksy reaction using the\n" );
	printf ( "Oregonator, by default in a reaction-diffusion system,\n" );
	printf ( "behaviour that can be overriden, if one wants to simulate\n" );
	printf ( "an ideally mixed system. The following options can be set:\n" );
	printf ( "\n" );
	printf ( "\t-a <initial concentration of A>\n" );
	printf ( "\t-A <diffusivity of A>\n" );
	printf ( "\t-b <initial concentration of B>\n" );
	printf ( "\t-B <diffusivity of B>\n" );
	printf ( "\t-D\n" );
	printf ( "\t\tUse default options\n" );
	printf ( "\t-f <f>\n" );
	printf ( "\t-h\n" );
	printf ( "\t\tPrint this help\n" );
	printf ( "\t-H <concentration of hydrogen ions>\n" );
	printf ( "\t-I <steps between storage to file>\n" );
	printf ( "\t-i <k1>\n" );
	printf ( "\t-j <k2>\n" );
	printf ( "\t-k <k3>\n" );
	printf ( "\t-l <k4>\n" );
	printf ( "\t-m <kc>\n" );
	printf ( "\t-N <initial number of reaction centers>\n" );
	printf ( "\t-p <initial concentration of P>\n" );
	printf ( "\t-P <diffusivity of P>\n" );
	printf ( "\t-q\n" );
	printf ( "\t\tQuiet: hide almost all console messages\n" );
	printf ( "\t-s <size of the mesh for diffusion-reaction problem>\n" );
	printf ( "\t-S <file in which the results shall be stored>\n" );
	printf ( "\t-L <file in which the logs shall be stored>\n" );
	printf ( "\t-t <time step for differential equation solver>\n" );
	printf ( "\t-T <duration of the simulation>\n" );
	printf ( "\t-U\n" );
	printf ( "\t\tSimple: we assume ideal mixing and replace the\n" );
	printf ( "\t\treaction-diffusion system with a simple system of\n" );
	printf ( "\t\tordinary differential equations\n" );
	printf ( "\t-x <initial concentration of X (in drop)>\n" );
	printf ( "\t-X <diffusivity of X>\n" );
	printf ( "\t-y <initial concentration of Y>\n" );
	printf ( "\t-Y <diffusivity of Y>\n" );
	printf ( "\t-z <initial concentration of Z>\n" );
	printf ( "\t-Z <diffusivity of Z>\n" );
	printf ( "\n" );
	printf ( "By default the file in which the results are stored is named\n" );
	printf ( "\"simulation_results.csv\", and the file in which completion\n" );
	printf ( "status and parameters are stored is \"simulation_logs.csv\".\n" );
	printf ( "\n" );
	printf ( "The results are stored in a slightly unusual format, due to\n" );
	printf ( "intrinsical demands of the system, if the option -U is not\n" );
	printf ( "informed; a small example follows:\n" );
	printf ( "\n" );
	printf ( "0.000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000009,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000059,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "1.000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000000,0.000000\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000067,0.000049\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000007,0.000018\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000159,0.000195\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000067,0.000049\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000007,0.000018\n" );
	printf ( "0.000000,0.000000,0.000000,0.000000,0.000159,0.000195\n" );
	printf ( "\n" );
	printf ( "This file, whose values were obtained invoking the program\n" );
	printf ( "with options \"-s 6 -T 2 -I 1 -t 1\", is an artificially\n" );
	printf ( "built example of the format in which results are stored; the\n" );
	printf ( "number alone in its line stores the simulation time needed to\n" );
	printf ( "arrive at the concentrations in the lines below. The number\n" );
	printf ( "occupying the (m+1)-th column of the (3n+1)-th line is the\n" );
	printf ( "value of [X] at the cell m,n of the mesh. The values of [Y]\n" );
	printf ( "and [Z] are, respectively, one and two lines below it.\n" );
	printf ( "\n" );
	printf ( "If invoked with the option -U, the data are stored in an\n" );
	printf ( "intuitive format: a .csv file in which the first column is\n" );
	printf ( "time and the next three [X], [Y] and [Z], respectively.\n" );

}
