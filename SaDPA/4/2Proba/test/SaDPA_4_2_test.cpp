#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cmath>
using namespace std;
/*Сведения об успеваемости одного студента по одной дисциплине: 
Номер зачетной книжки, Шифр группы, Название дисциплины, Дата получения оценки, Оценка, Фамилия преподавателя*/
struct student {
    int id = 0;

    string surname = "";
    string name = "";
    string birthday = "";
    string phone = "";
    string date = "";
};

ifstream& operator >> (ifstream& in, student& st) {
    in >> st.id >> st.surname >> st.name >> st.birthday >> st.phone >> st.date;
    return in;
}

ofstream& operator<<(ofstream& out, student& st) {
    out << st.id << " " << st.surname << " " << st.name << " " << st.birthday << " " << st.phone << " " << st.date;
    return out;
}

void split(int p) { // алгоритм разделения для простого слияния
    ifstream a("a.txt");
    ofstream b("b.txt"), c("c.txt");
    student x;
    a >> x;
    while(!a.eof()) {
        for (int i = 0; !a.eof() && i < p; i++) {
            b << x << endl;
            a >> x;
        }
        for (int i = 0; !a.eof() && i < p; i++) {
            c << x << endl;
            a >> x;
        }
    }
    a.close(); b.close(); c.close();
}

bool nat_split() { // алгоритм разделения для естественного слияния
    ifstream a("a.txt");
    ofstream b("b.txt"), c("c.txt");
    student x, y;
    bool c_empty = true;
    a >> y;
    while (!a.eof()) {
        do {
            x = y;
            b << x << endl;
            a >> y;
        } while (x.id <= y.id && !a.eof());
        if (a.eof()) { 
            if (c_empty) {
                b << y << endl;
                a.close(); b.close(); c.close();
                return false;
            }
        }
        else {
            do {
                c_empty = false;
                x = y;
                c << x << endl;
                a >> y;
            } while (x.id <= y.id && !a.eof());
        }
    }
    a.close(); b.close(); c.close();
    return true;
}

void merge(int p) { // алгоритм слияния для простого слияния
    ofstream a("a.txt");
    ifstream b("b.txt"), c("c.txt");
    student x, y;
    b >> x;
    c >> y;
    while (!b.eof() && !c.eof()) {
        int i = 0, j = 0;
        while (!b.eof() && !c.eof() && i < p && j < p) {
            if (x.id < y.id) {
                a << x << endl;
                b >> x;
                i++;
            }
            else {
                a << y << endl;
                c >> y;
                j++;
            }
        }
        while (!b.eof() && i < p) {
            a << x << endl;
            b >> x;
            i++;
        }
        while (!c.eof() && j < p) {
            a << y << endl;
            c >> y;
            j++;
        }
    }
    while (!b.eof()) {
        a << x << endl;
        b >> x;
    }
    while (!c.eof()) {
        a << y << endl;
        c >> y;
    }
    a.close(); b.close(); c.close();
}

void nat_merge() { // алгоритм слияния для естественного слияния
    ofstream a("a.txt");
    ifstream b("b.txt"), c("c.txt");
    student x1, x2, y1, y2;
    b >> x1;
    c >> y1;
    while (!b.eof() && !c.eof()) {
        if (x1.id < y1.id) {
            a << x1 << endl;
            b >> x2;
            if (!b.eof() && x1.id > x2.id) {
                a << y1 << endl;
                c >> y2;
                while (!c.eof() && y1.id <= y2.id) {
                    y1 = y2;
                    a << y1 << endl;
                    c >> y2;
                }
                y1 = y2;
            }
            x1 = x2;
        }
        else {
            a << y1 << endl;
            c >> y2;
            if (!c.eof() && y1.id > y2.id) {
                a << x1 << endl;
                b >> x2;
                while (!b.eof() && x1.id < x2.id) {
                    x1 = x2;
                    a << x1 << endl;
                    b >> x2;
                }
                x1 = x2;
            }
            y1 = y2;

        }
    }
    while (!b.eof()) {
        a << x1 << endl;
        b >> x1;
    }
    while (!c.eof()) {
        a << y1 << endl;
        c >> y1;
    }
    a.close(); b.close(); c.close();
}

void merge_sort(int n /*количество записей*/) { // сортировка простого слияния
    for (int p = 1; p < n; p *= 2) {
        split(p);
        merge(p);
    }
}

void nat_merge_sort() { // сортировка естесвенного слияния
    while (nat_split()) {
        nat_merge();
    }
}

int main()
{
    setlocale(0, "");
    int n = 32;
    auto start = chrono::high_resolution_clock::now();
    merge_sort(n);
    //nat_merge_sort();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> du = end - start;
    cout << "Время выполнения " << du.count() << " s " << endl;
}
