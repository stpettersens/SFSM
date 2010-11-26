/*
	SFSM (Scriptable Finite State Machine)

	A finate state machine executor written in C,
	which runs FSMs specified in *.fsm scripts.

	Copyright (c) 2010 Sam Saint-Pettersen.
	Licensed under the MIT/X11 License.
	Please see LICENSE file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xplatform.h"

#define MAXLINES 1000
#define MAXLEN 100

int numLines;
char lines[MAXLINES][MAXLEN];

struct stateMachine {
	char *sequence;
	int delay;
	int repeat;
	char *state;
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
	int i, x, match;
	char *s;
	for(i = 0; i < numLines; i++) {
		if(strcmp(lines[i], ":define sequence") == 0) {
			fsm.sequence = lines[i+1];
		}
		else if(strcmp(lines[i], ":delay") == 0) {
			fsm.delay = atoi(lines[i+1]);
		}
		else if(strcmp(lines[i], ":repeat") == 0) {
			fsm.repeat = atoi(lines[i+1]);
		}
		else if(strcmp(lines[i], ":state") == 0) {
			strcat(s, lines[i+1]);
			puts(s);
		}
	}
	dumpFSM();
}

// Dump the loaded FSM internals
void dumpFSM(void) {
	printf("FSM sequence: %s\n", fsm.sequence);
	printf("FSM delay (ms): %i\n", fsm.delay);
	printf("FSM repeat (1/0): %i\n", fsm.repeat);
}
