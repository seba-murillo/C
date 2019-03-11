/*
 * info.c
 *
 *  Created on: Sep 10, 2018
 *      Author: Sebastian Murillo
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <info.h>

/*
 * extractData extrae la informacion en el archivo 'filename', desde el primer 'start' hasta 'end', y lo guarda en 'result'
 * retorna
 * 		true: funciona
 * 		false: no se encuentra 'start'
 */
_Bool extractData(const char *filename, char *result, const char* start,
		const char* end) {
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL)
		return false;
	char line[MAX_STRING];
	bool flag_found = false;
	memset(result, 0, MAX_STRING); // clean string
	while (fgets(line, MAX_STRING, file) != NULL) {
		char *tmp = strstr(line, start);
		if (tmp != NULL) { // line found
			flag_found = true;
			int pos1 = tmp - line + strlen(start);
			int pos2 = strlen(line);
			tmp = strstr(line + pos1, end);
			if (tmp != NULL) {
				pos2 = tmp - line + strlen(end);
			}
			int p = 1;
			if (end[0] != '\n')
				p = strlen(end);
			strncpy(result, line + pos1, pos2 - pos1 - p);
			break;
		}
	}
	fclose(file);
	return flag_found;
}

void getName(char* result) {
	extractData("/proc/sys/kernel/hostname", result, "", "\n");
}

void getDate(char* result) {
	/*
	 extractData("/proc/driver/rtc", result, "rtc_date	: ", "\n");
	 int D, M, Y;
	 sscanf(result, "%d-%d-%d", &Y, &M, &D);
	 sprintf(result, "%d/%d/%d", D, M, Y);
	 */
	FILE *file;
	if ((file = popen("date +%d/%m/%y", "r")) == NULL) {
		sprintf(result, "%s", "ERROR @ getDate(char* result)");
	}
	fgets(result, MAX_STRING, file);
	result[strlen(result) - 1] = 0;
	pclose(file);
}

void getTime(char* result) {
//	extractData("/proc/driver/rtc", result, "rtc_time	: ", "\n");
	FILE *file;
	if ((file = popen("date +%H:%M:%S", "r")) == NULL) {
		sprintf(result, "%s", "ERROR @ getDate(char* result)");
	}
	fgets(result, MAX_STRING, file);
	result[strlen(result) - 1] = 0; // borrando '\n'
	pclose(file);
}

void getCPU(char* result) {
	extractData("/proc/cpuinfo", result, "model name	: ", "\n");
}

void getOS(char* result) {
	extractData("/proc/version", result, "#1 SMP ", "-");
}

void getKernelVersion(char* result) {
	extractData("/proc/version", result, "Linux version ", " ");
}

void getTimeSinceBoot(char* result) {
	extractData("/proc/uptime", result, "", " ");
	int time = atoi(result);
	int D = time / 86400;
	time -= D * 86400;
	int H = time / 3600;
	time -= H * 3600;
	int M = time / 60;
	time -= M * 60;
	int S = time;
	sprintf(result, "%02d:%02d:%02d:%02d", D, H, M, S);
}

// cuenta lineas en /proc/filesystems
void getSupportedFilesystems(char* result) {
	FILE *file;
	file = fopen("/proc/filesystems", "r");
	int count = 0;
	if (file != NULL) {
		while (!feof(file)) {
			if (fgetc(file) == '\n')
				count++;
		}
	}
	fclose(file);
	sprintf(result, "%d", count);
}

void getCPUSpecifics(char* result) {
	// http://man7.org/linux/man-pages/man5/proc.5.html
	FILE *file;
	file = fopen("/proc/stat", "r");
	if (file == NULL)
		return;
	int data[4] = { 0, 0, 0, 0 };
	fscanf(file, "cpu  %d %d %d %d %*d %*d %*d %*d %*d %*d", &data[0], &data[1],
			&data[2], &data[3]);
	fclose(file);
	int HZ = getHZ(); // HZ = 100
	sprintf(result, "%d | %d | %d", (data[0] + data[1]) / HZ, data[2] / HZ,
			data[3] / HZ);
}

void getContextSwitches(char* result) {
	extractData("/proc/stat", result, "ctxt ", "\n");
}

//current time (desde EPOCH) - uptime (desde EPOCH) = boot time (desde EPOCH) + formatting
void getBootTime(char* result) {
	/*
	 extractData("/proc/stat", result, "btime", "\n");
	 int time = atoi(result);
	 int D = time / 86400;
	 time -= D * 86400;
	 int H = time / 3600;
	 time -= H * 3600;
	 int M = time / 60;
	 time -= M * 60;
	 int S = time;
	 sprintf(result, "%02d:%02d:%02d:%02d", D, H, M, S);
	 */
	// No existe current time en /proc
	extractData("/proc/uptime", result, "", " ");
	unsigned int uptime = atoi(result);
	unsigned long int currentTime;
	FILE *file;
	if ((file = popen("date +%s", "r")) == NULL) {
		sprintf(result, "%s", "ERROR1 @ getBootTime(char* result)");
	}
	fgets(result, MAX_STRING, file);
	pclose(file);
	sscanf(result, "%lu", &currentTime);
	currentTime -= uptime; // bootTime (ahorrar memoria)
	sprintf(result, "date -d@%lu %s", currentTime, "'+%d/%m/%y | %H:%M:%S'"); // command (ahorrar memoria)
	if ((file = popen(result, "r")) == NULL) {
		sprintf(result, "%s", "ERROR2 @ getBootTime(char* result)");
	}
	fgets(result, MAX_STRING, file);
	result[strlen(result) - 1] = 0; // borrando '\n'
	pclose(file);
}

void getCreatedProcesses(char* result) {
	extractData("/proc/stat", result, "processes ", "\n");
}

void getIORequests(char* result) {
	//https://www.kernel.org/doc/Documentation/ABI/testing/procfs-diskstats
	FILE *file;
	file = fopen("/proc/diskstats", "r");
	int in = 0;
	int out = 0;
	if (file != NULL) {
		while (!feof(file)) {
			int i, o;
			int ok = fscanf(file,
					"%*d %*d %*s %d %*d %*d %*d %d %*d %*d %*d %*d %*d %*d", &i,
					&o);
			if (ok != -1) {
				in += i;
				out += o;
			}
		}
	}
	fclose(file);
	sprintf(result, "%d/%d", in, out);
}

void getHardwareMemory(char* result) {
	extractData("/proc/meminfo", result, "MemTotal:", "kB");
	sprintf(result, "%d", atoi(result) / 1024);
}

void getAvailableMemory(char* result) {
	extractData("/proc/meminfo", result, "MemFree:", "kB");
	sprintf(result, "%d", atoi(result) / 1024);
}

void getLoadAvg(char* result) {
	extractData("/proc/loadavg", result, "", " ");
}

// obtiene USER_HZ (que sirve para convertir de jiffies a sec en getCPUSpecifics(char* result)
int getHZ() {
	/*
	 char search[MAX_STRING], tmp[MAX_STRING];
	 sprintf(search, "%s", "/boot/config-");
	 //	printf("search [%s]\ntmp [%s]\n\n",search, tmp);
	 extractData("/proc/version", tmp, "Linux version ", " ");
	 strcat(search,tmp);
	 extractData(search, search, "CONFIG_HZ=", "\n");
	 //	printf("search [%s]\ntmp [%s]\n\n",search, tmp);
	 return atoi(search);
	 */
	return sysconf(_SC_CLK_TCK);
}