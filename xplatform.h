/*
	C/C++ header file implementing some
	useful cross platform functions.
	
	Public domain.
	
	Author: Sam Saint-Pettersen.
*/
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else 
#include <unistd.h>
#endif

// Function prototypes
void xsleep(int ms);
void xcls(void);

// Function to pause execution of program 
// for so many milliseconds.
void xsleep(int ms) {
#ifdef _WIN32
	Sleep(ms);
#else	
	sleep(ms / 1000); // UNISTD sleep takes s rather than ms
#endif
}

// Function to clear the screen.
void xcls(void) {
#ifdef _WIN32
	system("cls"); // WIN32 -> CLS
#else
	system("clear"); // *NIX -> CLEAR
#endif
}
