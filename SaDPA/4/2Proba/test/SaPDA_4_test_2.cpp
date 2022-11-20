#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

struct student {
    string country = "";
    string city = "";
    string hotel = "";
    string rating = "";
    string travel = "";
    string excurs = "";
    string service = "";
    string cost = "";
};

ifstream& operator>>(ifstream& in, student& st) {
    in >> st.country >> st.city >> st.hotel >> st.rating >> st.travel >> st.excurs >> st.service >> st.cost;
    return in;
}

ofstream& operator<<(ofstream& out, student& st) {
    out << st.country << " " << st.city << " " << st.hotel << " " << st.rating << " " << st.travel << " " << st.excurs << " " << st.service << " " << st.cost;
    return out;
}

void split(int p) { // алгоритм разделения для простого слияния
    ifstream a("a.txt");
    ofstream b("b.txt"), c("c.txt");
    student x;
    a >> x;
    while (!a.eof()) {
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
        } while (x.country <= y.country && !a.eof());
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
            } while (x.country <= y.country && !a.eof());
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
            if (x.country < y.country) {
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
        if (x1.country < y1.country) {
            a << x1 << endl;
            b >> x2;
            if (!b.eof() && x1.country > x2.country) {
                a << y1 << endl;
                c >> y2;
                while (!c.eof() && y1.country <= y2.country) {
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
            if (!c.eof() && y1.country > y2.country) {
                a << x1 << endl;
                b >> x2;
                while (!b.eof() && x1.country < x2.country) {
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