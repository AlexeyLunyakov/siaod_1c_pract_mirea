#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
1. Вычислить значение цифрового корня для некоторого целого числа N.
2. Найти в двунаправленном списке количество четных элементов.
*/

struct Kniga {
	string kniga_;
    string data_take;
    string data_return;
	Kniga* next;
	Kniga(string new_name, string data_take, string data_return);
};

struct ListKnig {
	Kniga* first;
	Kniga* last;
	ListKnig();
	bool is_empty();
	void push_back(string new_name, string data_take, string data_return);
	void print();
	Kniga* find(string);
    void debt_under();
    string return_kniga();
};

struct Chitatel {
    string number_;
    ListKnig* knigi_;
    Chitatel* next;
    Chitatel* prev;
    Chitatel();
    void read();
    void print();
    void add_kniga();
    void data_change();
    void debt(string now_date);
    
};

struct ListChitatels {
    Chitatel* first;
    Chitatel* last;
    ListChitatels();
    bool is_empty();
    void push_back();
    Chitatel* find(string);
    void find_reader(string find_val);
    void print(bool);
    void remove_first();
    void remove_last();
    void remove(string);
};

Chitatel::Chitatel() {
    number_ = "";
    knigi_ = nullptr;
    prev = nullptr;
    next = nullptr;
}

void Chitatel::print() {
    cout << "Номер читателя библиотеки: " << number_ << "\n";
    cout << "Список книг: ";
    knigi_->print();
}

void Chitatel::read() {
    ListKnig *list = new ListKnig;
    cout << "Введите номер читателя библиотеки: ";
    cin >> number_;
    cout << "Введите номер книги и даты выдачи и возврата через пробел (0 0 0 - чтобы закончить список ): \n";
    while (true) {
        string a, b, c;
        cin >> a >> b >> c;
        if (a == "0" && b == "0" && c == "0")
            break;
        list->push_back(a, b, c);
        //list->print();
    }
    knigi_ = list;
    cout << "Записи о читателе: \n";
    knigi_->print();
}

ListChitatels::ListChitatels() {
    first = nullptr;
    last = nullptr;
}

bool ListChitatels::is_empty() {
    return first == nullptr;
}

void ListChitatels::push_back() {
    Chitatel* new_val = new Chitatel();
    new_val->read();
    if (is_empty()) {
        first = new_val;
        last = new_val;
    }
    else {
        new_val->prev = last;
        last->next = new_val;
        last = new_val;
    }
}

void ListChitatels::print(bool direction) {
    if (is_empty())
        return;
    Chitatel* i = first;
    if (!direction)
        i = last;
    while (i) {
        cout << "-----------------------------" << "\n";
        i->print();
        if (direction)
            i = i->next;
        else
            i = i->prev;
    }
}

Chitatel* ListChitatels::find(string find_val) {
    Chitatel* temp = first;
    while (temp && temp->number_ != find_val)
        temp = temp->next;
    return (temp && temp->number_ == find_val) ? temp : nullptr;
}

void ListChitatels::find_reader(string find_val) {
    Chitatel* temp = find(find_val);
    if (temp != nullptr) {
        temp->print();
    }
    else {
        cout << "Неверный номер читателя\n";
    }
}

void ListChitatels::remove_first() {
    if (is_empty()) return;
    Chitatel* temp = first;
    first = temp->next;
    delete temp;
}

void ListChitatels::remove_last() {
    if (is_empty()) return;
    if (first == last) {
        remove_first();
        return;
    }
    Chitatel* tmp = first;
    while (tmp->next != last) tmp = tmp->next;
    tmp->next = nullptr;
    delete last;
    last = tmp;
}

