/*
Eduardo Aguilar Leal A01193626
Aglahir Jimenez Flores A01364026
*/

#include <iostream>
#include <vector>

using namespace std;

int numMult = 0;

//printMatrix
void printMatrix(vector< vector<int> > matrix){
  int n = matrix.size();
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

/*
fillEmptyVector

fills a (matrix)vector with 0s with the corresponding size

params:
size: size of the desired matrix

return:
vector< vector<int> >: result vector/matrix
*/
vector< vector<int> > fillEmptyVector(int size){
  vector< vector<int> > matrix;

  for (int i = 0; i < size; i++){
    vector<int> aux;
    for(int j = 0; j < size; j++){
      aux.push_back(0);
    }
    matrix.push_back(aux);
  }
  return matrix;
}

/*
fillInitialVector

recieves input from the user to fill in a matrix/vector

params:
n: size of the desired matrix

return:
vector< vector<int> >: result vector/matrix
*/
vector< vector<int> > fillInitialVector(int n){
  vector< vector<int> > matrix;
  for(int i = 0; i < n; i++){
    vector<int> aux;
    for(int j = 0; j < n; j++){
      int num;
      cin >> num;
      aux.push_back(num);
    }
    matrix.push_back(aux);
  }
  return matrix;
}

/*
addMatrixes

adds two matrixes

params:
  A: matrix
  B: matrix

return:
  vector< vector<int> >: added matrix
*/
vector< vector <int> > addMatrixes(vector< vector<int> > A, vector< vector<int> > B){
  int n = A.size();
  vector< vector<int> > matrix = fillEmptyVector(n);

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      matrix[i][j] = A[i][j] + B[i][j];
    }
  }
  return matrix;
}

/*
subtractMatrixes

subtracts two matrixes

params:
  A: matrix
  B: matrix

return:
  vector< vector<int> >: subtracted matrix result
*/
vector< vector<int> > subtractMatrixes(vector< vector<int> > A, vector< vector<int> > B){
  int n = A.size();
  vector< vector<int> > matrix = fillEmptyVector(n);

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      matrix[i][j] = A[i][j] - B[i][j];
    }
  }
  return matrix;
}

/*
dotMatrixes

gets the dot product of 2 matrixes

params:
  A: matrix
  B: matrix

return:
  vector< vector<int> >: multiplied matrix result
*/
vector< vector<int> > dotMatrixes(vector< vector<int> > A, vector< vector<int> > B){
  int n = A.size();
  vector< vector<int> > matrix = fillEmptyVector(n);

  for(int row_in_A = 0; row_in_A < n; row_in_A++){
    for(int col_in_B = 0; col_in_B < n; col_in_B++){
      int product = 0;
      int sum = 0;
      //traverse row/col
      for(int i = 0; i < n; i++){
        product = A[row_in_A][i] * B[i][col_in_B];
        sum += product;

        numMult++;
      }
      matrix[row_in_A][col_in_B] = sum;
    }
  }
  return matrix;
}

