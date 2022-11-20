#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;

/*Даны два линейных однонаправленных списка L1 и L2.
1. Разработать функцию, которая формирует список L, включив в него по одному разу элементы, значения которых входят 
в список L1 и не входят в список L2.
2. Разработать функцию, которая удаляет подсписок списка L1 заданный диапазоном позиций. Например, со второго три.
3. Разработать функцию, которая упорядочивает значения списка L2, располагая их в порядке возрастания.*/

/*1. Информационная часть узла определена вариантом
2. Разработать функции вставки нового узла перед первым узлом и удаления узла по ключу.
3. Реализуйте возможность а) создания нового списка вручную, а также
б) использования уже готового списка для тестирования заданий индивидуального варианта.
4. Разработать функцию вывода списка в консоль.
5. Разработать функции согласно индивидуальному варианту. При необходимости можно добавлять вспомогательные функции, декомпозируя задачу.
6. Реализуйте текстовое пользовательское меню.
7. В основной программе выполните тестирование каждой функции
(пункты 2-5).*/


struct Node {
    char val;
    Node* next; // связь
    Node(char _val) : val(_val), next(nullptr) {} // конструктор экземпляра узла списка
};

struct list {
    Node* first;                // указатель на первый узел
    Node* last;	                // указатель на последний узел
    list() : first(nullptr), last(nullptr) {} // конструктор списка

    bool is_empty();            // метод проверки наличия узлов в списке
    void push_back(char val);   // метод добавления элемента в конец списка
    void push_front(char val);  // метод добавления элемента в начало списка
    Node* find(char val);       // метод поиска узла в списке по значению
    void remove_first();        // метод удаления первого узла 
    void remove_last();         // метод удаления последнего узла 
    void remove(char val);      // метод удаления элемента по значению 
    void print();               // метод печати списка
    Node* operator[] (const int index);
    void isort();               // сортировка вставками
};

bool list::is_empty() {
    return first == nullptr;
}

void list::push_back(char val) {
    Node* temp = new Node(val);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    last->next = temp;
    last = temp;
}

void list::push_front(char val) {
    Node* temp = new Node(val);
    if (is_empty()) {
        first = temp;
        last = temp;
        return;
    }
    temp->next = first;
    first = temp;
}

Node* list::find(char val) {
    Node* temp = first;
    while (temp && temp->val != val) temp = temp->next;
    return (temp && temp->val == val) ? temp : nullptr;
}           //      if                      else

void list::remove_first() {
    Node* temp = first;
    first = temp->next;
    delete temp;
}

void list::remove_last() {
    if (first->next == nullptr) {
        delete first;
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* temp = first;
    while (temp->next->next != nullptr) temp = temp->next;
    delete last;
    last = temp;
    temp->next = nullptr;
}

void list::remove(char val) {
    if (is_empty()) return;
    if (first->val == val) {
        remove_first();
        return;
    }
    else if (last->val == val) {
        remove_last();
        return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != val) {
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

void list::print() {
    if (is_empty()) return;
    Node* temp = first;
    while (temp) {
        cout << setw(3);
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

//Сортировка вставками для списка
void list::isort(){
    Node* a, *b, *p, *h = NULL;
 
    for(Node* i = first; i != NULL; ) {
        a = i;
        i = i->next;
        b = h;
        for(p = NULL; (b != NULL) && (a->val > b->val); ) {
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

void L_list_form(list* mainlist, list* list1, list* list2){
    for (int i = 0; i < 10; i++) {
        if (!(mainlist->find((*list1)[i]->val))) {
            mainlist->push_back((*list1)[i]->val);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (mainlist->find((*list2)[i]->val)) {
            mainlist->remove((*list2)[i]->val);
        }
    }
}

Node* list::operator[] (const int index) {
        if (is_empty()) return nullptr;
        Node* temp = first;
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
    list mainlist;
    list list1;
    list list2;

	int index;
    char number;
    
    int comand_start, comand;
    cout << "Команды:\n";

    writeMenu_start();

	cout << "\nВыбранная команда:\n";
	cin >> comand_start;

    if (comand_start == 1) {
        cout << "Введите 10 элементов первого списка:\n";
        for (int i = 0; i < 10; i++) {
            char num;
		    cin >> num;
            list1.push_back(num);
        }
        cout << "Введите 10 элементов второго списка:\n";
        for (int i = 0; i < 10; i++) {
            char num;
		    cin >> num;
            list2.push_back(num);
        }
    }
    else if (comand_start != 1) {
        for (int i = 0; i < 10; i++) {
            char num;
		    num = rand() % 50;
            list1.push_back(num);
        }
        cout << "Ваш список\n";
        list1.print();
        cout << endl;
        for (int i = 0; i < 10; i++) {
            char num;
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
                list1.remove(list1[index]->val);
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