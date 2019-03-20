/*
 ============================================================================
 Name        : mn_regresion_lineal.c
 Author      : Sebastian Murillo
 Version     : 
 Copyright   : free
 Description : implementation of lineal regresion algorithm
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
double X[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
double Y[] = {0.5, 2.5, 2.0, 4.0, 3.5, 6.0, 5.5};
// end config
void regresion_lineal(double* a, double* b);

int main(void) {
	printf("> %-13s[%s]\n\n", "starting:", "regresion_lineal");
	double a, b;
	regresion_lineal(&a, &b);
	printf("\n> result is y(x) = %.*f x + %.*f\n\n", FLOAT_DECIMALS, a, FLOAT_DECIMALS, b);
	printf("> %-13s[%s]\n", "stopping:", "regresion_lineal");
	return EXIT_SUCCESS;
}

void regresion_lineal(double* a, double* b){
	printf("> lineal regression:\n");
	if(sizeof(X) != sizeof(Y)){
		printf(TAB "@regresion_lineal - ERROR: sizeof(X) != sizeof(Y)\n");
		return;
	}
	int n = sizeof(X) / sizeof(double);
	double sum_X = 0.0;
	double sum_Y = 0.0;
	double sum_XY = 0.0;
	double sum_XX = 0.0;
	// a, b
	for(int i = 0;i < n; i++){
		sum_X += X[i];
		sum_Y += Y[i];
		sum_XY += X[i] * Y[i];
		sum_XX += X[i] * X[i];
	}
	double mean_X = sum_X / n;
	double mean_Y = sum_Y / n;
	*a = (n * sum_XY - sum_X * sum_Y) / (n * sum_XX - sum_X * sum_X);
	*b = mean_Y - (*a) * mean_X;
	// Sr, Syx, St
	double Sr = 0.0;
	double Syx;
	double St = 0.0;
	double r2;
	for(int i = 0;i < n; i++){
		Sr += pow((Y[i] - (*a) * X[i] - (*b)), 2.0);
		St += pow(mean_Y - Y[i], 2.0);
	}
	Syx = sqrt(Sr / (n - 2));
	r2 = (St - Sr) / St;
	// print
	printf(TAB "Sr:  [%.*f]\n", FLOAT_DECIMALS, Sr);
	printf(TAB "Syx: [%.*f]\n", FLOAT_DECIMALS, Syx);
	printf(TAB "St:  [%.*f]\n", FLOAT_DECIMALS, St);
	printf(TAB "r^2: [%.*f]\n", FLOAT_DECIMALS, r2);
	return;
}
