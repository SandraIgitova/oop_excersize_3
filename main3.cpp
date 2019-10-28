#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>

// координаты в двумерном пространстве
struct _2D
{
	double x;
	double y;
};

// площадь прямоугольника
int comp(const void * a, const void * b) {
	return ((_2D*)a)->x - ((_2D*)b)->x;
}
double Area(_2D A, _2D B, _2D C, _2D D)
{
	_2D mas[4] = { A, B, C, D };
	qsort(mas, 4, sizeof(_2D), comp);	
	if (mas[0].x == mas[1].x) {
		if (mas[0].y > mas[1].y) { _2D hlp = mas[1]; mas[1] = mas[0]; mas[0] = hlp; }
		if (mas[2].y < mas[3].y) { _2D hlp = mas[2]; mas[2] = mas[3]; mas[3] = hlp; }
	}
	else if (mas[1].y < mas[3].y) {_2D hlp = mas[1]; mas[1] = mas[3]; mas[3] = hlp;}

	double d1 = sqrt(pow(mas[1].x - mas[0].x, 2) + pow(mas[1].y - mas[0].y, 2));
	double d2 = sqrt(pow(mas[2].x - mas[1].x, 2) + pow(mas[1].y - mas[2].y, 2));
	return d1 * d2;
};

// площадь треугольника по формуле Герона
double Area(_2D A, _2D B, _2D C)
{
	_2D mas[3] = { A, B, C };
	qsort(mas, 3, sizeof(_2D), comp);
	if (mas[0].x == mas[1].x) 
		if (mas[0].y > mas[1].y) { _2D hlp = mas[1]; mas[1] = mas[0]; mas[0] = hlp; }
	if (mas[1].x == mas[2].x)
		if (mas[2].y > mas[1].y) { _2D hlp = mas[1]; mas[1] = mas[2]; mas[2] = hlp; }
	else if (mas[1].y < mas[2].y) { _2D hlp = mas[1]; mas[1] = mas[2]; mas[2] = hlp; }
	double a = sqrt(pow(mas[1].x - mas[0].x, 2) + pow(mas[1].y - mas[0].y, 2));
	double b = sqrt(pow(mas[1].x - mas[2].x, 2) + pow(mas[2].y - mas[1].y, 2));
	double c = sqrt(pow(mas[2].x - mas[0].x, 2) + pow(mas[0].y - mas[2].y, 2));
	double p = (a + b + c)/2;
	return  sqrt(p*(p - a)*(p - b)*(p - c));
};

// центр прямоугольника
_2D Center(_2D A, _2D B, _2D C, _2D D) {
	_2D Center;
	Center.x = (A.x + B.x + C.x + D.x) / 4;
	Center.y = (A.y + B.y + C.y + D.y) / 4;
	return Center;

}

// центр треугольника
_2D Center(_2D A, _2D B, _2D C) {
	_2D Center;
	Center.x = (A.x + B.x + C.x) / 3;
	Center.y = (A.y + B.y + C.y) / 3;
	return Center;
}

class Figure
{
public:
	_2D m_tops[4];
	_2D m_center;
	double m_area;
	int m_t; // количество углов у фигуры

	Figure(_2D A, _2D B, _2D C)
	{
		m_tops[0].x = A.x;			m_tops[0].y = A.y;
		m_tops[1].x = B.x;			m_tops[1].y = B.y;
		m_tops[2].x = C.x;			m_tops[2].y = C.y;
	}
	Figure(_2D A, _2D B, _2D C, _2D D)
	{
		m_tops[0].x = A.x;			m_tops[0].y = A.y;
		m_tops[1].x = B.x;			m_tops[1].y = B.y;
		m_tops[2].x = C.x;			m_tops[2].y = C.y;
		m_tops[3].x = D.x;			m_tops[3].y = D.y;
	}

