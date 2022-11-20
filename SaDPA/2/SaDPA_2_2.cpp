#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;
// Функция Selectioin sort
void Selection_sort(int n, int* massiv) {
    long long int c_comp = 0, c_perm = 0;
    cout << "Размерность проверяемого массива " << n;
    auto start_time = chrono :: steady_clock :: now();
    for (int i = 0; i < n - 1; i++) {                                                                // устанавливаем начальное значение минимального индекса 
            c_comp += 2;            
            int min_i = i;
        for (int j = i + 1; j < n; j++) {                                                            //  находим индекс минимального элемента 
            c_comp += 1;
            if (massiv[j] < massiv[min_i]) {
                c_comp += 1;
                c_perm += 1;
                min_i = j;
            }
        }                                                                                           // меняем значения местами
        swap(massiv[i], massiv[min_i]);
    }
    auto end_time = chrono :: steady_clock :: now();
    auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);
    if (n <= 10) {
        cout << '\n';
        for(int i = 0; i < n; i++) {
            cout << massiv[i] << ' ';
        }
    }
    cout << "\nC = " << c_comp << "; M = " << c_perm << "; C + M = " << c_comp + c_perm << endl;
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
}

// Генератор рандомных значений массива
int* mas_random_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		int num = rand() % 10 + 1;
        massiv[i] = num;
    }
    return massiv;
}

//функция для сортировки по возрастанию
int incr (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
 
//функция для сортировки по убыванию
int decr (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}


int main() {    
    const int n = 10;
    int massiv_[n];
    cout << "Введите значения массива через пробел \n";
    for(int i = 0; i < n; i++) {
        cin >> massiv_[i];
    }   
    cout << "Контрольные прогоны программы для рамера массива n = 10 \n(Элементы введены с клавиатуры) \n";
    qsort (massiv_, n, sizeof(int), decr);
    // for(int i = 0; i < n; i++) {
    //     cout << massiv_[i] << ' ';
    // }
    Selection_sort(n, massiv_);
    
    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000;
    int *massiv1 = mas_random_gen(n1);
    int *massiv2 = mas_random_gen(n2);
    int *massiv3 = mas_random_gen(n3);
    int *massiv4 = mas_random_gen(n4);
    int *massiv5 = mas_random_gen(n5);

    // Selection_sort(n1, massiv1);
    // Selection_sort(n2, massiv2);
    // Selection_sort(n3, massiv3);
    // Selection_sort(n4, massiv4);
    // Selection_sort(n5, massiv5);   

    qsort (massiv1, n1, sizeof(int), decr);
    Selection_sort(n1, massiv1);
    qsort (massiv2, n2, sizeof(int), decr);
    Selection_sort(n2, massiv2);
    qsort (massiv3, n3, sizeof(int), decr);
    Selection_sort(n3, massiv3);
    qsort (massiv4, n4, sizeof(int), decr);
    Selection_sort(n4, massiv4);
    qsort (massiv5, n5, sizeof(int), decr);
    Selection_sort(n5, massiv5);   
    return 0;
}

// void Insertion_sort(int n, int* massiv) {
//     long long int c_comp = 0, c_perm = 0;
//     cout << "Размерность проверяемого массива " << n;
//     auto start_time = chrono :: steady_clock :: now();
//     for(int i = 0; i < n; i++) {
//         c_comp += 1;                                
//         int key = massiv[i];
//         int j = i - 1;
//         while(j > 0 && massiv[j] > key) {
//             c_comp += 1;
//             c_perm += 1;
//             massiv[j + 1] = massiv[j];
//             j--;
//         }
//         massiv[j + 1] = key;
//     }
//     auto end_time = chrono :: steady_clock :: now();
//     auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);
//     if (n <= 10) {
//         cout << '\n';
//         for(int i = 0; i < n; i++) {
//             cout << massiv[i] << ' ';
//         }
//     }
//     cout << "\nC = " << c_comp << "; M = " << c_perm << "; C + M = " << c_comp + c_perm << endl;
//     cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
// }
