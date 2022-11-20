#include <iostream>
/* #include <conio.h>
using namespace std;
void Get(int *mas,int x){
    cout<<endl<<endl;
    for (int i=0; i<x;i++){
        if (i==8 or i==16 or i==2)
            cout<<" | ";
        cout<<mas[i]<<"("<<i<<")"<<'\t';
        if (i==12 or i==6 or i==3 )
            cout<<" | ";}
    cout<<endl;
}
void Initialize (int n, int size, int small, int *x, int *tree) {
    int i, j, k;
    for (i = 0; i < n; i++)
        tree [size + i ] = x[i];
    //Get(tree,32);
    for (i = size + n; i < 2 * size ; i++)
        tree[i] = small;
    //Get(tree,32);
    for (j = size; j < 2*size ; j+=2) {
        if (tree[j] >= tree[j+1]){
            tree[j/2] = j;
        }
        else {
            tree[j/2] = j+1;
        }
    }
    k = size / 2;
    //Get(tree,32);

    while (k > 0) {

        for (j = k; j < 2*k - 1; j+=2)
            if (tree[tree[j]] >= tree[tree[j + 1]]) {
                tree[j/2] = tree[j];
            }
            else {
                tree[j/2] = tree[j+1];
            }

        k/=2;
    }
    //Get(tree,32);

}

//переупорядочивание вдоль пути от i к 1
void ReadJust(int i, int *tree) {
    //Get(tree,32);
    int j;//помещаем индекс соперника в ячейку "победителя"( условно в 12)
    if (i % 2==0) {
        tree[i/2] = i + 1;
    }
    else {
        tree[i/2] = i - 1;
    }
    cout<<endl<<"FIN"<<endl;
    //Get(tree,32);

    i = i / 2;//12

    while(i > 1) {
        cout<<endl<<i<<endl;
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
        cout<<endl<<"FIN"<<endl;
        //Get(tree,32);
    }

}

void Tourtament (int n, int *massiv) {
    int i, k, size, small, tree[128];
    size = 1; small = -32768;
    while (size < n) {
        size *= 2;
    }

    Initialize (n, size, small, massiv, tree);

    for (k = n-1; k > 0; k--) {
        cout<<endl<<k<<endl;
        i = tree[1];
        massiv[k] = tree[i];
        tree[i] = small;
        //Get(massiv,n);
        ReadJust (i, tree);
    }

    massiv[0] = tree[tree[1]];

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
    system("chcp 65001");
    int massiv[] = { 45, 23, 12, 34, 1, 42, 11, 5, 67, 36}, n = 10;
    mas_random_gen(n);

    cout<<"До сортировки: \n";

    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
    Tourtament (n, massiv);

    cout << "\n\nПосле сортировки : \n" ;

    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
}*/

#include <iostream>
// #include <conio.h>
using namespace std;
void Get(int *mas,int x){
    cout<<endl<<endl;
    for (int i=0; i<x;i++){
        if (i==8 or i==16 or i==2)
            cout<<" | ";
        cout<<mas[i]<<"("<<i<<")"<<'\t';
        if (i==12 or i==6 or i==3 )
            cout<<" | ";}
    cout<<endl;
}
void Initialize (int n, int size, int small, int *x, long long *tree) {
    int i, j, k;
    for (i = 0; i < n; i++)
        tree [size + i ] = x[i];
    //Get(tree,32);
    for (int i=size+n;i<size*2;i++)
        tree[i] = small;
    //Get(tree,32);
    for (j = size; j < 2*size ; j+=2) {
        if (tree[j] >= tree[j+1]){
            tree[j/2] = j;
        }
        else {
            tree[j/2] = j+1;
        }
    }
    k = size / 2;
    //Get(tree,32);

    while (k > 0) {

        for (j = k; j < 2*k - 1; j+=2)
            if (tree[tree[j]] >= tree[tree[j + 1]]) {
                tree[j/2] = tree[j];
            }
            else {
                tree[j/2] = tree[j+1];
            }

        k/=2;
    }
    //Get(tree,32);

}

//переупорядочивание вдоль пути от i к 1
void ReadJust(int i, long long  *tree) {
    //Get(tree,32);
    int j;//помещаем индекс соперника в ячейку "победителя"( условно в 12)
    if (i % 2==0) {
        tree[i/2] = i + 1;
    }
    else {
        tree[i/2] = i - 1;
    }
    //cout<<endl<<"FIN"<<endl;
    //Get(tree,32);

    i = i / 2;//12

    while(i > 1) {
        //cout<<endl<<i<<endl;
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
        //cout<<endl<<"FIN"<<endl;
        //Get(tree,32);
    }

}

void Tourtament (int n, int *massiv) {
    cout<<"sf";
    int i, k, size, small;
    size = 1; small = -32768;
    while (size < n) {
        size *= 2;
    }
    long long tree[size*2];
    cout<<"cchek";

    Initialize (n, size, small, massiv, tree);
    cout<<"CHEk";

    for (k = n-1; k > 0; k--) {
        //cout<<endl<<k<<endl;
        i = tree[1];
        //cout<<endl<<i<<endl;
        massiv[k] = tree[i];
        tree[i] = small;
        //Get(massiv,n);
        ReadJust (i, tree);
    }

    massiv[0] = tree[tree[1]];

}
int* mas_random_gen(int n) {
    int* massiv = new int[n];
    for (int i = 0; i < n; i++){
        int num = rand() % 100 + 1;
        massiv[i] = num;
    }
    return massiv;
}

void merge(int* osnova, int* left, int* right, int n,int* per,int *srav)
{
    int leftind = 0, rightindex = 0,osnovaind = 0;
    int mid = n / 2;
    *per+=1;
    *srav+=1;

    while (leftind < mid and rightindex < (n-mid)) {
        *srav+=1;
        if (left[leftind] <= right[rightindex]) {
            *srav+=1;
            *per+=2;
            osnova[osnovaind] = left[leftind];
            leftind++;
        }
        else {
            *srav+=1;
            *per+=2;
            osnova[osnovaind] = right[rightindex];
            rightindex++;
        }
        *per+=1;
        osnovaind++;
    }
    *srav+=1;
    while (leftind < mid) {
        *srav+=1;
        *per+=3;
        osnova[osnovaind] = left[leftind ];
        leftind++;
        osnovaind++;
    }
    *srav+=1;
    while (rightindex < (n-mid)) {
        *srav+=1;
        *per+=3;
        osnova[osnovaind] = right[rightindex];
        rightindex++;
        osnovaind++;
    }
    cout<<endl<<*srav+*per<<endl;
}
void MergeSort(int* array, int n,int *per,int *srav) {

    int start = clock();
    if (n < 2) {
        return;
    }
    int mid = n / 2;
    int* left = new int[mid];
    int* right = new int[n - mid];
    for (int i = 0; i < mid; i++)
        left[i] = array[i];
    for (int i = mid; i < n; i++)
        right[i - mid] = array[i];
    MergeSort(left, mid,per,srav);
    MergeSort(right, n - mid,per,srav);
    *per=0,*srav=0;
    merge(array, left, right, n,per,srav);
}



int main () {
    system("chcp 65001");
    int pt=0,sv=0;
    int *per=&pt;
    int *srav=&sv;
    int massiv[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    //int *massiv=mas_random_gen(n);

    cout<<"До сортировки: \n";

    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
    cout<<"SAD";
    //Tourtament (n, massiv);
    MergeSort(massiv,n,per,srav);

    cout << "\n\nПосле сортировки : \n" ;

    for (int i=0; i < n; i++) {
        cout << massiv[i] << " ";
    }
}