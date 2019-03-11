/*
 ============================================================================
 Name        : ksamp.c
 Author      : Sebastian Murillo
 Version     : 1.0
 Copyright   : GNU General Public License
 Description : shows basic information about running linux system
 ============================================================================
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <info.h>

// una separacion de la info mostrada en 3 grupos
#define showTags false

static int samplingInterval = 5;
static int showInfoTime = 1;

void showTutorial();
void showHeader();
void showInfoA();
void showInfoB();
void showInfoC();
void printInfo(const char* info, const char* value);

int main(int argc, char *argv[]) {
	printf("> ksamp starting...\n\n");
	// START parsing
	bool flagS = false;
	bool flagL = false;
	int opt;
	while ((opt = getopt(argc, argv, "sl")) != -1) {
		switch (opt) {
		case 's':
			flagS = true;
			break;
		case 'l':
			flagL = true;
			if (strcmp(argv[1], "-l") == 0) {
				if (argc < 4)
					showTutorial();

				if (!isdigit(*argv[2]) || !isdigit(*argv[3]))
					showTutorial();

				samplingInterval = atoi(argv[2]);
				showInfoTime = atoi(argv[3]);
			} else if (strcmp(argv[2], "-l") == 0) {
				if (argc < 5)
					showTutorial();

				if (!isdigit(*argv[3]) || !isdigit(*argv[4]))
					showTutorial();

				samplingInterval = atoi(argv[3]);
				showInfoTime = atoi(argv[4]);
			} else {
				showTutorial();
			}
			break;
		default:
			showTutorial();
		}
	}
	if (samplingInterval < 1 || showInfoTime < 1)
		showTutorial();
	// END parsing
	// START ksamp
	showHeader();
	showInfoA();
	if (flagS) {
		showInfoB();
	}
	if (flagL) {
		for (int L = showInfoTime / samplingInterval; L > 1; L--) {
			showInfoC();
			sleep(samplingInterval);
		}
		showInfoC(); // ultimo fuera del loop para no esperar otro sleep antes de terminar
	}
	printf("> ksamp is done\n");
	exit(EXIT_SUCCESS);
	// END ksamp
}

// muestra como usar programa
void showTutorial() {
	puts("  usage: ksamp [OPTIONS]");
	puts("      options:");
	printf("          %-15s%s", "-s:", "shows more info\n");
	printf("          %-15s%s", "-l [a] [b]:",
			"shows even more info every a seconds for b seconds\n\n");
	exit(EXIT_FAILURE);
}

void showHeader() {
	char output[MAX_STRING];
	if (showTags)
		printf("[header]\n");
	getName(output);
	printInfo("host: ", output);
	getDate(output);
	char tmp[MAX_STRING];
	getTime(tmp);
	strcat(output, " | ");
	strcat(output, tmp);
	printInfo("date & time:", output);
	if (showTags)
		printf("[/header]\n\n");
}

void showInfoA() {
	char output[MAX_STRING];
	if (showTags)
		printf("[showInfoA]\n");
	getCPU(output);
	printInfo("CPU info:", output);
	getOS(output);
	strcat(output, " with linux kernel ");
	char tmp[MAX_STRING];
	getKernelVersion(tmp);
	strcat(output, tmp);
	printInfo("OS & kernel:", output);
	getTimeSinceBoot(output);
	printInfo("time since boot:", output);
	getSupportedFilesystems(output);
	printInfo("filesystems supported:", output);
	if (showTags)
		printf("[/showInfoA]\n\n");
}

void showInfoB() {
	char output[MAX_STRING];
	if (showTags)
		printf("[showInfoB]\n");
	getCPUSpecifics(output);
	printInfo("CPU used by user | sys | idle (sec):", output);
	getContextSwitches(output);
	printInfo("conxtext changes:", output);
	getBootTime(output);
	printInfo("boot date & time:", output);
	getCreatedProcesses(output);
	printInfo("number of processes:", output);
	if (showTags)
		printf("[/showInfoB]\n\n");

}

void showInfoC() {
	char output[MAX_STRING];
	if (showTags)
		printf("[showInfoC]\n");
	getIORequests(output);
	printInfo("disk requests (I/O):", output);
	// comentado por distinto formato, funciona bien
	/*
	 getHardwareMemory(output);
	 printInfo("total memory (MB):", output);
	 getAvailableMemory(output);
	 printInfo("available memory (MB):", output);
	 */
	getAvailableMemory(output);
	strcat(output, "/");
	char tmp[MAX_STRING];
	getHardwareMemory(tmp);
	strcat(output, tmp);
	strcat(output, " MB");
	printInfo("memory (available/total):", output);
	getLoadAvg(output);
	printInfo("load average (1 min):", output);
	if (showTags)
		printf("[/showInfoC]\n\n");
	else {
		printf("\n");
	}
}

// un print con formato
void printInfo(const char* info, const char* value) {
	printf("  %-40s%s\n", info, value);
}