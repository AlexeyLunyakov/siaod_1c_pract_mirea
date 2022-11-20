#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

// Заполенение элементами массива узлы дерева, дополнение элементов сверх малым числом (для отриц. элементов)
// Вывление наибольшего из элементов
void Initialize (int n, int size, int sm_number, int *massiv, long int *tree, long long int* c_comp, long long int* c_perm) { 
    int i, j, k;
    for (i = 1; i <= n; i++) 
        tree [size + i - 1] = massiv[i];
        *c_comp += 1;
    for (i = size + n; i <= 2 * size - 1; i++) 
        tree[i] = sm_number;
        *c_comp += 1;
    for (j = size; j <= 2*size - 1; j+=2) { 
        *c_comp += 2;
        if (tree[j] >= tree[j+1]){ 
            tree[j/2] = j;
            *c_perm += 1; 
        }
        else {
            tree[j/2] = j+1;
            *c_perm += 1;
        }
    }
    k = size / 2;

    while (k > 0) {
        *c_comp += 2;
        for (j = k; j <= 2*k - 1; j+=2) {
            if (tree[tree[j]] >= tree[tree[j + 1]]) {
                tree[j/2] = tree[j];
                *c_perm += 1;
            }
            else {
                tree[j/2] = tree[j+1];
                *c_perm += 1;
            }
        }
        k/=2;
    }
}

// Переупорядочивание вдоль пути от i к 1
void ReadJust(int i, long int *tree, long long int* c_comp, long long int* c_perm) {
    int j;
    if (i % 2 == 0) {
        tree[i/2] = i + 1;
        *c_perm += 1;
    }
    else {
        tree[i/2] = i - 1;
        *c_perm += 1;
    }
    i = i / 2;
    while (i > 1) {
        *c_comp += 3;
        if (i % 2==0){ // В зависимости от четности выбирается положение
            j = i + 1;
        }
        else {
            j = i - 1;
        }
        // (сравнивается элемент с поставленным)
        if (tree[tree[i]] > tree[tree[j]]){
            tree[i/2] = tree[i];
            *c_perm += 1;
        }
        else {
            tree[i/2] = tree[j];
            *c_perm += 1;
        }
        i = i / 2;
    }

}

void Main_Tour_sort(int n, int *massiv) { 

    long long int c_comp = 0, c_perm = 0;
    cout << "Размерность проверяемого массива " << n;

    auto start_time = chrono :: steady_clock :: now();

    int i, k, size, sm_number;
    long int *tree = new long int[n*4]; // Выделение памяти для массива "дерева"

    for (int i = 0; i < n*2; i++) {
        tree[i] = 0;                    // заполение нулями
    }
    size = 1; sm_number = -99999;
    while (size < n) {
        size *= 2;              //  В общем случае исходный массив состоит из n > size (= 2^k) чисел 
                                // и количество его элементов n дополняется до 2^k добавлением достаточно малых чисел (sm_number = -99999)
    }

    Initialize (n, size, sm_number, massiv, tree, &c_comp, &c_perm);
    long long int sum_comp = 0, sum_perm = 0;
    sum_comp += c_comp;
    sum_perm += c_perm;    
    for (k = n; k >= 0; k--) { 
        i = tree[1];            // Индекс наибольшего числа
        massiv[k] = tree[i];    // Запись наибольшего числа в массив
        tree[i] = sm_number;    // Замена наибольшего достаточно малым числом
        ReadJust (i, tree, &c_comp, &c_perm);     // Переупорядочивание вдоль пути от i к 1
    }
    sum_comp += c_comp;
    sum_perm += c_perm;    
    massiv[0] = tree[tree[1]]; 

    auto end_time = chrono :: steady_clock :: now();
    auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);

    if (n <= 10) {
        cout << '\n';
        for(int i = 1; i <= n; i++) {
            cout << massiv[i] << ' ';
        }
    }

    cout << "\nC = " << sum_comp << "; M = " << sum_perm << "; C + M = " << sum_comp + sum_perm << endl;
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
    delete [] tree;
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
    int massiv_[n+1];
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
    
    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000; // ОТРАБАТЫВАЕТ НА 512, ДАЛЬШЕ НЕ ИДЕТ
    int *massiv1 = mas_decr_gen(n1+1);
    int *massiv2 = mas_decr_gen(n2+1);
    int *massiv3 = mas_decr_gen(n3+1);
    int *massiv4 = mas_decr_gen(n4+1);
    int *massiv5 = mas_decr_gen(n5+1);

    Main_Tour_sort(n1, massiv1);
    Main_Tour_sort(n2, massiv2);
    Main_Tour_sort(n3, massiv3);
    Main_Tour_sort(n4, massiv4);
    Main_Tour_sort(n5, massiv5);   


    return 0;
}
