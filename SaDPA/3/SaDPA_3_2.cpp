nclude <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
using namespace std;

void qsortRecursive(int *massiv, int size, long long int* c_comp, long long int* c_perm) {
    //Указатели начала и конеца массива
    int i = 0;
    int j = size - 1;
    //Опорный элемент элемент массива (середина)
    int mid = massiv[size / 2];
    *c_perm += 1;
    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(massiv[i] < mid) {
            i++;
            *c_comp += 1;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(massiv[j] > mid) {
            j--;
            *c_comp += 1;
        }
        //Оставшиеся - меняем местами
        if (i <= j) {
            swap(massiv[i], massiv[j]);
            *c_perm += 1;
            *c_comp += 1;
            i++;
            j--;
        }
        *c_comp += 1;
    } while (i <= j);

    //Рекурсивный вызов, если осталось, что сортировать
    if(j > 0) {
        //"Слева"
        qsortRecursive(massiv, j + 1,  c_comp, c_perm);
    }
    if (i < size) {
        //"Справа"
        qsortRecursive(&massiv[i], size - i, c_comp, c_perm);
    }
}

void help_sort(int* massiv, int n) {
    long long int c_comp = 1, c_perm = 1; 
    cout << "Размерность проверяемого массива " << n << endl;

    auto start_time = chrono :: steady_clock :: now();
    qsortRecursive(massiv, n,  &c_comp, &c_perm);
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

//функция генерации массива 
int* mas_random_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		int num = rand() % 10 + 1;
        massiv[i] = num;
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
    help_sort(massiv_, n);


    const int n1 = 100, n2 = 1000, n3 = 10000, n4 = 100000, n5 = 1000000;
    int *massiv1 = mas_random_gen(n1);
    int *massiv2 = mas_random_gen(n2);
    int *massiv3 = mas_random_gen(n3);
    int *massiv4 = mas_random_gen(n4);
    int *massiv5 = mas_random_gen(n5);

    help_sort(massiv1, n1);
    help_sort(massiv2, n2);
    help_sort(massiv3, n3);
    help_sort(massiv4, n4);
    help_sort(massiv5, n5);   


    return 0;
}
