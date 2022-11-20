include <iostream>
#include <algorithm>
using namespace std;

void algorithm_1(int* mas1, int& length_, int key, int& c_perm, int& c_comp){
	int i = 0;
	c_comp = 1;
	c_perm = 1;
	while (i < length_) {
		c_comp += 2; // while
		if (mas1[i] == key){
			c_comp += 1; // if
			for (int j = i; j < (length_ - 1); j++){
				mas1[j] = mas1[j + 1];
				c_comp += 1; // for
				c_perm += 1; 
			}
			length_ = length_ - 1;
			c_perm += 1;
		}
		else{
			i = i + 1;
			c_perm++;
		}
	}
}

void algorithm_2(int* mas2, int& length_, int key, int& c_perm, int& c_comp){
	int j = 0;
	c_comp = 1;
	c_perm = 0;
	for (int i = 0; i < length_; i++){
		c_comp += 1;
        mas2[j] = mas2[i];
		c_perm += 1;
        if (mas2[i] != key)
			c_comp += 1;
			j = j + 1;
			c_perm += 1;
	}
	length_ = j;
}

int main(){
	srand(time(NULL));
    int n, key; 
    cout << "N = "; cin >> n;
    cout << "key = "; cin >> key;
    int* mas1 = new int [n] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //{0}; 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
    int* mas2 = new int [n] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // for (int i = 0; i < n; i++){
	// 	int num = rand() % 10 + 1;
    //     mas1[i] = mas2[i] = num;
    // }
    int length_1 = n; int length_2 = n;
	cout << "\nМассив до преобразований: \n";
	for (int i = 0; i < n - 4; i += 5) {
        cout << "x[" << i << "] = " << mas1[i] << '\t' << "x[" << i+1 << "] = " << mas1[i + 1] << 
		 '\t' << "x[" << i + 2 << "] = " <<  mas1[i + 2] << '\t' << "x[" << i + 3 << "] = " <<
		 mas1[i + 3] << '\t' << "x[" << i + 4 << "] = " << mas1[i + 4] <<  "\n";
    }
	int c_perm = 0; int c_comp = 0;
	algorithm_1(mas1, length_1, key, c_perm, c_comp);
	cout << "\nПреобразованный массив\n";
	if (length_1 == 0){
		cout << "\nВсе элементы были удалены\n";
	}
	for (int i = 0; i < length_1 + (length_1 % 5); i+=5){
		if (i < length_1){
			cout << "x[" << i << "] = " << mas1[i] <<'\t';
		}
		if (i + 1 < length_1){
			cout << "x[" << i+1 << "] = " << mas1[i + 1] << '\t'; 
		}
		if (i + 2 < length_1){
			cout << "x[" << i + 2 << "] = " <<  mas1[i + 2] << '\t';
		}
		if (i + 3 < length_1){
			cout << "x[" << i + 3 << "] = " << mas1[i + 3] << '\t';
		}
		if (i + 4 < length_1){
			cout << "x[" << i + 4 << "] = " << mas1[i + 4] << '\t';
		}
		cout << endl;
    }
	cout << "\nКоличество перестановок в алгоритме 1: " << c_perm;
	cout << "\nКоличество сравнений в алгоритме 1: " << c_comp << "\n\n";

	c_comp = c_perm = 0;
    algorithm_2(mas2, length_2, key, c_perm, c_comp);
	for (int i = 0; i < length_2 + (length_2 % 5); i+=5){
		if (i < length_2){
			cout << "x[" << i << "] = " << mas2[i] <<'\t';
		}
		if (i + 1 < length_2){
			cout << "x[" << i+1 << "] = " << mas2[i + 1] << '\t'; 
		}
		if (i + 2 < length_2){
			cout << "x[" << i + 2 << "] = " <<  mas2[i + 2] << '\t';
		}
		if (i + 3 < length_2){
			cout << "x[" << i + 3 << "] = " << mas2[i + 3] << '\t';
		}
		if (i + 4 < length_2){
			cout << "x[" << i + 4 << "] = " << mas2[i + 4] << '\t';
		}
		cout << endl;
    }
	cout << "\nКоличество перестановок в алгоритме 2: " << c_perm;
	cout << "\nКоличество сравнений в алгоритме 2: " << c_comp << "\n\n";
	return 0;
}