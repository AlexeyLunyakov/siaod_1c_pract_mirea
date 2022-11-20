#include <iostream>
using namespace std;
void quicksort(int *mas, int first, int last)
{
    int mid, count;
    int f = first, l = last;
    mid = mas[(f + l) / 2]; //вычисление опорного элемента
    do
    {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        if (f <= l) //перестановка элементов
        {
            count = mas[f];
            mas[f] = mas[l];
            mas[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
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
int main(){
    int mas[10] = { 98, 2, 54, 65, 3, -150, 8, 11, 12, 76 };
    int n = 10;
    quicksort(mas, 0, n-1);
    for (auto&k : mas){
        cout << k << " ";
    }
    cout << endl;
    return 0;
}