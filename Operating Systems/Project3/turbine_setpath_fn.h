#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#endif

void setpath()
{
#if defined _WIN32 || defined WIN32 //Windows
	//strcpy_s(in_path, "C:\\temp\\coursein\\p3-in.txt");
	//strcpy_s(out_path, "C:\\temp\\courseout\\p3-out.txt");
	printf("hello im here");
	strcpy_s(in_path, "C:\\Users\\david2999999\\source\\repos\\Project1\\Project1\\turbine_setup.txt");
	strcpy_s(out_path, "C:\\Users\\david2999999\\source\\repos\\Project1\\Project1\\turbine_output.txt");

#else //Linux
	// For Linux, the "home" directory actually contains the current userid
	// so we have to get that name from the system and put it in front of the path.
	// Many Linux shells will only expand the "~" if it is used from the command line
	const char *homedir;
	homedir = getenv("HOME");
	if (homedir != NULL)
		homedir = getpwuid(getuid())->pw_dir;
	// get the actual home directory for the current user
	strcpy(in_path, homedir);
	strcpy(out_path, homedir);
	// now add on the detail part of the path
	strcat(in_path, "/temp/coursein/p3-in.txt");
	strcat(out_path, "/temp/courseout/p3-out.txt");
#endif
}

// Now you can use the names, infile and outfile in your fopen, input and output statements.
// example: infile=fopen(in_path,"r"); outfile=fopen(out_path,"w");
