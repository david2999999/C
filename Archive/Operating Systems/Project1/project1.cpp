// David Jiang
// Project 1

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "time_functions.h"

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#endif

using namespace std;

void firstFunction(char *in_path, char *out_path);
void secondFunction(char *in_path, char *out_path);


int main()
{
	#ifdef _WIN32  //Windows
	       char in_path[]="C:\\temp\\coursein\\p1-in.txt";
	       char out_path[]="C:\\temp\\courseout\\p1-out.txt";
	#else //Linux
             char in_path[200], out_path[200];
		     const char *homedir;
		     homedir = getenv("HOME");
		     if (homedir!= NULL)
			    homedir = getpwuid(getuid())->pw_dir;
		     strcpy(in_path,homedir);
		     strcpy(out_path,homedir);
		     // now add on the common part of the path
		     strcat(in_path,"/temp/coursein/p1-in.txt");
		     strcat(out_path,"/temp/courseout/p1-out.txt");
	#endif
	int mode;

	cout << "\nEnter the mode of the application (0 or 1): ";
	cin >> mode;

	if (mode == 0)
	{
		firstFunction(in_path, out_path);
	}
	else if (mode == 1)
	{
		secondFunction(in_path, out_path);
	}
	else {
		cout << "There is no such mode.";
	}

}

void firstFunction(char *in_path, char *out_path) {
	// single character to be read from the text file
	char c;

	// read and write text files
	ifstream readFile;
	ofstream writeFile;

	// opening both read and write files
	readFile.open(in_path);
	writeFile.open(out_path);

	// if the read file can not be opened, exit the program
	if (!readFile) {
		cerr << "Unable to open file read.txt";
		exit(1);
	}

	start_nanotime();
	start_timing();

	// reading the file one character at a time
	while (readFile.get(c) && !readFile.eof()) {
		// write the character to another file
		writeFile << c;
	}

	stop_timing();

	cout << "CPU elapsed time: " << (get_nanodiff() / 1000000.0) << " ms" << endl;
	cout << "Wall Clock Time: " << get_wall_clock_diff()  * 1000.0 << " ms" << endl;

	// closing both read and write file
	readFile.close();
	writeFile.close();
}

void secondFunction(char *in_path, char *out_path) {
	// read and write text files
	ifstream readFile;
	ofstream writeFile;

	// opening both read and write files
	readFile.open(in_path);
	writeFile.open(out_path);

	// if the read file can not be opened, exit the program
	if (!readFile) {
		cerr << "Unable to open file read.txt";
		exit(1);
	}

	start_nanotime();
	start_timing();

	if(readFile) {
		for(string line; getline(readFile, line);) {
			writeFile << line << endl;
		}
	}

	stop_timing();

	cout << "CPU elapsed time: " << (get_nanodiff() / 1000000.0) << " ms" << endl;
	cout << "Wall Clock Time: " << get_wall_clock_diff() * 1000.0 << " ms" << endl;

	// closing both read and write file
	readFile.close();
	writeFile.close();
}