//StrasenFunction
//shit logic
vector< vector <int> > strassen(vector< vector<int> > A, vector< vector<int> > B){
  int n = A.size();

  //if i can't recursively divide more
  if(n == 2){
    return dotMatrixes(A, B);
  }else{
    vector< vector<int> > matrix = fillEmptyVector(n);

    vector< vector<int> > A_11 = fillEmptyVector(n/2);
    vector< vector<int> > A_12 = fillEmptyVector(n/2);
    vector< vector<int> > A_21 = fillEmptyVector(n/2);
    vector< vector<int> > A_22 = fillEmptyVector(n/2);
    vector< vector<int> > B_11 = fillEmptyVector(n/2);
    vector< vector<int> > B_12 = fillEmptyVector(n/2);
    vector< vector<int> > B_21 = fillEmptyVector(n/2);
    vector< vector<int> > B_22 = fillEmptyVector(n/2);

    for(int i = 0; i < n/2; i++){
      for(int j = 0; j < n/2; j++){
        A_11[i][j] = A[i][j];
        A_12[i][j] = A[i][j+n/2];
        A_21[i][j] = A[i+n/2][j];
        A_22[i][j] = A[i+n/2][j+n/2];

        B_11[i][j] = B[i][j];
        B_12[i][j] = B[i][j+n/2];
        B_21[i][j] = B[i+n/2][j];
        B_22[i][j] = B[i+n/2][j+n/2];
      }
    }

    //GET M matrixes
    //get M1 := (A_1,1 + A_2,2) * (B_1,1 + B_2,2)
    vector< vector<int> > M1 = strassen(addMatrixes(A_11, A_22),addMatrixes(B_11, B_22));

    //get M2 := (A_2,1 + A_2,2) * B_1,1
    vector< vector<int> > M2 = strassen(addMatrixes(A_21, A_22), B_11);

    //get M3 := A_1,1 * (B_1,2 - B_2,2)
    vector< vector<int> > M3 = strassen(A_11, subtractMatrixes(B_12, B_22));

    //get M4 := A_2,2 * (B_2,1 - B_1,1)
    vector< vector<int> > M4 = strassen(A_22, subtractMatrixes(B_21,B_11));

    //get M5 := (A_1,1 + A_1,2) * B_2,2
    vector< vector<int> > M5 = strassen(addMatrixes(A_11, A_12), B_22);

    //get M6 := (A_2,1 - A_1,1) * (B_1,1 + B_1,2)
    vector< vector<int> > M6 = strassen(subtractMatrixes(A_21, A_11), addMatrixes(B_11, B_12));

    //get M7 := (A_1,2 - A_2,2) * (B_2,1 + B_2,2)
    vector< vector<int> > M7 = strassen(subtractMatrixes(A_12, A_22), addMatrixes(B_21, B_22));

    //GET C matrixes
    //get C_1,1 := M1 + M4 - M5 + M7
    vector< vector<int> > C_11 = addMatrixes(addMatrixes(M1, subtractMatrixes(M4, M5)), M7);

    //get C_1,2 := M3 + M5
    vector< vector<int> > C_12 = addMatrixes(M3, M5);

    //get C_2,1 := M2 + M4
    vector< vector<int> > C_21 = addMatrixes(M2, M4);

    //get C_2,2 := M1 - M2 + M3 + M6
    vector< vector<int> > C_22 = addMatrixes(subtractMatrixes(M1, M2),addMatrixes(M3, M6));


    for(int i = 0; i < n/2; i++){
      for(int j = 0; j < n/2; j++){
        matrix[i][j] = C_11[i][j];
        matrix[i][j+n/2] = C_12[i][j];
        matrix[i+n/2][j] = C_21[i][j];
        matrix[i+n/2][j+n/2] = C_22[i][j];
      }
    }

    return matrix;
  }
}

int main() {

  int n;
  cin >> n;

  vector< vector<int> > A = fillInitialVector(n);
  vector< vector<int> > B = fillInitialVector(n);

  //Normal multiplication (brute force) ==>
  numMult = 0;
  vector< vector<int> > matrixNorm = dotMatrixes(A, B);
  int numMultNorm = numMult;
  //<==

  //Strasse multiplciation ==>
  numMult = 0;
  vector< vector <int> > matrixStrassen = fillEmptyVector(n);
  matrixStrassen = strassen(A, B);
  int numMultStrasse = numMult;
  //<==

  //Print
  cout << "Traditional:" << endl;
  printMatrix(matrixNorm);
  cout << "Scalar Multiplications: " << numMultNorm << endl;
  cout << endl;
  cout << "Strasse:" << endl;
  printMatrix(matrixStrassen);
  cout << "Scalar Multiplications: " << numMultStrasse<< endl;
  //<==

  return 0;
}

/*
Sample input

4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1


Sample Output

Traditional:
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
Scalar Multiplications: 64

Strasse:
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
Scalar Multiplications: 56
*/
