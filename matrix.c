#include <stdio.h>
#include <stdlib.h>  //동적할당 함수를 쓰기 위해서 라이브러리를 포함시킨다.
#include <time.h>  

/* Method Declaration */
int** create_matrix(int row, int col);  //이중포인터로 행렬을 만드는 함수 
void print_matrix(int** matrix, int row, int col);  //행렬을 출력하는 함수
int free_matrix(int** matrix, int row, int col);  //동적 할당된 메모리를 해제하는 함수
int fill_data(int** matrix, int row, int col);  //메모리가 동적 할당된 행렬에 값을 채우는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  //두 행렬의 데이터끼리 더하여 새로운 행렬에 저장하고 그 데이터를 출력하는 함수(두 행렬의 합)
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);  //두 행렬의 데이터끼리 빼서 새로운 행렬에 저장하고 그 데이터를 출력하는 함수(두 행렬의 차)
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  //matrix 행렬의 행과 열의 크기를 바꿔, 전치행렬 matrix_t를 만드는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);  //두 행렬의 데이터끼리 곱해서 새로운 행렬에 저장하고 그 데이터를 출력하는 함수(두 행렬의 곱)

int main()
{
    char command;  //기능 선택을 위한 문자형 변수를 선언한다.
    printf("[----- [배기원]  [2021041081] -----]\n");

	int row, col;
	srand(time(NULL));  //매번 랜덤 값이 새롭게 지정되도록 하는 함수이다.

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);  //행과 열을 입력
    int** matrix_a = create_matrix(row, col);  //리턴 받은 2차원 행렬을 이중포인터 matrix_a에 할당한다.(인자는 (call by value)*2)
	int** matrix_b = create_matrix(row, col);  //위와 동일.
    int** matrix_a_t = create_matrix(col, row);  //row와 col을 바꿔 col by row행렬을 matrix_a_t에 할당한다.

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //만약 행렬이 제대로 할당되지 않았다면, 에러 발생을 의미하는 'return -1'로 프로그램을 종료한다.

	do{
		printf("\n----------------------------------------------------------------\n");  //행렬을 이용하는 메뉴 출력
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {  //각 입력값에 따라 기능을 실행한다.
		case 'z': case 'Z':
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);  //matrix_a와 b에 값을 채운다.(인자는 call by reference, (call by value)*2)
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':
            printf("\n[Print matrix]\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);  //matrix_a와 b를 출력한다.(인자는 call by reference, (call by value)*2)
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
        case 'a': case 'A':
			printf("\n[Add two matrices]\n");
			addition_matrix(matrix_a, matrix_b, row, col);  //matrix_a와 matrix_b의 데이터의 합을 출력한다.(인자는 (call by reference)*2, (call by value)*2)
			break;
        case 's': case 'S':
			printf("\n[Subtract two matrices] \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);  //matrix_a와 matrix_b의 데이터의 차를 출력한다.(인자는 (call by reference)*2, (call by value)*2)
			break;
        case 't': case 'T':
			printf("\n[Transpose matrix_a] \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  //matrix_a의 행과 열의 크기를 바꾼다.(인자는 (call by reference)*2, (call by value)*2)
            print_matrix(matrix_a_t, col, row);  //matrix_a_t를 출력한다.
			break;
        case 'm': case 'M':
			printf("\n[Multiply matrix_a with transposed matrix_a] \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);  //matrix_a의 행과 열의 크기를 바꾼다.
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //matrix_a와 matrix_a_t의 데이터의 곱을 출력한다.(인자는 (call by reference)*2, (call by value)*2)
			break;
        case 'q': case 'Q':
            printf("\nFree all matrices..\n");
            free_matrix(matrix_a_t, col, row);  //동적 할당 되어있는 메모리들을 해제한다.
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //quit를 의미하는 'q'나 'Q'를 입력하기 전까지 반복한다.

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);  //row개 만큼의 주소 저장 크기인 8byte 메모리를, 이중포인터 matrix에 할당한다.
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);  //이중포인터 matrix의 각 인덱스(=각 행)마다 col개의 4byte(int크기) 메모리를 할당한다. 
	}

	/* Check post conditions */
	if (matrix == NULL) {  //matrix에 동적 할당이 잘 되었는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;  //만든 row by col 행렬을 리턴한다.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");  
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //행렬의 각 인덱스들을 차례대로 출력한다.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {  //메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return;
	}

	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //포인터 matrix의 각 인덱스에 동적 할당된 메모리를 해제한다.(저장되어있는 데이터 또한 모두 사라진다.)
		free(matrix[matrix_row]);
	}

	free(matrix);  //이중포인터 matrix에 동적 할당된 메모리를 해제한다.(저장되어있는 데이터 또한 모두 사라진다.)
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;  
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)  //행과 열의 인덱스마다 0~19사이 값을 랜덤으로 저장한다.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;
	/* Check post conditions */
    if (matrix == NULL) {  //메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);  //이중포인터 matrix_sum을 새로 만들고 동적 할당한다.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_a와 b의 같은 인덱스끼리 값을 더하여, matrix_sum의 해당 인덱스에 저장한다.  
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {  //각 행렬에 메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);  //matrix_sum을 출력한다.
	free_matrix(matrix_sum, row, col);  //matrix_sum의 동적 할당된 메모리를 해제한다.(저장되어있는 데이터 또한 모두 사라진다.)
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);  //이중포인터 matrix_sub을 새로 만들고 동적 할당한다.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_a와 b의 같은 인덱스끼리 값을 빼서, matrix_sum의 해당 인덱스에 저장한다.  
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {  //각 행렬에 메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);  //matrix_sub을 출력한다.
	free_matrix(matrix_sub, row, col);  //matrix_sub의 동적 할당된 메모리를 해제한다.(저장되어있는 데이터 또한 모두 사라진다.)

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix 행렬의 행과 열의 크기를 바꿔, 전치행렬 matrix_t를 만든다.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {  //두 행렬에 메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);  //이중포인터 matrix_axt를 새로 만들고 동적 할당한다.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //행과 열이 0보다 커야한다.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {  //matrix_a와 matrix_a의 전치행렬 matrix_t의 각 행의 인덱스 값들을 곱해, 
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];  //임시저장소 temp에 저장하고,
			matrix_axt[matrix_a_row][matrix_t_row] = temp;  //matrix_axt[matrix_a_row][matrix_t_row]에 저장한다.
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {  //두 행렬에 메모리가 제대로 할당되어 있는지 확인한다.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);  //matrix_axt를 출력한다.
	free_matrix(matrix_axt, row, col);  //matrix_axt의 동적 할당된 메모리를 해제한다.(저장되어있는 데이터 또한 모두 사라진다.)
	return 1;
}

