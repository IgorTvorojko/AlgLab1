#include <iostream>
#include <vector>
using namespace std;
const int one_step = 1;
const int seed = 5;

void generate_sorted_mass(vector <int>& mass, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		mass[i] = i; // Отсортированный по возрастанию
	}
}

// Генерация почти отсортированного массива (90/10)
void generate_nearly_sorted_mass(vector <int>& mass, int size, int seed)
{
	srand(seed);
	int numSwaps = size / 10;
	int booffer;
	for (int i = 0; i < numSwaps; i++)
	{
		int idx1 = rand() % size;
		int idx2 = rand() % size;
		booffer = mass[idx1];
		mass[idx1] = mass[idx2];
		mass[idx2] = booffer;
	}
}

// Генерация массива, отсортированного в обратном порядке
void generate_reversed_mass(vector <int>& mass, int size)
{
	for (int i = 0; i < size; i++)
	{
		mass[i] = size - i; // Отсортированный по убыванию
	}
}

// Генерация случайного массива с заданным сидом
void generate_random_mass(vector <int>& mass, int size, int seed)
{
	srand(seed);
	for (int i = 0; i < size; ++i)
	{
		mass[i] = rand() % 100; // Заполняем случайными числами от 0 до 99
	}
}

void swap(vector <int>& mass, int index_one_element, int index_two_element)
{
	int buff;
	buff = mass[index_one_element];
	mass[index_one_element] = mass[index_two_element];
	mass[index_two_element] = buff;
}

int permutations(vector <int> & mass, int left, int right, int pivot)
{
	int j = left;
	int i = left;
	while (i <= right)//Проход по всему массиву
	{
		if (mass[i] > pivot)//Если элемент больше чем pivot
		{
			i++;
		}
		else
		{
			swap(mass, i, j);//Смена мест
			i++;
			j++;
		}
	}
	return(j - one_step);//Позиция деления
}

void quick_sort(vector <int> & mass, int left, int right)
{
	if (left < right)//Если массив больше 0
	{
		int pivot = mass[right];//Выбор элемента сравнения
		int pos = permutations(mass, left, right, pivot);//Перемещение
		quick_sort(mass, left, pos - one_step);//Деление массива
		quick_sort(mass, pos + one_step, right);//Деление массива
	}
}

void test(vector <int> & mass, int size)
{
	int ld = mass.size();//Считывание размера массива
	clock_t start = clock();
	quick_sort(mass, 0, ld - one_step);//Сортировка массива
	clock_t end = clock();
	double second = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Время выполнения сортировки: " << second << endl;
}

int main()
{
	setlocale(LC_ALL, "RU");//Подключение локализации
	int i;
	int last_i = 0;
	i = 10000;
	vector <int> mass(i);
	//generate_sorted_mass(mass, i);
	generate_nearly_sorted_mass(mass, i, seed);
	//generate_random_mass(mass, i, seed);
	//generate_reversed_mass(mass, i);
	for (i = 10000; i <= 100000; i++)
	{
		test(mass, i);
	}
}