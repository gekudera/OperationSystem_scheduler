
#include <iostream>
#include <fstream> 
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <time.h> 
using namespace std;

//считает размер матрицы из файла
int countWords() //функция считает size файла
{
	string Matrix_str;
	ifstream Matrix_F;
	Matrix_F.open("input.txt");
	if (Matrix_F.is_open())
	{
		getline(Matrix_F, Matrix_str);
	}
	
	Matrix_str += ' ';
	int i = 0, count_word = 0;
	while (Matrix_str[i])
	{
		if (Matrix_str[i] != ' ' && Matrix_str[i + 1] == ' ') count_word++;
		i++;
	}
	Matrix_F.close();
	return count_word;
}

//проверка на ввод числа (не буква и не символ)
static bool is_correct_input(std::string buf)
{
	bool test = true;
	for (int i = 0; i < buf.size(); i++)
	{
		if (buf[i] >= '0' && buf[i] <= '9') test = true;
		else
		{
			test = false;
			cout << "Некорректный ввод! Введите число ещё раз." << endl;
			cout << endl;
			system("pause");
			break;
		}
	}
	return test;
}

//выводит таблицу с номером и временем процессов
void ishod_output(int* matr, int kol)
{ 
	cout << endl << "Матрица введенных данных: " << endl;
	cout  << "   Номер: ";
	for (int i = 0; i < kol; i++)
	{
		cout << " | " << std::setw(3) << i + 1;
	}
	cout << " | " << endl << "Время вып.";
	for (int i = 0; i < kol; i++)
	{
		cout << " | " << std::setw(3) << matr[i];
	}
	cout << " | " << endl << endl;
}

//выводит итоговую таблицу на экран
void Print_table(int kol, int su_quant, int* times, bool* flags)
{
	int summ_quant = su_quant;                               //суммарный квант ЦП
	int random_quant = 0, razniza = 0;                       //рандомный квант ЦП
	int min, number;                                         //для запоминания выбранного процесса
	vector<int> solution;                                    //вектор решения
	bool first_in_flag = true, flag1 = true;                 //флаги для красивого отображения таблицы
	int count = 1;                                           //для подсчета итераций


	cout << "__________________________________________________________________________________________________________________ " << endl;
	cout << endl << "| № итер.| Квант вр. ЦП | Cумм. доступное время ЦП | № выбр.процесса | Время выбр. процесса | Оставшееся время ЦП |" << endl;
	cout << "|_________________________________________________________________________________________________________________|";
	while (solution.size() != kol)
	{
		if (first_in_flag == false)
		{
			count++;
			random_quant = 1 + rand() % 49;
			summ_quant = razniza + random_quant; //суммарный квант
		}
		else
		{
			random_quant = summ_quant;
		}
		first_in_flag = false;
		flag1 = false;
		cout << endl << "| " << std::setw(6) << count << " | quant = " << std::setw(4) << random_quant << " |";

		while (summ_quant != -1)
		{
			if (flag1 == true)
			{
				cout << endl << "|        |              |";
				flag1 = false;
			}

			min = 50, number = -1;
			for (int j = 0; j < kol; j++)
			{
				if (((summ_quant - times[j]) < min) && ((summ_quant - times[j]) >= 0) && (flags[j] == false))
				{
					min = summ_quant - times[j];
					number = j;
				}
			}

			cout << "                " << std::setw(2) << summ_quant << "        |";
			if (number != -1)
			{
				solution.push_back(number);      //записываем выбранный номер в решение
				flags[number] = true;            //помечаем, что номер выбран
				summ_quant = min;
				razniza = min;
				flag1 = true;
				cout << "  number: " << std::setw(2) << number + 1 << "     " << "|" << "          time: " << std::setw(2) << times[number]
					<< "    |         " << std::setw(2) << razniza << "          |";
			}
			else
			{
				//выход из цикла
				summ_quant = -1;
				cout << " ... ";
			}
		}
	}
	cout << endl << "|_________________________________________________________________________________________________________________|" << endl;
	cout << "Найденное решение: ";
	for (int i = 0; i < kol; i++)
	{
		cout << (solution[i] + 1) << "; ";
	}
	cout << endl;
	system("pause");
}

