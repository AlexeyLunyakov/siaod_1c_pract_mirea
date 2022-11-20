#include <iostream>
#include <algorithm>
using namespace std;

void Matrix_x_vector(int n, int m, int **matrix, int *vektor, int *res)
{
  for (int i = 0; i < n; i++) {
    int temp = 0;
    for (int j = 0; j < m; j++) {
      temp += (matrix[i][j] * vektor[j]);
    }
    res[i] = temp;
  }
}

int main(){
	srand(time(0));
	int n, m;
	cin >> n >> m;
	//Динамическая матрица
	int **matrix = new int*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int [m];
	}
	//Заполнение матрицы случайными числами
	for (int c_row = 0; c_row < n; c_row++) {
		for (int c_col = 0; c_col < m; c_col++) {
			matrix[c_row][c_col] = (rand() % 10 + 1);
		}
	}
	//Векторы
	int *vektor = new int[m];
	int *res = new int[n];
	//Заполнение вектора случайными числами
	for (int c_row = 0; c_row < m; c_row++) {
		vektor[c_row] = (rand() % 10 + 1);
	}
	cout << "\nМатрица до умножения \n";
	for (int c_row = 0; c_row < n; c_row++) {
		for (int c_col = 0; c_col < m; c_col++) {
			cout << matrix[c_row][c_col] << ' ';
		}
		cout << endl;
	}
	cout << "\nВектор до умножения \n";
	for (int c_row = 0; c_row < m; c_row++) {
		cout << vektor[c_row] << '\n'; 
	}
	Matrix_x_vector(n, m, matrix, vektor, res);
	cout << "\nРезультат умножения \n";
	for (int x = 0; x < n; x++) {
		cout << res[x] << '\n';
	}
	// Очистка памяти
	for (int i = 0; i < n; i++) {
		delete [] matrix[i];
	}
	delete [] vektor;
	delete [] res;
	return 0;
}