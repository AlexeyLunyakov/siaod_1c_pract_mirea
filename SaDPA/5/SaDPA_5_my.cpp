#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;

/*Дан линейный однонаправленный список L
1. Разработать функцию, которая вставляет перед последним уз-лом два новых узла.
2. Удаляет из списка L первое отрицательное значение, если оно присутствует в списке.
3. Найти в списке L максимальное значение и перенести его узел в конец списка.*/

/*1. Информационная часть узла определена вариантом
2. Разработать функции вставки нового узла перед первым узлом и удаления узла по ключу.
3. Реализуйте возможность а) создания нового списка вручную, а также
б) использования уже готового списка для тестирования заданий индивидуального варианта.
4. Разработать функцию вывода списка в консоль.
5. Разработать функции согласно индивидуальному варианту. При необходимости можно добавлять вспомогательные функции, декомпозируя задачу.
6. Реализуйте текстовое пользовательское меню.
7. В основной программе выполните тестирование каждой функции
(пункты 2-5).*/


struct list {
	double number;
	list* next;
};

void addElement_start(double newNumber, list* originalList); 				 // вставка нового узла перед первым 
void deleteElement_key(int index, list* originalList);                 // удаление узла по ключу
list* findElement(double number, list* originalList);                 // нахождение элемента
list* findPrevElement(double number, list* originalList);            // нахождение предыдущего элемента
void showAllElements(list* originalList);                        // вывод списка в консоль
int getComand();                                                // определение команды
void addElement_end(list *originalList); // вставка двух элементов в конец списка
void deleteElement_negative(list* originalList);// удаление первого отрицательного элемента

void enterElements(list* originalList) {
	cout << "Введите 10 элементов списка:" << endl;
	list* currentList = originalList;
	for (int i = 0; i < 10; i++) {
		double num;
		cin >> num;
		currentList->number = num;

		if (i == 9) {
			currentList->next = NULL;
			break;
		}

		currentList -> next = new list;
		currentList = currentList -> next;
	}
}

void generate_list(list* originalList) {
	list* currentList = originalList;
	for (int i = 0; i < 10; i++) {
		double num;
		num = rand() % 50;
		currentList->number = num;
		if (i == 9) {
			currentList->next = NULL;
			break;
		}
		currentList -> next = new list;
		currentList = currentList -> next;
	}
}

void writeMenu_start() {

	string start_menu;
    start_menu += "1 - Созданный в ручную спискок \n";
    start_menu += "2 - Готовый спискок\n";

    cout << start_menu;
}
void writeMenu() {

	string menu = "Список команд:\n";
	menu += "3 - Добавить элемент в начало\n";		//done
	menu += "4 - Удаление элемента по ключу\n";		//not done
    menu += "5 - Вывести список на экран\n";		//done
	menu += "6 - Добавление двух элементов в конец\n";	//done
    menu += "7 - Найти первое вхождение отрицательного элемента и удалить его\n";	//not done
    menu += "8 - Найти макисмальный элемент и поместить в конец списка\n";			//not done
	menu += "0 - Выход из программы\n";

	cout << menu;
}

int main() {

	list originalList;
	int index;
    double number, number_2;
    int comand_start, comand;

    cout << "Каким массивом вы хотите пользоваться?\n";
    writeMenu_start();
	cout << "\nВыбранная команда:\n";
	cin >> comand_start;

    if (comand_start == 1) {
        enterElements(&originalList);
    }
    else if (comand_start != 1) {
        generate_list(&originalList);
    }
	writeMenu();

	cout << "\nВыбранная команда:\n";
	cin >> comand;

	while (comand != 0) {
		switch (comand) {
		case 3:
			cout << "Введите новый элемент:\n";
			cin >> number;
			addElement_start(number, &originalList);
			break;
		case 4:
			cout << "Введите номер элемента, который нужно удалить:\n";
			cin >> index;
			deleteElement_key(index, &originalList);
			break;
		case 5:
			cout << "Список:\n";
			showAllElements(&originalList);
			break;
		case 6:
			addElement_end(&originalList);
			break;		
        case 7:
			cout << "Лист всех элементов до изменений:\n";
			showAllElements(&originalList);
			deleteElement_negative(&originalList);
			cout << "Лист всех элементов после измененения:\n";
			showAllElements(&originalList);			
			break;
        case 8:
			cout << "Список:\n";
			showAllElements(&originalList);
			break;
		default:
			break;
		}

		comand = getComand();
	}


	return 0;
}

int getComand() {
	int comand;
	cout << "Новая команда: " << endl;
	cin >> comand;
	return comand;
}

void addElement_start(double newNumber, list* originalList) {	//done
	originalList->number = newNumber;
}

void addElement_end(list *originalList) {	//done
	list* currentList = originalList;
	for (int i = 0; i < 13; i++) {
		double num;
		if(i == 9 || i == 10) {
			cout << "Число: \n";
			cin >> num;
			currentList->number = num;
		}
		else {
			currentList->number = originalList->number;
			originalList = originalList->next;
		}
		if (i == 11) {
			currentList->next = NULL;
			break;
		}

		currentList -> next = new list;
		currentList = currentList -> next;
	}
}

void deleteElement_key(int index, list* originalList) {
	list* currentList = originalList;
	int num = index;
	for (int i = 0; i < 10; i++) {
		if(i == num) {
			list* tmp = originalList->next;
			*originalList = *(originalList->next);
			delete tmp;
			break;
		}
		else {
			currentList->number = originalList->number;
			originalList = originalList->next;
		}
		if (i == 9) {
			currentList->next = NULL;
			break;
		}

		currentList -> next = new list;
		currentList = currentList -> next;
	}
	
}

void deleteElement_negative(list* originalList) {
	list* currentList = originalList;
	for (int i = 0; i < 10; i++) {
		double num;
		cout << currentList->number << endl;
		if(currentList->number < 0) {
			list* tmp = originalList->next;
			*originalList = *(originalList->next);
			delete tmp;
			break;
		}
		else {
			currentList->number = originalList->number;
			originalList = originalList->next;
		}
		if (i == 9) {
			currentList->next = NULL;
			break;
		}

		currentList -> next = new list;
		currentList = currentList -> next;
	}
}

list* findElement(double number, list* originalList)
{
	if (number == originalList->number)
	{
		return originalList;
	}

	return findPrevElement(number, originalList)->next;
}

list* findPrevElement(double number, list* originalList)
{
	list* currentList = originalList;

	while (currentList->next->number != number)
	{
		currentList = currentList->next;

		if (currentList == NULL)
		{
			return NULL;
		}
	}

	return currentList;
}

void showAllElements(list* originalList)
{
	list* currentList = originalList;

	while (currentList != NULL)
	{
		cout << currentList->number << endl;
		currentList = currentList->next;
	}
}