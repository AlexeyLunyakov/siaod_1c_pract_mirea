
nclude <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cmath>
using namespace std;
/*Сведения об успеваемости одного студента по одной дисциплине: 
Номер зачетной книжки, Шифр группы, Название дисциплины, Дата получения оценки, Оценка, Фамилия преподавателя*/
struct Student {
    int zachetka = 0;
    int groupcode = 0;
    string discipline = "";
    string date = "";
    int mark = 0;
    string teacher = "";
};

ifstream& operator >> (ifstream& in, Student& st) {
    in >> st.zachetka >> st.groupcode >> st.discipline >> st.date >> st.mark >> st.teacher;
    return in;
}

ofstream& operator<<(ofstream& out, Student& st) {
    out << st.zachetka << " " << st.groupcode << " " << st.discipline << " " << st.date << " " << st.mark << " " << st.teacher;
    return out;
}

void split(int p) { // разделение простое слияние
    ifstream a_file("a.txt");
    ofstream b_file("b.txt"), c_file("c.txt");
    Student x;
    a_file >> x;
    while(!a_file.eof()) {
        for (int i = 0; !a_file.eof() && i < p; i++) {
            b_file << x << endl;
            a_file >> x;
        }
        for (int i = 0; !a_file.eof() && i < p; i++) {
            c_file << x << endl;
            a_file >> x;
        }
    }
    a_file.close(); b_file.close(); c_file.close();
}

void merge(int p) { // слияние простое слияние
    ofstream a_file("a.txt");
    ifstream b_file("b.txt"), c_file("c.txt");
    Student x, y;
    b_file >> x;
    c_file >> y;
    while (!b_file.eof() && !c_file.eof()) {
        int i = 0, j = 0;
        while (!b_file.eof() && !c_file.eof() && i < p && j < p) {
            if (x.zachetka < y.zachetka) {
                a_file << x << endl;
                b_file >> x;
                i++;
            }
            else {
                a_file << y << endl;
                c_file >> y;
                j++;
            }
        }
        while (!b_file.eof() && i < p) {
            a_file << x << endl;
            b_file >> x;
            i++;
        }
        while (!c_file.eof() && j < p) {
            a_file << y << endl;
            c_file >> y;
            j++;
        }
    }
    while (!b_file.eof()) {
        a_file << x << endl;
        b_file >> x;
    }
    while (!c_file.eof()) {
        a_file << y << endl;
        c_file >> y;
    }
    a_file.close(); b_file.close(); c_file.close();
}


void merge_sort(int n /*количество записей*/) { // сортировка простого слияния
    for (int p = 1; p < n; p *= 2) {
        split(p);
        merge(p);
    }
}


bool nat_split() { // разделение естественного слияния
    ifstream a_file("a.txt");
    ofstream b_file("b.txt"), c_file("c.txt");
    Student x, y;
    bool c_empty = true;
    a_file >> y;
    while (!a_file.eof()) {
        do {
            x = y;
            b_file << x << endl;
            a_file >> y;
        } while (x.zachetka <= y.zachetka && !a_file.eof());
        if (a_file.eof()) {
            if (c_empty) {
                b_file << y << endl;
                a_file.close(); b_file.close(); c_file.close();
                return false;
            }
        }
        else {
            do {
                c_empty = false;
                x = y;
                c_file << x << endl;
                a_file >> y;
            } while (x.zachetka <= y.zachetka && !a_file.eof());
        }
    }
    a_file.close(); b_file.close(); c_file.close();
    return true;
}

void nat_merge() { // слияние естественного слияния
    ofstream a_file("a.txt");
    ifstream b_file("b.txt"), c_file("c.txt");
    Student x1, x2, y1, y2;
    b_file >> x1;
    c_file >> y1;
    while (!b_file.eof() && !c_file.eof()) {
        if (x1.zachetka < y1.zachetka) {
            a_file << x1 << endl;
            b_file >> x2;
            if (!b_file.eof() && x1.zachetka > x2.zachetka) {
                a_file << y1 << endl;
                c_file >> y2;
                while (!c_file.eof() && y1.zachetka <= y2.zachetka) {
                    y1 = y2;
                    a_file << y1 << endl;
                    c_file >> y2;
                }
                y1 = y2;
            }
            x1 = x2;
        }
        else {
            a_file << y1 << endl;
            c_file >> y2;
            if (!c_file.eof() && y1.zachetka > y2.zachetka) {
                a_file << x1 << endl;
                b_file >> x2;
                while (!b_file.eof() && x1.zachetka < x2.zachetka) {
                    x1 = x2;
                    a_file << x1 << endl;
                    b_file >> x2;
                }
                x1 = x2;
            }
            y1 = y2;

        }
    }
    while (!b_file.eof()) {
        a_file << x1 << endl;
        b_file >> x1;
    }
    while (!c_file.eof()) {
        a_file << y1 << endl;
        c_file >> y1;
    }
    a_file.close(); b_file.close(); c_file.close();
}

void nat_merge_sort() { // сортировка естесвенного слияния
    while (nat_split()) {
        nat_merge();
    }
}

int main() {
    int n = 32;
    auto start_time = chrono :: steady_clock :: now();
    //merge_sort(n);
    nat_merge_sort();
    auto end_time = chrono :: steady_clock :: now();
    auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
}