#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
1. Вычислить значение цифрового корня для некоторого целого числа N.
2. Найти в двунаправленном списке количество четных элементов.
*/

struct list {
	int field;                  // поле данных
	struct list *next;          // указатель на следующий элемент
	struct list *prev;          // указатель на предыдущий элемент
};

struct list * init(int a) {     // а- значение первого узла
	struct list *last; 
	
    // выделение памяти под корень списка
	last = (struct list*)malloc(sizeof(struct list));

	last->field = a;
	last->next = NULL;           // указатель на следующий узел
	last->prev = NULL;           // указатель на предыдущий узел

	return(last);
}

struct list * addelem(list *last, int number) {
	struct list *temp, *p;

	temp = (struct list*)malloc(sizeof(list));

	p = last->next;              // сохранение указателя на следующий узел
	last->next = temp;           // предыдущий узел указывает на создаваемый
	temp->field = number;       // сохранение поля данных добавляемого узла

	temp->next = p;             // созданный узел указывает на следующий узел
	temp->prev = last;           // созданный узел указывает на предыдущий узел

	if (p != NULL)
		p->prev = temp;
    
	return(temp);
}

void listprint(list *last) {
	struct list *p;
	p = last;
	do {
		printf("%d ", p->field); // вывод значения элемента p
		p = p->next;             // переход к следующему узлу
	} while (p != NULL);         // условие окончания обхода
}

int count(list* node, int i) { 
    if (i < 0)
        return 0;               // выход из рекурсии, когда проверены все элементы
    int n = 0;
    if (node->field % 2 == 0)
        n = 1;                   // если подходит условию, то засчитываем
    return n + count(node->next, i - 1); // суммируем засчитанные элементы
}

long long int root(long long int N) { // итерационный метод
    int  n, m;
    n = N;
    do
    {
        for(m = 0; n; n/=10) {
            m += n % 10;
        }
        n = m;
    } while(n>9);
    return n;
}

long long int rec_root(long long int N) { // рекурсивный метод
    int temp_n = 0;
    while(N > 0) {
        temp_n += N % 10;
        N /= 10;
    }
    if(temp_n > 9) return root(temp_n);
    else return temp_n;
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
    writeMenu_start();
	cout << "\nВыбранная команда: \n";
	cin >> comand_start;

    if (comand_start == 1) {
        long long int N;
        cout << "Введите значение числа N: \n";
        cin >> N;
        writeMenu_sqrt();
        cout << "\nВыбранная команда:\n";
	    cin >> comand;
        while (comand != 0) {
            switch (comand) {
            case 3: {
                cout << "Ваш цифровой корень (итерационный метод): \n" << root(N) << "\n";
                break;
            }
            case 4: {
                cout << "Ваш цифровой корень (рекурсивный метод метод): \n" << rec_root(N) << "\n";
                break;
            }
            default:
                break;
            }
            comand = getComand();
        }
        
    }
    else if (comand_start == 2) {
        list *head = nullptr, *cur = nullptr;
        int kolvo;
        writeMenu_list();
        cout << "\nВыбранная команда:\n";
	    cin >> comand;
        while (comand != 0) {
            switch (comand) {
            case 3: {
                cout << "\nВведите количество элементов ДС: ";
                cin >> kolvo;
                int num;
                cout << "\nelem = ";
                cin >> num;
                head = init(num);
	            cur = head;
                for (int i = 0; i < kolvo - 1; i++) {
                    cout << "elem = ";
                    cin >> num;
                    cur = addelem(cur, num);
                }
                cout << "\nВаш новый список: \n";
                listprint(head);
                cout << endl;
                bool direction = true;
                break;
            }
            case 4: {
                cout << "Количество четных элементов: \n";
                if (head != nullptr)
                    cout << count(head, kolvo-1) << endl;
                else 
                    cout << "Сначала заполните ДС! \n";
                    break;
                break;
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