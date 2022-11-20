#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

// Функция для преобразования в сортирующее дерево с корневым узлом i, что является индексом в massiv[]

void Tour_sort_help(int n, int* massiv, int i) {
    int largest = i;   
    // Инициализируем наибольший элемент как текущий
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше текущего
    if (l < n && massiv[l] > massiv[largest]) {
        largest = l;
    }
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && massiv[r] > massiv[largest]) {
        largest = r;
    }
    // Если самый большой элемент не текущий
    if (largest != i) {
        swap(massiv[i], massiv[largest]);
    // Рекурсивно преобразуем в сортирующее дерево
        Tour_sort_help(n, massiv, largest);
    }
}

// Основная функция, выполняющая сортировку
void Main_Tour_sort(int n, int* massiv) {

    long long int c_comp = 0, c_perm = 0;
    cout << "Размерность проверяемого массива " << n;
    auto start_time = chrono :: steady_clock :: now();

    // Построение дерева (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        Tour_sort_help(n, massiv, i);

    // Один за другим извлекаем элементы из дерева
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий элемент в конец
        swap(massiv[0], massiv[i]);

        // вызываем процедуру Tour_sort_help на уменьшенном дереве
        Tour_sort_help(i, massiv, 0);
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

//функция генерации массива 
int* mas_random_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		int num = rand() % 10 + 1;
        massiv[i] = num;
    }
    return massiv;
}
//функция для создания возрастающего массива 
int* mas_incr_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		massiv[i] = i;
    }
    return massiv;
}
//функция для создания убывающего массива 
int* mas_decr_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		massiv[i] = n - i - 1;
    }
    return massiv;
}

int main() {    
    const int n = 10;
    int massiv_[n];
    cout << "Введите значения массива через пробел \n";
    for(int i = 0; i < n; i++) {
        cin >> massiv_[i];
    }   
    cout << "Контрольные прогоны программы для рамера массива n = 10 \n(Элементы введены с клавиатуры) \n";
    //int *massiv = mas_incr_gen(n1);
    // for(int i = 0; i < n; i++) {
    //     cout << massiv_[i] << ' ';
    // }
    Main_Tour_sort(n, massiv_);
    
    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000;
    int *massiv1 = mas_random_gen(n1);
    int *massiv2 = mas_random_gen(n2);
    int *massiv3 = mas_random_gen(n3);
    int *massiv4 = mas_random_gen(n4);
    int *massiv5 = mas_random_gen(n5);

    Main_Tour_sort(n1, massiv1);
    Main_Tour_sort(n2, massiv2);
    Main_Tour_sort(n3, massiv3);
    Main_Tour_sort(n4, massiv4);
    Main_Tour_sort(n5, massiv5);   


    return 0;
}
