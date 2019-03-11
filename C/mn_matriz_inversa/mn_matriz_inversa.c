/*
 ============================================================================
 Name        : mn_matriz_inversa.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define TITLE_ALIGNMENT 12
#define TAB "    "
#define ALIGN 8
#define FLOAT_DECIMALS 2
#define MAX_POLINOMIAL_ORDER 100
#define MAX_STRING 128

// config
#define ORDER 3
void init();
// end config

typedef struct matrix_structure matrix;
struct matrix_structure {
	unsigned int rows;
	unsigned int cols;
	double data[ORDER + 1][ORDER + 1];
};

matrix A;

matrix new_matrix(unsigned int rows, unsigned int cols);
void print_matrix(matrix mat);
matrix getLeftSide(matrix mat);
matrix getRightSide(matrix mat);
matrix multiplicate(matrix mat1, matrix mat2);
matrix transpose(matrix mat);
matrix copy(matrix from);

matrix pivot(matrix mat);
matrix decomp_LU();
matrix decomp_L();
matrix decomp_U();
matrix forward_substitution(matrix mat, matrix equals);
matrix backward_substitution(matrix mat, matrix equals);
matrix invert(matrix mat);

int main(void) {
	printf("> %-*s[%s]\n", TITLE_ALIGNMENT, "starting:", "matriz_inversa");
	
	// creando matriz
	init();
	printf("> A:\n");
	print_matrix(A);
	
	// pivot
	//A = pivot(A);
	//printf("> A (pivoted):\n");
	//print_matrix(A);
	
	// copy
	matrix C = copy(A);
	printf("> C (copy):\n");
	print_matrix(C);
	
	// transpose
	matrix T = transpose(getLeftSide(A));
	printf("> T (transpose):\n");
	print_matrix(T);
	
	// LU decomp
	matrix LU = decomp_LU(A);
	matrix L = decomp_L(A);
	matrix U = decomp_U(A);
	matrix B = getRightSide(A);
	matrix D = forward_substitution(L, B);
	matrix X = backward_substitution(U, D);
	printf("> L+U:\n");	
	print_matrix(LU);
	printf("> L:\n");
	print_matrix(L);
	printf("> U:\n");
	print_matrix(U);
	printf("> B:\n");
	print_matrix(B);
	printf("> D (forward substitution):\n");
	print_matrix(D);
	printf("> D (right side of LU):\n");
	D = getRightSide(LU);
	print_matrix(D);
	printf("> X:\n");
	print_matrix(X);
	
	// invert
	matrix I = invert(getLeftSide(A));
	matrix II = invert(I);
	printf("> I (invert):\n");
	print_matrix(I);
	printf("> II (inverted invert):\n");
	print_matrix(II);
	printf("> original (A):\n");
	print_matrix(getLeftSide(A));
	printf("> I * II:\n");
	print_matrix(multiplicate(I, II));
	printf("> %-*s[%s]\n", TITLE_ALIGNMENT, "stopping:", "matriz_inversa" );
	return EXIT_SUCCESS;
}

void init(){
	/*
	A.rows = ORDER;
	A.cols = ORDER + 1;
	
	A.data[0][0] = 3;
	A.data[0][1] = -0.1;
	A.data[0][2] = -0.2;
	A.data[0][3] = 7.85;
	
	A.data[1][0] = 0.1;
	A.data[1][1] = 7;
	A.data[1][2] = -0.3;
	A.data[1][3] = -19.3;
	
	A.data[2][0] = 0.3;
	A.data[2][1] = -0.2;
	A.data[2][2] = 10.0;
	A.data[2][3] = 71.4;
	*/
	//{ 1, 1, 0}
	//{ 0, 3, 1}
	//{ 2, 0, 1}
	A.rows = ORDER;
	A.cols = ORDER;
	A.data[0][0] = 1;
	A.data[0][1] = 1;
	A.data[0][2] = 0;
	A.data[1][0] = 0;
	A.data[1][1] = 3;
	A.data[1][2] = 1;
	A.data[2][0] = 2;
	A.data[2][1] = 0;
	A.data[2][2] = 1;	
}

matrix new_matrix(unsigned int rows, unsigned int cols){
	matrix result;
	result.rows = rows;
	result.cols = cols;
	if(rows == 0) result.rows = ORDER;
	if(cols == 0) result.cols = ORDER;
	for(int x = 0;x < result.rows;x++){
		for(int y = 0;y < result.cols;y++){
			result.data[x][y] = 0.0;
		}
	}
	return result;
}

void print_matrix(matrix mat){
	int alignment = 7 + FLOAT_DECIMALS;
	char tmp[30];
	for(int x = 0;x < mat.rows;x++){
		for(int y = 0;y < mat.cols;y++){
			//double val = mat.data[x * mat.cols + y];
			//if(mat.data[x][y] == 0.0) sprintf(tmp, " ");
			if(mat.data[x][y] == 0.0) sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, mat.data[x][y]);
			else{
				sprintf(tmp, "[%.*f]", FLOAT_DECIMALS, mat.data[x][y]);
			}
			if(mat.cols > mat.rows && y == mat.cols - 1){
				printf(TAB "||");
			}
			printf(TAB "%*s", alignment, tmp);
		}
		printf("\n");
	}
	printf("\n");
}

matrix getLeftSide(matrix mat){
	mat.cols = mat.rows;
	return mat;
}

matrix getRightSide(matrix mat){
	matrix equals = new_matrix(0, 1);
	for(int x = 0;x < mat.rows;x++){
		equals.data[x][0] = mat.data[x][mat.cols - 1];
	}
	return equals;
}

