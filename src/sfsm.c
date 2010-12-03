/*
	SFSM (Scriptable Finite State Machine)

	A finate state machine executor written in C,
	which runs FSMs specified in *.fsm scripts.

	Copyright (c) 2010 Sam Saint-Pettersen.
	Released under the MIT/X11 License.
	Please see LICENSE file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xplatform.h"

#define MAXLEN 100

int numLines;
char lines[MAXLEN][MAXLEN];

struct stateMachine {
	char *sequence;
	int delay;
	int repeat;
	char state[MAXLEN][MAXLEN][MAXLEN];
};

struct stateMachine fsm;

void loadFSM(char *file);
void parseFSM(void);
void executeFSM(void);
void dumpFSM(void);

// Main method
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("SFSM (Scriptable Finite State Machine)");
		#ifdef _WIN32
		printf("\nUsage: sfsm.exe <fsm script>\n");
		#else 
		printf("\nUsage: sfsm <fsm script>\n");
		#endif
	}
	else loadFSM(argv[1]);
	return 0;
}

// Load the FSM script
void loadFSM(char *file) {
	FILE *pFile;
	char line[MAXLEN];
	pFile = fopen(file, "r");
	if(pFile != NULL) {
		int i = 0;
		while(fgets(line, MAXLEN, pFile) != NULL) {
			strcpy(lines[i], xstrtrim(line));
			i++;
			numLines++;
		}
	}
	parseFSM();
}

// Parse the FSM script into the FSM structure
void parseFSM(void) {
	int i; int x = 1; int z = 1;
	for(i = 0; i < numLines; i++) {
		if(strcmp(lines[i], ":sequence") == 0) {
			fsm.sequence = lines[++i];
		}
		else if(strcmp(lines[i], ":delay") == 0) {
			fsm.delay = atoi(lines[++i]);
		}
		else if(strcmp(lines[i], ":repeat") == 0) {
			fsm.repeat = atoi(lines[++i]);
		}
		else if(strcmp(lines[i], ":state") == 0) {
			i++;
			while(1) {  
  				strcpy(fsm.state[x][z], lines[i]);
  				z++; i++;
  				if(strcmp(lines[i], ".") == 0) {
        			x++; 
        			z = 0;
  				}
  				if(strcmp(lines[i], "") == 0) {
        			break;
  				}
			}
		}
	}
	printf("Test %s\n", fsm.state[2][0]);
	executeFSM();
}

// Execute the FSM
void executeFSM(void) {
	int x = 1; int z = 1;
	while(1) {
		printf("%i %i\n", x, z);
		printf("%s\n", fsm.state[x][z]);
		z++; 
		if(strcmp(fsm.state[x][z], ".") == 0) {
			x++;
			z = 0;
		}
		if(strcmp(fsm.state[x][z], "") == 0) {
			x++;
			z = 0;
  		}
  		if(x == 5) {
  			break;
  		}
	}
}

// DEBUG: Dump the loaded FSM internals
void dumpFSM(void) {
	printf("FSM sequence: %s", fsm.sequence);
	printf("\nFSM delay (ms): %i", fsm.delay);
	printf("\nFSM repeat (1/0): %i\n", fsm.repeat);
}
