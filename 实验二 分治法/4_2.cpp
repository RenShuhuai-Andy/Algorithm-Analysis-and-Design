#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;

int Strassen(int n, int** MatrixA, int ** MatrixB, int ** MatrixC);//Multiplies Two Matrices recrusively.
int ADD(int** MatrixA, int** MatrixB, int** MatrixResult, int length);//Adds two Matrices, and places the result in another Matrix
int SUB(int** MatrixA, int** MatrixB, int** MatrixResult, int length);//subtracts two Matrices , and places  the result in another Matrix
int MUL(int** MatrixA, int** MatrixB, int** MatrixResult, int length);//Multiplies two matrices in conventional way.
void FillMatrix(int** matrix1, int** matrix2, int length);//Fills Matrices with random numbers.
void PrintMatrix(int **MatrixA, int MatrixSize);//prints the Matrix content.

int main()
{
	int MatrixSize = 0;
	int** MatrixA;
	int** MatrixB;
	int** MatrixC;

	clock_t startTime_For_Normal_Multipilication;
	clock_t endTime_For_Normal_Multipilication;
	clock_t startTime_For_Strassen;
	clock_t endTime_For_Strassen;

	time_t start, end;

	srand(time(0));

	cout << "\nPlease Enter your Matrix Size(must be in a power of two(eg:32,64,512,..): ";
	cin >> MatrixSize;

	int N = MatrixSize;//for readiblity.

	MatrixA = new int *[MatrixSize];
	MatrixB = new int *[MatrixSize];
	MatrixC = new int *[MatrixSize];

	for (int i = 0; i < MatrixSize; i++) {
		MatrixA[i] = new int[MatrixSize];
		MatrixB[i] = new int[MatrixSize];
		MatrixC[i] = new int[MatrixSize];
	}

	FillMatrix(MatrixA, MatrixB, MatrixSize);

	// //*******************conventional multiplication test
	//     cout<<"Phase I started:  "<< (startTime_For_Normal_Multipilication = clock());

	//     MUL(MatrixA,MatrixB,MatrixC,MatrixSize);

	//     cout<<"\nPhase I ended: "<< (endTime_For_Normal_Multipilication = clock());

	//     cout<<"\nMatrix Result... \n";
	//     PrintMatrix(MatrixC,MatrixSize);

	//*******************Strassen multiplication test
	cout << "\nMultiplication started: " << (startTime_For_Strassen = clock());

	Strassen(N, MatrixA, MatrixB, MatrixC);

	cout << "\nMultiplication: " << (endTime_For_Strassen = clock());

	cout << "\nMatrix Result... \n";
	PrintMatrix(MatrixC, MatrixSize);

	// cout<<"Matrix size "<<MatrixSize;
	// cout<<"\nNormal mode "<<(endTime_For_Normal_Multipilication - startTime_For_Normal_Multipilication)<<" Clocks.."<<(endTime_For_Normal_Multipilication - startTime_For_Normal_Multipilication)/CLOCKS_PER_SEC<<" Sec";
	// cout<<"\nStrassen mode "<<(endTime_For_Strassen - startTime_For_Strassen)<<" Clocks.."<<(endTime_For_Strassen - startTime_For_Strassen)/CLOCKS_PER_SEC<<" Sec\n";
	system("Pause");
	return 0;
}

