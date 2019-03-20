/*
 ============================================================================
 Name        : mn_seccion_aurea.c
 Author      : Sebastian Murillo
 Version     : 
 Copyright   : free
 Description : implementation of golden ratio algorithm for function root search
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TITLE_ALIGNMENT 12
#define TAB "    "
#define FLOAT_DECIMALS 4

// config
#define GOLDEN_RATIO 0.61803398875
//#define GOLDEN_RATIO 1.61803398875
#define SEARCH_MIN 11
#define SEARCH_MAX 111
#define MAX_ERROR 0.0005
#define MAX_ITERATIONS 1000
#define X_MIN 0.0
#define X_MAX 15.0

// f(x) = -(x-5)^2 + 10
double f(double x){
	return (- pow(x - 5, 2.0) + 10);
}
// end config
double method_seccion_aurea(int min_max);


int main(void) {
	printf("> %-13s[%s]\n\n", "starting:", "seccion_aurea");
	double result = method_seccion_aurea(SEARCH_MAX);
	printf("\n> result is: %.2f\n\n", result);
	printf("> %-13s[%s]\n", "stopping:", "seccion_aurea");
	return EXIT_SUCCESS;
}

double method_seccion_aurea(int min_max){
	if(min_max != SEARCH_MIN && min_max != SEARCH_MAX){
		printf("@method_seccion_aurea: min or max? -> invalid\n");
		return -999;
	}
	double X1 = X_MIN;
	double X2 = X_MAX;
	double Xopt;
	double D;
	double error = 100000 * MAX_ERROR;
	for(int i = 0;fabs(error) > MAX_ERROR && i < MAX_ITERATIONS; i++){
		D = GOLDEN_RATIO * fabs(X2 - X1);
		double Xa = X1 + D;
		double Xb = X2 - D;
		double Fa = f(Xa);
		double Fb = f(Xb);
		if(min_max == SEARCH_MAX){
			if(Fa > Fb){
				X1 = Xb;
				Xopt = X2;
			}
			else{
				X2 = Xa;
				Xopt = X1;
			}
		}
		else{ // SEARCH_MIN
			if(Fa > Fb){
				X2 = Xa;
				Xopt = X2;
			}
			else{				
				X1 = Xb;
				Xopt = X1;
			}
		}
		error = fabs(X1 - X2) / (fabs(Xa) + fabs(Xb));
		if(Fa == Fb) return Xopt;
		//print
		char tmp[128];
		int align1 = 8;
		printf("> %s %d:\n", "iteracion", i);
		// D
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, D);
		printf(TAB "%-*s%-s\n", align1, "D:", tmp);
		// X1
		sprintf(tmp, "[%.*f] -> [%.*f]", FLOAT_DECIMALS, Xa - D, FLOAT_DECIMALS, X1);
		printf(TAB "%-*s%-s\n", align1, "X1:", tmp);
		// X2
		sprintf(tmp, "[%.*f] -> [%.*f]", FLOAT_DECIMALS, Xb + D, FLOAT_DECIMALS, X2);
		printf(TAB "%-*s%-s\n", align1, "X2:", tmp);
		/*		
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, Xa);
		printf(TAB "%-*s%-s\n", align1, "Xa:", tmp);		
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, Xb);
		printf(TAB "%-*s%-s\n", align1, "Xb:", tmp);		
		printf(TAB "Xopt = ");
		if(Xopt == X1) printf("X1\n");
		if(Xopt == X2) printf("X2\n");
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, Fa);
		printf(TAB "%-*s%-s\n", align1, "Fa:", tmp);
		sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, Fb);
		printf(TAB "%-*s%-s\n", align1, "Fb:", tmp);
		*/	
		printf(TAB "%-*s[%.*f]\n", 8, "error:", 2 * FLOAT_DECIMALS, error);
		double newerror = (1 - GOLDEN_RATIO) * fabs((X_MAX - X_MIN) / Xopt);
		printf(TAB "%-*s[%.*f]\n", 8, "newerror:", 2 * FLOAT_DECIMALS, newerror);
	}
	return Xopt;
}

