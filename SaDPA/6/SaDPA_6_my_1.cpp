nclude <iostream>
#include <vector>
#include <random>
#include <string>
#include <iomanip>
using namespace std;

struct Chitatel {
    int num;
    Chitatel* next; // связь со слеующим
    Chitatel* prev; // свядь с прошлым
    Chitatel(int _num) : num(_num), next(nullptr) {} // конструктор экземпляра узла списка
};

struct List_Chitateley {
    Chitatel* first;                // указатель на первый узел
    Chitatel* last;	                // указатель на последний узел
    List_Chitateley() : first(nullptr), last(nullptr) {} // конструктор списка

    bool is_empty();            // метод проверки наличия узлов в списке
    void push_back(int num);   // метод добавления элемента в конец списка
    void push_front(int num);  // метод добавления элемента в начало списка
    Chitatel* find(int num);       // метод поиска узла в списке по значению
    void remove_first();        // метод удаления первого узла 
    void remove_last();         // метод удаления последнего узла 
    void remove(int num);      // метод удаления элемента по значению 
    void print();               // метод печати списка
    Chitatel* operator[] (const int index);
    void isort();               // сортировка вставками
};

struct Book {
    string data;
    Book* next; // связь со слеующим
    Book* prev; // свядь с прошлым
    Book(int _data) : data(_data), next(nullptr) {} // конструктор экземпляра узла списка
};

struct Book_list {
    Book* first;                // указатель на первый узел
    Book* last;	                // указатель на последний узел
    Book_list() : first(nullptr), last(nullptr) {} // конструктор списка

    bool is_empty();            // метод проверки наличия узлов в списке
    void push_back(int data);   // метод добавления элемента в конец списка
    void push_front(int data);  // метод добавления элемента в начало списка
    Book* find(int data);       // метод поиска узла в списке по значению
    void remove_first();        // метод удаления первого узла 
    void remove_last();         // метод удаления последнего узла 
    void remove(int data);      // метод удаления элемента по значению 
    void print();               // метод печати списка
    Book* operator[] (const int index);
    void isort();               // сортировка вставками
};

struct Date {
    string year = "";
    string month = "";
    string day = "";

    Date() {
        day = "11";
        month = "11";
        year = "1983";
    }

    Date(string date) {
        day += date[0];
        day += date[1];
        month += date[3];
        month += date[4];
        year += date[6];
        year += date[7];
        year += date[8];
        year += date[9];
    }
};

ostream& operator << (ostream& out, const Date& object) {
    out << object.day << "." << object.month << "." << object.year << "\n";
    return out;
}

bool comparator_date(pair<Date, string> a, pair<Date, string> b) {
    return stoi(a.first.year) * 10000 + stoi(a.first.month) * 100 + stoi(a.first.day) < stoi(b.first.year) * 10000 + stoi(b.first.month) * 100 + stoi(b.first.day);
}

bool Book_list::is_empty() {
    return first == nullptr;
}

void Book_list::push_back(int data) {
    Book* temp = new Book(data);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    last->next = temp;
    last = temp;
}

void Book_list::push_front(int data) {
    Book* temp = new Book(data);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    temp->next = first;
    first = temp;
}

// Book* Book_list::find(int num) {
//     Book* temp = first;
//     while (temp && temp->data != num) temp = temp->next;
//     return (temp && temp->data == num) ? temp : nullptr;
// }           //      if                      else

void Book_list::remove_first() {
    Book* temp = first;
    first = temp->next;
    delete temp;
}

void Book_list::remove_last() {
    if (first->next == nullptr) {
        delete first;
        first = nullptr;
        last = nullptr;
        return;
    }
    Book* temp = first;
    while (temp->next->next != nullptr) temp = temp->next;
    delete last;
    last = temp;
    temp->next = nullptr;
}

void Book_list::remove(int data) {
    if (is_empty()) return;
    if (first->data == data) {
        remove_first();
        return;
    }
    else if (last->data == data) {
        remove_last();
        return;
    }
    Book* slow = first;
    Book* fast = first->next;
    while (fast && fast->data != data) {
        fast = fast->next;
        slow = slow->next;
    }

    if (fast == nullptr) {
        cout << "Данный элемент не существует" << endl;
        return;
    }

    slow->next = fast->next;
    delete fast;
}

