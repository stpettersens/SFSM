/*
	SFSM (Scriptable Finite State Machine)

	A finate state machine executor written in C,
	which runs FSMs specified in *.fsm scripts.

	Copyright (c) 2010 Sam Saint-Pettersen.
	Licensed under the MIT/X11 License.
	Please see LICENSE file.
*/
#include <stdio.h>
#include "xplatform.h"

void loadStateMachine(char *file);

FILE *pFile;

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("SFSM (Scriptable Finite State Machine)");
		#ifdef _WIN32
		printf("\nUsage: sfsm.exe <fsm script>\n");
		#else 
		printf("\nUsage: sfsm <fsm script>\n");
		#endif
	}
	else loadStateMachine(argv[1]);
	return 0;
}

void loadStateMachine(char *file) {
	char *line;
	pFile = fopen(file, "r");
	if(pFile != NULL) {
		fgets(
	}
}