int Strassen(int N, int **MatrixA, int **MatrixB, int **MatrixC)
{
	int HalfSize = N / 2;
	int newSize = N / 2;
	if (N <= 64)//choosing the threshhold is extremely important, try N<=2 to see the result
		MUL(MatrixA, MatrixB, MatrixC, N);
	else {
		printf("\n%d", 1);
		int** A11;
		int** A12;
		int** A21;
		int** A22;
		int** B11;
		int** B12;
		int** B21;
		int** B22;
		int** C11;
		int** C12;
		int** C21;
		int** C22;
		int** P1;
		int** P2;
		int** P3;
		int** P4;
		int** P5;
		int** P6;
		int** P7;
		int** AResult;
		int** BResult;
		//making a 1 diminsional pointer based array.
		A11 = new int *[newSize];
		A12 = new int *[newSize];
		A21 = new int *[newSize];
		A22 = new int *[newSize];
		B11 = new int *[newSize];
		B12 = new int *[newSize];
		B21 = new int *[newSize];
		B22 = new int *[newSize];
		C11 = new int *[newSize];
		C12 = new int *[newSize];
		C21 = new int *[newSize];
		C22 = new int *[newSize];

		P1 = new int *[newSize];
		P2 = new int *[newSize];
		P3 = new int *[newSize];
		P4 = new int *[newSize];
		P5 = new int *[newSize];
		P6 = new int *[newSize];
		P7 = new int *[newSize];

		AResult = new int *[newSize];
		BResult = new int *[newSize];

		int newLength = newSize;

		//making that 1 diminsional pointer based array , a 2D pointer based array
		for (int i = 0; i < newSize; i++) {
			A11[i] = new int[newLength];
			A12[i] = new int[newLength];
			A21[i] = new int[newLength];
			A22[i] = new int[newLength];
			B11[i] = new int[newLength];
			B12[i] = new int[newLength];
			B21[i] = new int[newLength];
			B22[i] = new int[newLength];
			C11[i] = new int[newLength];
			C12[i] = new int[newLength];
			C21[i] = new int[newLength];
			C22[i] = new int[newLength];
			P1[i] = new int[newLength];
			P2[i] = new int[newLength];
			P3[i] = new int[newLength];
			P4[i] = new int[newLength];
			P5[i] = new int[newLength];
			P6[i] = new int[newLength];
			P7[i] = new int[newLength];
			AResult[i] = new int[newLength];
			BResult[i] = new int[newLength];
		}
		//splitting input Matrixes, into 4 submatrices each.
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				A11[i][j] = MatrixA[i][j];
				A12[i][j] = MatrixA[i][j + N / 2];
				A21[i][j] = MatrixA[i + N / 2][j];
				A22[i][j] = MatrixA[i + N / 2][j + N / 2];

				B11[i][j] = MatrixB[i][j];
				B12[i][j] = MatrixB[i][j + N / 2];
				B21[i][j] = MatrixB[i + N / 2][j];
				B22[i][j] = MatrixB[i + N / 2][j + N / 2];
			}
		}
		//here we calculate P1..P7 matrices .
		//P1[][]
		ADD(A11, A22, AResult, HalfSize);
		ADD(B11, B22, BResult, HalfSize);
		Strassen(HalfSize, AResult, BResult, P1); //now that we need to multiply this , we use the strassen itself .
												  //P2[][]
		ADD(A21, A22, AResult, HalfSize);              //P2=(A21+A22)B11
		Strassen(HalfSize, AResult, B11, P2);       //Mul(AResult,B11,P2);
													//P3[][]
		SUB(B12, B22, BResult, HalfSize);              //P3=A11(B12-B22)
		Strassen(HalfSize, A11, BResult, P3);       //Mul(A11,BResult,P3);
													//P4[][]
		SUB(B21, B11, BResult, HalfSize);           //P4=A22(B21-B11)
		Strassen(HalfSize, A22, BResult, P4);       //Mul(A22,BResult,P4);
													//P5[][]
		ADD(A11, A12, AResult, HalfSize);           //P5=(A11+A12)B22
		Strassen(HalfSize, AResult, B22, P5);       //Mul(AResult,B22,P5);
													//P6[][]
		SUB(A21, A11, AResult, HalfSize);
		ADD(B11, B12, BResult, HalfSize);             //P6=(A21-A11)(B11+B12)
		Strassen(HalfSize, AResult, BResult, P6);    //Mul(AResult,BResult,P6);
													 //P7[][]
		SUB(A12, A22, AResult, HalfSize);
		ADD(B21, B22, BResult, HalfSize);             //P7=(A12-A22)(B21+B22)
		Strassen(HalfSize, AResult, BResult, P7);     //Mul(AResult,BResult,P7);

													  //C11 = P1 + P4 - P5 + P7;
		ADD(P1, P4, AResult, HalfSize);
		SUB(P7, P5, BResult, HalfSize);
		ADD(AResult, BResult, C11, HalfSize);
		//C12 = P3 + P5;
		ADD(P3, P5, C12, HalfSize);
		//C21 = P2 + P4;
		ADD(P2, P4, C21, HalfSize);
		//C22 = P1 + P3 - P2 + P6;
		ADD(P1, P3, AResult, HalfSize);
		SUB(P6, P2, BResult, HalfSize);
		ADD(AResult, BResult, C22, HalfSize);

		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				MatrixC[i][j] = C11[i][j];
				MatrixC[i][j + N / 2] = C12[i][j];
				MatrixC[i + N / 2][j] = C21[i][j];
				MatrixC[i + N / 2][j + N / 2] = C22[i][j];
			}
		}
		printf("\n%d", 1);
		PrintMatrix(P1, newSize);
		// dont forget to free the space we alocated for matrices,
		for (int i = 0; i < newLength; i++) {
			delete[] A11[i]; delete[] A12[i]; delete[] A21[i];
			delete[] A22[i];
			delete[] B11[i]; delete[] B12[i]; delete[] B21[i];
			delete[] B22[i];
			delete[] C11[i]; delete[] C12[i]; delete[] C21[i];
			delete[] C22[i];
			delete[] P1[i]; delete[] P2[i]; delete[] P3[i]; delete[] P4[i];
			delete[] P5[i]; delete[] P6[i]; delete[] P7[i];
			delete[] AResult[i]; delete[] BResult[i];
		}
		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] P1; delete[] P2; delete[] P3; delete[] P4; delete[] P5;
		delete[] P6; delete[] P7;
		delete[] AResult;
		delete[] BResult;
	}//end of else
	return 0;
}

int ADD(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++) {
		for (int j = 0; j < MatrixSize; j++) {
			MatrixResult[i][j] = MatrixA[i][j] + MatrixB[i][j];
		}
	}
	return 0;
}

int SUB(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++) {
		for (int j = 0; j < MatrixSize; j++) {
			MatrixResult[i][j] = MatrixA[i][j] - MatrixB[i][j];
		}
	}
	return 0;
}

int MUL(int** MatrixA, int** MatrixB, int** MatrixResult, int MatrixSize)
{
	for (int i = 0; i<MatrixSize; i++) {
		for (int j = 0; j<MatrixSize; j++) {
			MatrixResult[i][j] = 0;
			for (int k = 0; k<MatrixSize; k++) {
				MatrixResult[i][j] = MatrixResult[i][j] + MatrixA[i][k] * MatrixB[k][j];
			}
		}
	}
	return 0;
}

void FillMatrix(int** MatrixA, int** MatrixB, int length)
{
	for (int row = 0; row<length; row++) {
		for (int column = 0; column<length; column++) {
			MatrixB[row][column] = (MatrixA[row][column] = rand() % 5);
			MatrixB[row][column] = (MatrixA[row][column] = 1);
		}
	}
}
void PrintMatrix(int **MatrixA, int MatrixSize)
{
	cout << endl;
	for (int row = 0; row<MatrixSize; row++) {
		for (int column = 0; column<MatrixSize; column++) {
			// cout<<MatrixA[row][column]<<"\t";
			cout << MatrixA[row][column] << "  ";
			if ((column + 1) % ((MatrixSize)) == 0)
				cout << endl;
		}
	}
	cout << endl;
}
