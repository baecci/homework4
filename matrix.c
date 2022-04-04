#include <stdio.h>
#include <stdlib.h>  //�����Ҵ� �Լ��� ���� ���ؼ� ���̺귯���� ���Խ�Ų��.
#include <time.h>  

/* Method Declaration */
int** create_matrix(int row, int col);  //���������ͷ� ����� ����� �Լ� 
void print_matrix(int** matrix, int row, int col);  //����� ����ϴ� �Լ�
int free_matrix(int** matrix, int row, int col);  //���� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
int fill_data(int** matrix, int row, int col);  //�޸𸮰� ���� �Ҵ�� ��Ŀ� ���� ä��� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  //�� ����� �����ͳ��� ���Ͽ� ���ο� ��Ŀ� �����ϰ� �� �����͸� ����ϴ� �Լ�(�� ����� ��)
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);  //�� ����� �����ͳ��� ���� ���ο� ��Ŀ� �����ϰ� �� �����͸� ����ϴ� �Լ�(�� ����� ��)
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  //matrix ����� ��� ���� ũ�⸦ �ٲ�, ��ġ��� matrix_t�� ����� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);  //�� ����� �����ͳ��� ���ؼ� ���ο� ��Ŀ� �����ϰ� �� �����͸� ����ϴ� �Լ�(�� ����� ��)

int main()
{
    char command;  //��� ������ ���� ������ ������ �����Ѵ�.
    printf("[----- [����]  [2021041081] -----]\n");

	int row, col;
	srand(time(NULL));  //�Ź� ���� ���� ���Ӱ� �����ǵ��� �ϴ� �Լ��̴�.

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);  //��� ���� �Է�
    int** matrix_a = create_matrix(row, col);  //���� ���� 2���� ����� ���������� matrix_a�� �Ҵ��Ѵ�.(���ڴ� (call by value)*2)
	int** matrix_b = create_matrix(row, col);  //���� ����.
    int** matrix_a_t = create_matrix(col, row);  //row�� col�� �ٲ� col by row����� matrix_a_t�� �Ҵ��Ѵ�.

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //���� ����� ����� �Ҵ���� �ʾҴٸ�, ���� �߻��� �ǹ��ϴ� 'return -1'�� ���α׷��� �����Ѵ�.

	do{
		printf("\n----------------------------------------------------------------\n");  //����� �̿��ϴ� �޴� ���
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {  //�� �Է°��� ���� ����� �����Ѵ�.
		case 'z': case 'Z':
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);  //matrix_a�� b�� ���� ä���.(���ڴ� call by reference, (call by value)*2)
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':
            printf("\n[Print matrix]\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);  //matrix_a�� b�� ����Ѵ�.(���ڴ� call by reference, (call by value)*2)
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
        case 'a': case 'A':
			printf("\n[Add two matrices]\n");
			addition_matrix(matrix_a, matrix_b, row, col);  //matrix_a�� matrix_b�� �������� ���� ����Ѵ�.(���ڴ� (call by reference)*2, (call by value)*2)
			break;
        case 's': case 'S':
			printf("\n[Subtract two matrices] \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);  //matrix_a�� matrix_b�� �������� ���� ����Ѵ�.(���ڴ� (call by reference)*2, (call by value)*2)
			break;
        case 't': case 'T':
			printf("\n[Transpose matrix_a] \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  //matrix_a�� ��� ���� ũ�⸦ �ٲ۴�.(���ڴ� (call by reference)*2, (call by value)*2)
            print_matrix(matrix_a_t, col, row);  //matrix_a_t�� ����Ѵ�.
			break;
        case 'm': case 'M':
			printf("\n[Multiply matrix_a with transposed matrix_a] \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);  //matrix_a�� ��� ���� ũ�⸦ �ٲ۴�.
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //matrix_a�� matrix_a_t�� �������� ���� ����Ѵ�.(���ڴ� (call by reference)*2, (call by value)*2)
			break;
        case 'q': case 'Q':
            printf("\nFree all matrices..\n");
            free_matrix(matrix_a_t, col, row);  //���� �Ҵ� �Ǿ��ִ� �޸𸮵��� �����Ѵ�.
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //quit�� �ǹ��ϴ� 'q'�� 'Q'�� �Է��ϱ� ������ �ݺ��Ѵ�.

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);  //row�� ��ŭ�� �ּ� ���� ũ���� 8byte �޸𸮸�, ���������� matrix�� �Ҵ��Ѵ�.
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);  //���������� matrix�� �� �ε���(=�� ��)���� col���� 4byte(intũ��) �޸𸮸� �Ҵ��Ѵ�. 
	}

	/* Check post conditions */
	if (matrix == NULL) {  //matrix�� ���� �Ҵ��� �� �Ǿ����� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;  //���� row by col ����� �����Ѵ�.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");  
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //����� �� �ε������� ���ʴ�� ����Ѵ�.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {  //�޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return;
	}

	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //������ matrix�� �� �ε����� ���� �Ҵ�� �޸𸮸� �����Ѵ�.(����Ǿ��ִ� ������ ���� ��� �������.)
		free(matrix[matrix_row]);
	}

	free(matrix);  //���������� matrix�� ���� �Ҵ�� �޸𸮸� �����Ѵ�.(����Ǿ��ִ� ������ ���� ��� �������.)
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;  
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)  //��� ���� �ε������� 0~19���� ���� �������� �����Ѵ�.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;
	/* Check post conditions */
    if (matrix == NULL) {  //�޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);  //���������� matrix_sum�� ���� ����� ���� �Ҵ��Ѵ�.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_a�� b�� ���� �ε������� ���� ���Ͽ�, matrix_sum�� �ش� �ε����� �����Ѵ�.  
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {  //�� ��Ŀ� �޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);  //matrix_sum�� ����Ѵ�.
	free_matrix(matrix_sum, row, col);  //matrix_sum�� ���� �Ҵ�� �޸𸮸� �����Ѵ�.(����Ǿ��ִ� ������ ���� ��� �������.)
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);  //���������� matrix_sub�� ���� ����� ���� �Ҵ��Ѵ�.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_a�� b�� ���� �ε������� ���� ����, matrix_sum�� �ش� �ε����� �����Ѵ�.  
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {  //�� ��Ŀ� �޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);  //matrix_sub�� ����Ѵ�.
	free_matrix(matrix_sub, row, col);  //matrix_sub�� ���� �Ҵ�� �޸𸮸� �����Ѵ�.(����Ǿ��ִ� ������ ���� ��� �������.)

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix ����� ��� ���� ũ�⸦ �ٲ�, ��ġ��� matrix_t�� �����.
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {  //�� ��Ŀ� �޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);  //���������� matrix_axt�� ���� ����� ���� �Ҵ��Ѵ�.
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {  //��� ���� 0���� Ŀ���Ѵ�.
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {  //matrix_a�� matrix_a�� ��ġ��� matrix_t�� �� ���� �ε��� ������ ����, 
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];  //�ӽ������ temp�� �����ϰ�,
			matrix_axt[matrix_a_row][matrix_t_row] = temp;  //matrix_axt[matrix_a_row][matrix_t_row]�� �����Ѵ�.
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {  //�� ��Ŀ� �޸𸮰� ����� �Ҵ�Ǿ� �ִ��� Ȯ���Ѵ�.
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);  //matrix_axt�� ����Ѵ�.
	free_matrix(matrix_axt, row, col);  //matrix_axt�� ���� �Ҵ�� �޸𸮸� �����Ѵ�.(����Ǿ��ִ� ������ ���� ��� �������.)
	return 1;
}

