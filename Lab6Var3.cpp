#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

FILE* f_out, * f_in;

struct product
{
	char name[56];
	int price;
	char unit[10];
};

void medium_1()
{
	//Записать в бин. файл информацию о товаре с найбольшей стоимостью;

	product* arr;
	int size, max_price = 0;

	do
	{
		cout << "Введите количество товаров, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new product[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите наименование товара номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].name, 56);
		cout << endl;

		do {
			cout << "Введите цену: ";
			cin >> arr[i].price;
			cout << endl;
		} while (arr[i].price <= 0);

		cout << "Введите ед. измерения: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].unit, 10);
		cout << endl << endl;
	}

	ofstream input("medium1_bin_File.bin", ios::binary | ios::out);

	for (int i = 0; i < size; i++)
	{
		if (arr[i].price > arr[max_price].price)
		{
			max_price = i;
		}
	}

	input << "Товар номер " << max_price + 1 << ":" << endl;
	input.write((char*)&arr[max_price], sizeof arr[max_price]) << endl << endl;

	input.close();

	cout << "Данные записаны в файл" << endl << endl;
}

void medium_2()
{
	//Запись в файл латинские символы, переписать данный файл, сделав каждый символ заглавным, вывести все данные в консоль;

	char arr[5]{ 'f','g','j','h','t' };

	ofstream tab("medium2_symbol_before.bin", ios::binary | ios::out);

	for (int i = 0; i < 5; i++)
	{
		tab.write((char*)&arr[i], 1);
	}

	cout << endl;
	tab.close();
	char new_arr[5];

	ifstream show("medium2_symbol_before.bin", ios::binary | ios::in);
	cout << "Символы до изменения: ";

	for (int i = 0; i < 5; i++)
	{
		show.read((char*)&new_arr[i], 1);
		cout << new_arr[i] << " ";
	}

	show.close();
	ofstream tab1("medium2_symbol_after.bin", ios::binary | ios::out);

	new_arr[0] = 'F';
	new_arr[1] = 'G';
	new_arr[2] = 'J';
	new_arr[3] = 'H';
	new_arr[4] = 'T';

	for (int i = 0; i < 5; i++)
	{
		tab1.write((char*)&new_arr[i], 1);
	}

	tab1.close();

	cout << endl;

	ifstream show1("medium2_symbol_after.bin", ios::binary | ios::in);
	cout << "Символы после изменения: ";

	for (int i = 0; i < 5; i++)
	{
		show1.read((char*)&new_arr[i], 1);
		cout << new_arr[i] << " ";
	}

	show1.close();
	cout << endl << endl;
}

struct student
{
	char surname[56];
	char name[56];
	char patronymic[56];
	int group_number;
	int point;
	int scholarship;
};

void medium_3()
{
	student* arr;
	int size, modern_year = 2020;

	do
	{
		cout << "Введите количество студентов, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new student[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите фамилию студента номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].surname, 56);
		cout << endl;

		cout << "Введите имя студента: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].name, 56);
		cout << endl;

		cout << "Введите отчество студента: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].patronymic, 56);
		cout << endl;

		cout << "Введите номер группы: ";
		cin >> arr[i].group_number;
		cout << endl;

		do {
			cout << "Введите средний балл: ";
			cin >> arr[i].point;
			cout << endl;
		} while (arr[i].point > 5);

		do {
			cout << "Введите стипендию: ";
			cin >> arr[i].scholarship;
			cout << endl;
		} while (arr[i].scholarship <= 0);

		cout << endl << endl;
	}

	f_out = fopen("medium3_student_before.bin", "wb");
	fwrite(arr, sizeof(student), size, f_out);
	fclose(f_out);

	student* new_arr = new student[size];

	f_in = fopen("medium3_student_before.bin", "rb");
	fread(new_arr, sizeof(student), size, f_in);
	fclose(f_in);

	cout << "Данные из файла перед изменением:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Фамилия студента номер " << i + 1 << ": " << new_arr[i].surname << ", Имя: " << new_arr[i].name << ", Отчество: " << new_arr[i].patronymic << endl;
		cout << "Номер группы: " << new_arr[i].group_number << endl;
		cout << "Средний балл: " << new_arr[i].point << endl;
		cout << "Стипендия: " << new_arr[i].scholarship << endl << endl;
	}

	for (int i = 0; i < size; i++)
	{
		if (new_arr[i].point > 3)
		{
			new_arr[i].scholarship = new_arr[i].scholarship / 100 * 130;
		}
	}

	f_out = fopen("medium3_student_after.bin", "wb");
	fwrite(new_arr, sizeof(student), size, f_out);
	fclose(f_out);

	f_in = fopen("medium3_student_after.bin", "rb");
	fread(new_arr, sizeof(student), size, f_in);
	fclose(f_in);

	cout << "Данные из файла после изменения:" << endl << endl;

	for (int i = 0; i < size; i++)
	{
		cout << "Фамилия студента номер " << i + 1 << ": " << new_arr[i].surname << ", Имя: " << new_arr[i].name << ", Отчество: " << new_arr[i].patronymic << endl;
		cout << "Номер группы: " << new_arr[i].group_number << endl;
		cout << "Средний балл: " << new_arr[i].point << endl;
		cout << "Стипендия: " << new_arr[i].scholarship << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	int a;
	int count = 0;

	do
	{
		cout << "Введите номер задания(medium_1 - 1, medium_2 - 2, medium_3 - 3): ";

		cin >> a;

		cout << endl;

		if (a == 1)
		{
			medium_1();
			count++;
		}

		if (a == 2)
		{
			medium_2();
			count++;
		}

		if (a == 3)
		{
			medium_3();
			count++;
		}

	} while (count == 0);

	int b;

	do
	{

		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}