matrix transpose(matrix mat) {
	matrix result = new_matrix(mat.cols, mat.rows);
	for(int x = 0;x < mat.rows;x++){
		for(int y = 0;y < mat.cols;y++){
			//result.data[y * mat.rows + x] = mat.data[x * mat.cols + y];
			result.data[y][x] = mat.data[x][y];
		}
	}
	return result;
}

matrix multiplicate(matrix mat1, matrix mat2){	
	if(mat1.rows == 0 || mat1.cols == 0){
		printf("ERROR @ invert(): invalid matrix 'mat1'\n");
		return mat1;
	}
	if(mat2.rows == 0 || mat2.cols == 0){
		printf("ERROR @ invert(): invalid matrix 'mat2'\n");
		return mat2;
	}
	if(mat1.cols != mat2.rows){
		printf("ERROR @ invert(): invalid operation (%dx%d * %dx%d)\n", mat1.rows, mat1.cols, mat2.rows, mat2.cols);
		return mat2;
	}
	matrix result = new_matrix(mat1.rows, mat2.cols);
	for(int x = 0;x < mat1.rows;x++){
		for(int y = 0;y < mat2.cols;y++){
			for(int tmp = 0;tmp < mat1.cols;tmp++){
				result.data[x][y] += mat1.data[x][tmp] * mat2.data[tmp][y];
			}
		}
	}
	return result;
}

matrix copy(matrix from) {
	return from;
}

matrix pivot(matrix mat) {
	double tmp[ORDER + 1];
	for(int i = 0;i < ORDER - 1;i++){
		// get highest pivot
		double max = DBL_MIN;
		int row;
		for(int x = i;x < ORDER;x++){
			if(mat.data[x][0] > max){
				max = mat.data[x][0];
				row = x;
			}
		}
		// copy highest pivot row
		for(int y = 0;y < ORDER + 1;y++)
			tmp[y] = mat.data[row][y];
		// copy current row to highest pivot row
		for(int y = 0;y < ORDER + 1;y++)
			mat.data[row][y] = mat.data[i][y];
		// highest pivot row to current row
		for(int y = 0;y < ORDER + 1;y++)
			mat.data[i][y] = tmp[y];
	}
	return mat;
}

matrix decomp_LU(matrix mat) {
	if(mat.cols - mat.rows < 0 || mat.cols - mat.rows > 1){
		printf("ERROR @ decomp_LU(): invalid matrix\n");
		return mat;
	}
	double f;
	for(int x = 0;x < mat.rows - 1;x++){
		for(int n = x + 1;n < mat.rows;n++){
			f = mat.data[n][x] / mat.data[x][x];
			for(int y = 0;y < mat.cols + 1;y++){
				mat.data[n][y] -= f * mat.data[x][y];
			}
			mat.data[n][x] = f;
		}
	}
	return mat;
}

matrix decomp_L(matrix mat) {
	matrix result = decomp_LU(mat);
	result.cols = result.rows;
	for(int x = 0; x < result.rows;x++){
		for(int y = 0; y < result.cols;y++){
			if(x == y){
				result.data[x][y] = 1.0;
			}
			if(y > x) result.data[x][y] = 0.0;
		}			
	}
	return result;
}

matrix decomp_U(matrix mat) {
	matrix result = decomp_LU(mat);
	result.cols = result.rows;
	for(int x = 0; x < result.rows;x++){
		for(int y = 0; y < result.cols;y++){
			if(x > y) result.data[x][y] = 0.0;
		}			
	}
	return result;
}

matrix forward_substitution(matrix mat, matrix equals){
	if(equals.cols > 1){
		printf("ERROR @ forward_substitution(): invalid matrix 'equals'\n");
		return mat;
	}
	for(int x = 0;x < mat.rows;x++){
		// get row solution
		for(int y = 0;y < x;y++){
			equals.data[x][0] -= mat.data[x][y];
		}
		// replace downwards
		for(int r = x + 1;r < mat.rows;r++){
			mat.data[r][x] *= equals.data[x][0];
		}
	}
	return equals;
}

matrix backward_substitution(matrix mat, matrix equals){
	if(equals.cols > 1){
		printf("ERROR @ backward_substitution(): invalid matrix 'equals'\n");
		return mat;
	}
	for(int x = mat.rows - 1;x >= 0;x--){
		// get row solution
		for(int y = mat.cols - 1;y > x;y--){
			equals.data[x][0] -= mat.data[x][y];
			mat.data[x][y] = 0.0;
		}
		equals.data[x][0] /= mat.data[x][x];
		mat.data[x][x] = 1.0;
		// replace upwards
		for(int r = x - 1;r >= 0;r--){
			mat.data[r][x] *= equals.data[x][0];
		}
	}
	return equals;
}

matrix invert(matrix mat) {
	if(mat.rows == 0 || mat.cols != mat.rows){
		printf("ERROR @ invert(): invalid matrix\n");
		return mat;
	}
	printf("@invert()\n");
	matrix L = decomp_L(mat);
	matrix U = decomp_U(mat);
	matrix result = new_matrix(mat.rows, mat.cols);
	for(int i = 0;i < mat.cols;i++){
		printf(TAB "i: %d\n", i);
		matrix tmp = new_matrix(0, 1);
		tmp.data[i][0] = 1.0;
		printf(TAB "tmp:\n");
		print_matrix(tmp);
		matrix tmp_D = forward_substitution(L, tmp);
		matrix tmp_X = backward_substitution(U, tmp_D);
		printf(TAB "tmp_D:\n");
		print_matrix(tmp_D);
		printf(TAB "tmp_X:\n");
		print_matrix(tmp_X);
		for(int x = 0;x < result.rows;x++){
			result.data[x][i] = tmp_X.data[x][0];;
		}
		printf(TAB "result:\n");
		print_matrix(result);
	}
	return result;
}