	void Output() {
	std::cout << "Координаты вершин:" << std::endl;
	std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		for (int number = 0; number < m_t ; number++) {
			std::cout << "\t" << m_tops[number].x << "\t" << m_tops[number].y << std::endl;
		}
	std::cout << "Координаты центра:" << std::endl;
	std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
	std::cout << "\t" << m_center.x << "\t" << m_center.y << std::endl;

	std::cout << "Площадь фигуры:"  << std::endl;
	std::cout << "\t" << m_area  << std::endl;
	}
};

double TotalArea(std::vector<Figure> &f) {
	double TotalArea =0;
	for (int n = 0; n < f.size(); n++) {
		TotalArea += f[n].m_area;
	}
	return TotalArea;
}

class Triangle: public Figure
{
public:
	Triangle(_2D A, _2D B, _2D C): Figure(A, B, C){
		m_area = Area(A, B, C);
		m_center = Center(A, B, C);
		m_t = 3;
	}
};

class Square: public Figure
{
public:
	Square(_2D A, _2D B, _2D C, _2D D): Figure(A, B, C, D) {
		m_area = Area(A, B, C, D);
		m_center = Center(A, B, C, D);
		m_t = 4;
	}
};

class Rectangle: public Figure
{
public:
	Rectangle(_2D A, _2D B, _2D C, _2D D): Figure(A, B, C, D) {
		m_area = Area(A, B, C, D);
		m_center = Center(A, B, C, D);
		m_t = 4;
	}
};


int main()
{
	uint32_t x = 0;
	std::vector<Figure> figures;
	while (x != 5)
	{
		std::cout << "1. Добавить фигуру в массив\n2. Удалить фигуру из массива\n3. Распечатать для каждой фигуры в массиве геом центр, координаты вершин, площадь\n4. Вычислить общую площадь фигур в массиве\n5. Выход из программы\n\n" << std::endl;
		std::cin >> x;
		std::cout << std::endl;
		if (x == 1) {
			std::cout << "1. Добавить треугольник\n2. Добавить четырехугольник\n\n" << std::endl;
			std::cin >> x;
			if (x == 1) {
				_2D A, B, C;
				std::cout << "Введите x: ";
				std::cin >> A.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> A.y;
				std::cout << std::endl;
				std::cout << "Введите x: ";
				std::cin >> B.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> B.y;
				std::cout << std::endl;
				std::cout << "Введите x: ";
				std::cin >> C.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> C.y;
				std::cout << std::endl;

				figures.push_back(Triangle(A, B, C));
			}
			if (x == 2) {
				_2D A, B, C, D;
				std::cout << "Введите x: ";
				std::cin >> A.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> A.y;
				std::cout << std::endl;
				std::cout << "Введите x: ";
				std::cin >> B.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> B.y;
				std::cout << std::endl;
				std::cout << "Введите x: ";
				std::cin >> C.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> C.y;
				std::cout << std::endl;
				std::cout << "Введите x: ";
				std::cin >> D.x;
				std::cout << "\t";
				std::cout << "Введите y: ";
				std::cin >> D.y;
				std::cout << std::endl;
				figures.push_back(Rectangle(A, B, C, D));
			}
			std::cout << std::endl;
			goto endselection;
		}
		if (x == 2) {
			int index;
			std::cout << "Введите индекс элемента в массиве\n" << std::endl;
			std::cin >> index;
			assert(index >= 0 && index < figures.size());
			figures.erase(figures.begin() + index);
			std::cout << std::endl;
			goto endselection;
		}
		if (x == 3) {
			for (int n = 0; n < figures.size(); n++) {
				std::cout << "Фигура № " << n << std::endl;
				figures[n].Output();
				std::cout << "------------------\n" << std::endl;
			}
			goto endselection;
		}
		if (x == 4) {
			std::cout << "Общая площадь фигур в массиве\n" << std::endl;
			std::cout << TotalArea(figures) << std::endl;
			std::cout << std::endl;
			goto endselection;
		}
	
	endselection:;

	}

    return 0;
}