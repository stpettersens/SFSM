/*
	SFSM (Scriptable Finite State Machine)

	A finate state machine executor written in C,
	which runs FSMs specified in *.fsm scripts.

	Copyright (c) 2010 Sam Saint-Pettersen.
	Licensed under the MIT/X11 License.
	Please see LICENSE file.
*/
#include <stdio.h>
#include <string.h>
#include "xplatform.h"

#define MAXLINES 1000
#define MAXLEN 100

int numLines;
char lines[MAXLINES][MAXLEN];

struct fsm {
	char *sequence;
};

struct fsm theMachine;

void loadFSM(char *file);
void parseFSM(void);
void executeFSM(void);

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

void loadFSM(char *file) {
	FILE *pFile;
	char line[MAXLEN];
	pFile = fopen(file, "r");
	if(pFile != NULL) {
		int i = 0;
		while(fgets(line, MAXLEN, pFile) != NULL) {
			strcpy(lines[i], strtrim(line));
			i++;
			numLines++;
		}
	}
	parseFSM();
}

void parseFSM(void) {
	int i, match;
	for(i = 0; i < numLines; i++) {
		if(strcmp(lines[i], ":define sequence") == 0) {
			theMachine.sequence = lines[i+1];
		}
	}
}
