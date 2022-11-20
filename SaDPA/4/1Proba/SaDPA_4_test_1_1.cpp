#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cmath>
using namespace std ;

void Delenie(int*p, int*end) {
    *end=0;
    ofstream b_file, c_file;
    ifstream a_file;
    a_file.open("A");
    b_file.open("B");
    c_file.open("C");
    string s;
    int i;
    while(!a_file.eof()) {
        i = 0;
        while (!a_file.eof() && i < *p) {
            getline(a_file, s, ' ');
            b_file << s << " ";
            i++;
        }
        i = 0;

        while (!a_file.eof() && i < *p) {
            getline(a_file, s, ' ');
            c_file << s << " ";

            i++;
            *end = 1;
        }
    }
    a_file.close();
    b_file.close();
    c_file.close();
}

void Sliyanie(int*p){
    ifstream b_file, c_file;
    ofstream a_file;
    string string_1, string_2;
    a_file.open("A");
    b_file.open("B");
    c_file.open("C");
    int g = 0;
    int i = 0;
    int j = 0;
    getline(b_file, string_1, ' ');
    getline(c_file, string_2, ' ');
    while(!b_file.eof() && !c_file.eof()){
        i = 0; j = 0;
        while(!b_file.eof() && !c_file.eof()&& i < *p && j < *p){
            if( stoi(string_1) < stoi(string_2)){
                if (g == 0) {
                    a_file << string_1;
                    getline(b_file, string_1, ' ');
                    i++;
                }
                else {
                    a_file << " " << string_1;
                    getline(b_file, string_1, ' ');
                    i++;
                }
                g += 1;
            }
            else {
                if (g == 0){
                    a_file << string_2;
                    getline(c_file, string_2, ' ');
                    j++;
                }
                else {
                    a_file << " " << string_2;
                    getline(c_file, string_2, ' ');
                    j++;
                }
                g+=1;
            }}
        while(!b_file.eof() && i<*p ) {
            a_file << " " << string_1;
            getline(b_file, string_1, ' ');
            i++;
        }
        while(!c_file.eof() && j<*p ) {
            a_file << " " << string_2;
            getline(c_file, string_2, ' ');
            j++;
        }
    }
    while(!b_file.eof()){
        a_file << " " << string_1;
        getline(b_file, string_1, ' ');
    }
    while(!c_file.eof()){
        a_file << " " << string_2;
        getline(c_file, string_2, ' ');
    }
    a_file.close();
    b_file.close();
    c_file.close();
}

void PryamSliyanie(){
    int end;
    string s;
    fstream c_file;
    c_file.open("C");
    int p = 1;
    char f;
    Delenie(&p, &end);
    while(end == 1){
        Sliyanie(&p);
        p *= 2;
        Delenie(&p, &end);
    }
}

int main() {
    auto start_time = chrono :: steady_clock :: now();
    PryamSliyanie();
    auto end_time = chrono :: steady_clock :: now();
    auto interval = chrono :: duration_cast < chrono :: nanoseconds > (end_time - start_time);
    cout << "Время компиляции " << interval.count() / pow(10, 6) << " ms\n\n";
    return 0;
}