void ListChitatels::remove(string chitatel_num) {
    if (is_empty())
        return;
    if (first->number_ == chitatel_num) {
        remove_first();
        return;
    }
    else if (last->number_ == chitatel_num) {
        remove_last();
        return;
    }
    Chitatel* tmp = first;
    while (tmp && tmp->number_ != chitatel_num)
        tmp = tmp->next;
    if (!tmp) {
        cout << "This element does not exist" << "\n";
        return;
    }
    Chitatel* new_prev = tmp->prev;
    Chitatel* new_next = tmp->next;
    new_prev->next = new_next;
    new_next->prev = new_prev;
    delete[] tmp;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void Chitatel::add_kniga() {    
    cout << "Книги читателя\n";
    knigi_->print();
    cout << "Введите номер книги и даты выдачи и возврата через пробел (0 0 0 - чтобы закончить список ): \n";
    while (true) {
        string a, b, c;
        cin >> a >> b >> c;
        if (a == "0" && b == "0" && c == "0")
            break;
        knigi_->push_back(a, b, c);
        knigi_->print();
    }
}

void Chitatel::data_change() {
    cout << "Книги читателя\n";
    knigi_->print();
    string temp_kniga;
    cout << "Введите номер книги: \n";
    cin >> temp_kniga;
    if (knigi_->find(temp_kniga) != nullptr) {
        Kniga* temp = knigi_->find(temp_kniga);
        string new_data;
        cout << "Введите новую дату: \n";
        cin >> new_data;
        temp->data_return = new_data;
    }
}

void  Chitatel::debt(string now_date) {
    cout << "Книги читателя\n";
    knigi_->print();
    string temp_kniga;
    cout << knigi_->return_kniga() << endl;
    temp_kniga = knigi_->return_kniga();
    if (knigi_->find(temp_kniga) != nullptr) {
        Kniga* temp = knigi_->find(temp_kniga);
        if (temp->data_return < now_date) {
            cout << "Книга " << temp_kniga << " просрочена\n";
        }
    }
}

string ListKnig::return_kniga() {
    Kniga* p = first;
    while (p) {
        return p->kniga_;        
        p = p->next;
    }
    return " ";
}

Kniga::Kniga(string new_val, string new_data_take, string new_data_return) { //string new_name, 
    kniga_ = new_val;
    data_take = new_data_take;
    data_return = new_data_return;
    next = nullptr;
}

ListKnig::ListKnig() {
    first = nullptr;
    last = nullptr;
}

bool ListKnig ::is_empty() {
    return first == nullptr;
}

void ListKnig ::push_back(string new_val, string new_data_take, string new_data_return) {
    Kniga* p = new Kniga(new_val, new_data_take, new_data_return);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
}

void ListKnig ::print() {
    if (is_empty())
        return;
    Kniga* p = first;
    while (p) {
        cout << p->kniga_ << " (" << p->data_take << " " << p->data_return << ") ";
        p = p->next;
    }
    cout << "\n";
}

Kniga* ListKnig::find(string find_val) {
    Kniga* p = first;
    while (p && p->kniga_!= find_val)
        p = p->next;
    return (p && p->kniga_ == find_val) ? p : nullptr;
}

void manual_fill(ListChitatels& objects) {
    int size;
    cout << "Введите размер нового списка читателей: ";
    cin >> size;
    for (int i = 0; i < size; ++i){
        objects.push_back();
        int j = 1;
        //objects.print(j);
    }
}

int root(int N) { // итерационный метод
    int temp_n = 0;
    while(N > 0)
    {
        temp_n += N % 10;
        N /= 10;
    }
    if(temp_n > 9) return root(temp_n);
    else return temp_n;
}

int digiroot(int number) { // рекурсивный метод
    if (number == 0) return number;
    return number%10 + digiroot(number/10);
}
 
int total_digiroot(int number) {
    int res = digiroot(number);
    if (res/10 == 0){
        return res;
    }
    return total_digiroot(res);
}

void writeMenu_start() {

	string start_menu;
	start_menu += "1 - Вычислить значение цифрового корня для некоторого целого числа N \n";	
    start_menu += "2 - Найти в двунаправленном списке количество четных элементов \n";
	start_menu += "0 - Выход из программы \n";

    cout << start_menu;
}

void writeMenu_sqrt() {

	string menu = "Список команд:\n";
    menu += "3 - Итерационный метод \n";
    menu += "4 - Рекурсивный метод \n";
	menu += "0 - Выход из программы \n";

	cout << menu;
}

void writeMenu_list() {

	string menu = "Список команд:\n";
    menu += "3 - Создание списка вручную \n";
    menu += "4 - Поиск количества четных элементов \n";
	menu += "0 - Выход из программы \n";

	cout << menu;
}

int getComand() {
	int comand;
	cout << "Новая команда: " << endl;
	cin >> comand;
	return comand;
}

int main() {

    int comand_start, comand;
    //ListChitatels originalList;

    writeMenu_start();
	cout << "\nВыбранная команда: \n";
	cin >> comand_start;

    if (comand_start == 1) {
        int N;
        cout << "Введите значение числа N: \n";
        cin >> N;
        writeMenu_sqrt();
        cout << "\nВыбранная команда:\n";
	    cin >> comand;
        while (comand != 0) {
            switch (comand) {
            case 3: {
                cout << "Ваш цифровой корень (итерационный метод): \n" << root(N) << "\n\n";
                break;
            }
            case 4: {
                cout << "Ваш цифровой корень (рекурсивный метод метод): \n" << total_digiroot(N) << "\n\n";
                break;
            }
            default:
                break;
            }
            comand = getComand();
        }
        
    }
    else if (comand_start == 2) {
        writeMenu_list();
        cout << "\nВыбранная команда:\n";
	    cin >> comand;
        while (comand != 0) {
            switch (comand) {
            case 3: {
                //manual_fill(originalList);
                cout << "\n\nВаш новый список: \n";
                bool direction = true;
                //originalList.print(direction);
                break;
            }
            case 4: {
                cout << "Количество четных элементов: \n";
                // функция подсчета четных элементов
            }
            default:
                break;
            }
            comand = getComand();
        }

    }
    else
        return 0;
}