void Book_list::print() {
    if (is_empty()) return;
    Book* temp = first;
    while (temp) {
        cout << setw(3);
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

//Сортировка вставками для списка
void Book_list::isort(){
    Book* a, *b, *p, *h = NULL;
 
    for(Book* i = first; i != NULL; ) {
        a = i;
        i = i->next;
        b = h;
        for(p = NULL; (b != NULL) && (a->data > b->data); ) {
            p = b;
            b = b->next;
        }
 
        if(p == NULL){
            a->next = h;
            h       = a;
        } else {
            a->next = b;
            p->next = a;
        }
    }
    if(h != NULL) 
        first = h;
}

void L_list_form(Book_list* mainlist, Book_list* list1, Book_list* list2){
    for (int i = 0; i < 10; i++) {
        if (!(mainlist->find((*list1)[i]->data))) {
            mainlist->push_back((*list1)[i]->data);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (mainlist->find((*list2)[i]->data)) {
            mainlist->remove((*list2)[i]->data);
        }
    }
}

Book* Book_list::operator[] (const int index) {
        if (is_empty()) return nullptr;
        Book* temp = first;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
            if (!temp) return nullptr;
        }
        return temp;
}

void writeMenu_start() {

	string start_menu;
    start_menu += "1 - Созданные в ручную спискоки \n"; //done
    start_menu += "2 - Готовый спискок\n";             //done

    cout << start_menu;
}
void writeMenu() {

	string menu = "Список команд:\n";
    // основные функции
	menu += "3 - Добавить элемент в начало\n";		//done
	menu += "4 - Удаление элемента по ключу\n";		//done
    menu += "5 - Вывести список на экран\n";		//done
    //дополнительные функции
	menu += "6 - Новый список L с элементами, значения которых входят в список L1 и не входят в список L2\n";	//done
    menu += "7 - Удаление подсписка списка L1, заданного диапазоном позиции\n";	//done
    menu += "8 - Сортировка L2 по возрастанию\n";   //done
    menu += "9 - Проверка команды\n";			    //done
	menu += "0 - Выход из программы\n";

	cout << menu;
}

int getComand() {
	int comand;
	cout << "Новая команда: " << endl;
	cin >> comand;
	return comand;
}

int main() {
    int n;
    n = 10;
    Book_list mainlist;
    Book_list list1;
    Book_list list2;

	int index;
    int number;
    
    int comand_start, comand;
    cout << "Команды:\n";

    writeMenu_start();

	cout << "\nВыбранная команда:\n";
	cin >> comand_start;

    if (comand_start == 1) {
        cout << "Введите 10 элементов первого списка:\n";
        for (int i = 0; i < 10; i++) {
            int data;
		    cin >> data;
            list1.push_back(num);
        }
        cout << "Введите 10 элементов второго списка:\n";
        for (int i = 0; i < 10; i++) {
            int num;
		    cin >> num;
            list2.push_back(num);
        }
    }
    else if (comand_start != 1) {
        for (int i = 0; i < 10; i++) {
            int num;
		    num = rand() % 50;
            list1.push_back(num);
        }
        cout << "Ваш список\n";
        list1.print();
        cout << endl;
        for (int i = 0; i < 10; i++) {
            int num;
		    num = rand() % 50;
            list2.push_back(num);
        }
        cout << "Ваш список\n";
        list2.print();
    }

	writeMenu();

	cout << "\nВыбранная команда:\n";
	cin >> comand;

	while (comand != 0) {
		switch (comand) {
		case 3:
			cout << "Введите новый элемент для первого списка:\n";
			cin >> number;
            list1.push_front(number);
			cout << "Введите новый элемент для второго списка:\n";
			cin >> number;
            list2.push_front(number);            
			break;
		case 4:
			cout << "Введите элемент для удаления (первый список):\n";
			cin >> number;
            list1.remove(number);
			cout << "Введите элемент для удаления (второй список):\n";
			cin >> number;
            list2.remove(number);
			break;
		case 5:
            cout << "Список 1:\n";
            list1.print();
            cout << "Список 2:\n";
            list2.print();
			break;
		case 6:
            cout << "Список L:\n";
            L_list_form(&mainlist, &list1, &list2);
            mainlist.print();
			break;		
        case 7:
            cout << "Введите индекс элемента и диапазон\n";
            int amount;
            cin >> index; 
            cin >> amount;
            for (int i = 0; i < amount; i++) {
                list1.remove(list1[index]->num);
            }
            list1.print();
            break;
        case 8:
            cout << "Список 2 до изменений:\n";
            list2.print();
            list2.isort();
            cout << "Список 2 после изменений:\n";
            list2.print();
			break;
        case 9:
            list1.isort();
            break;
		default:
			break;
		}

		comand = getComand();
	}
    return 0;
}