//для обработки данных с консоли
void case1_from_consol()
{
	int kol = 0;                                             //количество процессов
	int first_quant = 0;                                     //первый, введенный с консоли квант ЦП
	std::string buf = "";                                    //для проверки введенных значений
	int* times;                                              //массив времени выполнения процессов
	bool* flags;                                             //массив уже выбранных процессов

	cout << "Введите количество процессов: " << endl;
	getline(cin, buf);
	if (is_correct_input(buf))
	{
		kol = atoi(buf.c_str());
	}
	times = new int[kol];
	flags = new bool[kol];
	for (int i = 0; i < kol; i++)
	{
		times[i] = 0;
		flags[i] = false;
	}

	cout << "Вводите по очереди время процессов: " << endl;
	for (int i = 0; i < kol;)
	{
		getline(cin, buf);
		if (is_correct_input(buf))
		{
			times[i] = atoi(buf.c_str());
			i++;
		}
	}
	ishod_output(times, kol);

	cout << "Введите начальный квант времени: " << endl;
	getline(cin, buf);
	if (is_correct_input(buf))
	{
		first_quant = atoi(buf.c_str());
	}
	
	Print_table(kol, first_quant, times, flags);
}
	
//для создания случайных данных
void case2_random()
{
	int kol = 0;                                             //количество процессов
	int first_quant = 0;                                     //первый, введенный с консоли квант ЦП
	std::string buf = "";                                    //для проверки введенных значений
	int* times;                                              //массив времени выполнения процессов
	bool* flags;                                             //массив уже выбранных процессов

	kol = 2+rand()%10;
	//cout << "Количество процессов:  " << kol << endl;
	
	times = new int[kol];
	flags = new bool[kol];
	for (int i = 0; i < kol; i++)
	{
		times[i] = 0;
		flags[i] = false;
	}

	for (int i = 0; i < kol; i++)
	{
		times[i] = 1 + rand() % 45;
	}
	ishod_output(times, kol);

	first_quant = 1 + rand() % 49;
	Print_table(kol, first_quant, times, flags);
}

//для чтения данных из файла
void case3_from_file()
{
	int kol = 0;                                             //количество процессов
	int first_quant = 0;                                     //первый, введенный с консоли квант ЦП
	std::string buf = "";                                    //для проверки введенных значений
	int* times;                                              //массив времени выполнения процессов
	bool* flags;                                             //массив уже выбранных процессов

	kol = countWords();
	times = new int[kol];
	flags = new bool[kol];
	for (int i = 0; i < kol; i++)
	{
		times[i] = 0;
		flags[i] = false;
	}

	ifstream in("input.txt", ios::in | ios::binary);

	if (in)
	{
		for (int i = 0; i < kol; i++)
		{
			in >> times[i];
		}
	}
	else
		cout << "FILE ERROR! " << endl;

	in.close(); //Закрываем файл

	ishod_output(times, kol);

	first_quant = 1 + rand() % 49;
	Print_table(kol, first_quant, times, flags);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	while (true)
	{
		system("cls");
		cout << "Введите способ ввода и вывода данныx: (Если вы введете некорректные данные, то придется ввести их заново)\n";
		cout << "1 - Ввод с клавиатуры; \n";
		cout << "2 - Генерация случайным образом; \n";
		cout << "3 - Чтение из файла; \n";
		cout << "4 - Выход; \n";
		char punkt = _getch();
		if ((punkt >= '5') || (punkt <= '0'))
		{
			cout << "НЕ ВЫБРАН ПУНКТ МЕНЮ!" << endl;
			system("pause");
		}

		switch (punkt)
		{
		case '1':
		{
			cout << endl << "---------------выбран 1 пункт - ввод с клавиатуры------------------" << endl;
			case1_from_consol();
			break;
		}
		break;

		case '2':
		{
			cout << endl << "---------------выбран 2 пункт - случайные значения------------------" << endl;
			case2_random();
			break;
		}
		break;

		case '3':
		{
			cout << endl << "---------------выбран 3 пункт - чтение из файла------------------" << endl;
			case3_from_file();
			break;
		}
		break;

		case '4':
		{
			exit(0);
			break;
		}
		break;
		};
	}
}
