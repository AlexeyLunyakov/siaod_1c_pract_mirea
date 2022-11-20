#include <iostream>
// #include <conio.h>
using namespace std;

void Initialize (int n, int size, int small, int *x, int *tree) { 
    int i, j, k;
    for (i = 0; i <= n; i++) 
        tree [size + i - 1] = x[i];
    for (i = size + n; i <= 2 * size - 1; i++) 
        tree[i] = small;
    for (j = size; j <= 2*size - 1; j+=2) { 
        if (tree[j] >= tree[j+1]){ 
            tree[j/2] = j; 
        }
        else {
            tree[j/2] = j+1;
        }
    }
    k = size / 2;

    while (k > 0) {
        for (j = k; j <= 2*k - 1; j+=2)
        if (tree[tree[j]] >= tree[tree[j + 1]]) {
            tree[j/2] = tree[j];
        }
        else {
            tree[j/2] = tree[j+1];
        }

        k/=2;
    }

}

//переупорядочивание вдоль пути от i к 1
void ReadJust(int i, int *tree) {
    int j;
    if (i % 2==0) {
        tree[i/2] = i + 1;
    }
    else {
        tree[i/2] = i - 1;
    }
    
    i = i / 2;
    
    while(i > 1) {
        if (i % 2==0){ 
            j = i + 1;
        }
        else {
            j = i - 1;
        }

        if (tree[tree[i]] > tree[tree[j]]){
            tree[i/2] = tree[i];
        }
        else {
            tree[i/2] = tree[j];
        }
        
        i = i / 2;
    }

}

void Tourtament (int n, int *massiv) { 
    int i, k, size, small, tree[1023];
    size = 1; small = -32768;
    while (size < n) {
        size *= 2;
    }
    
    Initialize (n, size, small, massiv, tree);

    for (k = n; k > 1; k--) { 
        i = tree[1];
        massiv[k] = tree[i];
        tree[i] = small;
        ReadJust (i, tree); 
    }

    massiv[1] = tree[tree[1]];

}
int* mas_random_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
		int num = rand() % 10 + 1;
        massiv[i] = num;
    }
    return massiv;
}
int main () { 
    int massiv[] = { 45, 23, 12, 34, 1, 42, 11, 5, 67, 36, 12, -100, 5, 8, 99, 15 }, n = 16;

    cout<<"До сортировки: \n";

    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
    Tourtament (n, massiv);
    
    cout << "\n\nПосле сортировки : \n" ;
    
    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
}