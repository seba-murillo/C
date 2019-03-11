/*
 ============================================================================
 Name        : optimizacion_newton.c
 Author      : 
 Version     : 
 Copyright   : 
 Description : 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// format
#define TITLE_ALIGNMENT 12
#define TAB "    "
#define FLOAT_DECIMALS 4
// config
#define MAX_ERROR 0.001
#define MAX_ITERATIONS 1000
#define START_X 2.5
double f(double x){
	return (2 * sin(x) - pow(x, 2.0) / 10);
}

double df(double x){
	return (2 * cos(x) - x / 5);
}
double ddf(double x){
	return (-2 * sin(x) - 0.2);
}
// end config
double newton();
double getError(double _new, double _old);

int main(void) {
	printf("> %-13s[%s]\n\n", "starting:", "optimizacion_newton");
	double result = newton();
	printf("\n> max is f(%.*f) = [%.*f]\n\n", FLOAT_DECIMALS, result, FLOAT_DECIMALS, f(result));
	printf("> %-13s[%s]\n", "stopping:", "optimizacion_newton");
	return EXIT_SUCCESS;
}

double newton(){
	double new_X = START_X;
	double old_X = START_X;
	double error = 100000 * MAX_ERROR;		
	for(int i = 0;fabs(error) > MAX_ERROR && i < MAX_ITERATIONS; i++){		
		new_X = old_X - (df(old_X) / ddf(old_X));
		error = getError(new_X, old_X);
		//print
		char tmp[128];
		printf("> %s %d:\n", "iteracion", i);
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, new_X);
		printf(TAB "X:      %-s\n", tmp);
		printf(TAB "%-*s[%.*f]\n", 8, "error:", 2 * FLOAT_DECIMALS, error);
		old_X = new_X;
	}
	return new_X;
}

double getError(double _new, double _old){
	return ((_new - _old) * 100 / _new);
}