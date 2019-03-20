/*
 * info.h
 *
 *  Created on: Sep 10, 2018
 *      Author: Sebastian Murillo
 */

#ifndef INFO_H_
#define INFO_H_
#define MAX_STRING 256
_Bool extractData(const char *filename, char *result, const char* start,
		const char* end);
// Parte B
void getName(char* result);
void getDate(char* result);
void getTime(char* result);
void getCPU(char* result);
void getOS(char* result);
void getKernelVersion(char* result);
void getTimeSinceBoot(char* result);
void getSupportedFilesystems(char* result);
// Parte C
void getCPUSpecifics(char* result);
void getContextSwitches(char* result);
void getBootTime(char* result);
void getCreatedProcesses(char* result);
// Parte D
void getIORequests(char* result);
void getHardwareMemory(char* result);
void getAvailableMemory(char* result);
void getLoadAvg(char* result);
// get CONFIG_HZ para convertir jiffies en sec
int getHZ();
#endif /* INFO_H_ */
