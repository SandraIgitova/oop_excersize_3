#include "Figure.h"
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>

int comp(const void * a, const void * b) {
	return ((_2D*)a)->x - ((_2D*)b)->x;
}

bool IsRectangle(_2D A, _2D B, _2D C, _2D D) {
	_2D mas[4] = { A, B, C, D };
	qsort(mas, 4, sizeof(_2D), comp); // для введения точек в произвольном порядке	
	if (mas[0].x == mas[1].x) {
		if (mas[0].y > mas[1].y) { _2D hlp = mas[1]; mas[1] = mas[0]; mas[0] = hlp; }
		if (mas[2].y < mas[3].y) { _2D hlp = mas[2]; mas[2] = mas[3]; mas[3] = hlp; }
	}
	else if (mas[1].y < mas[3].y) { _2D hlp = mas[1]; mas[1] = mas[3]; mas[3] = hlp; }
	_2D vector1, vector2, vector3, vector4;
	vector1.x = mas[1].x - mas[0].x; vector1.y = mas[1].y - mas[0].y;
	vector2.x = mas[2].x - mas[1].x; vector2.y = mas[2].y - mas[1].y;
	vector3.x = mas[3].x - mas[2].x; vector3.y = mas[3].y - mas[2].y;
	vector4.x = mas[0].x - mas[3].x; vector4.y = mas[0].y - mas[3].y;
	// проверяем три угла скалярными произведениями
	if (((vector1.x * vector2.x + vector1.y * vector2.y) == 0) && ((vector3.x * vector2.x + vector3.y * vector2.y) == 0) && ((vector4.x * vector3.x + vector4.y * vector3.y) == 0)) {
		return true;
	}
	else { return false; }

}

bool IsSquare(_2D A, _2D B, _2D C, _2D D) {
	_2D mas[4] = { A, B, C, D };
	qsort(mas, 4, sizeof(_2D), comp); // для введения точек в произвольном порядке	
	if (mas[0].x == mas[1].x) {
		if (mas[0].y > mas[1].y) { _2D hlp = mas[1]; mas[1] = mas[0]; mas[0] = hlp; }
		if (mas[2].y < mas[3].y) { _2D hlp = mas[2]; mas[2] = mas[3]; mas[3] = hlp; }
	}
	else if (mas[1].y < mas[3].y) { _2D hlp = mas[1]; mas[1] = mas[3]; mas[3] = hlp; }
	double d1 = sqrt(pow(mas[1].x - mas[0].x, 2) + pow(mas[1].y - mas[0].y, 2));
	double d2 = sqrt(pow(mas[2].x - mas[1].x, 2) + pow(mas[1].y - mas[2].y, 2));
	_2D vector1, vector2, vector3, vector4;
	vector1.x = mas[1].x - mas[0].x; vector1.y = mas[1].y - mas[0].y;
	vector2.x = mas[2].x - mas[1].x; vector2.y = mas[2].y - mas[1].y;
	vector3.x = mas[3].x - mas[2].x; vector3.y = mas[3].y - mas[2].y;
	vector4.x = mas[0].x - mas[3].x; vector4.y = mas[0].y - mas[3].y;
	// проверяем два угла скалярными произведениями и равенство сторон	
	if (((vector1.x * vector2.x + vector1.y * vector2.y) == 0) && ((vector3.x * vector2.x + vector3.y * vector2.y) == 0) && ((vector4.x * vector3.x + vector4.y * vector3.y) == 0) && (d1 == d2)){
		return true;
	}
	else { return false; }
}


double TotalArea(std::vector<Figure*> &figures) {	// площадь всех фигур из вектора
	double TotalArea = 0;
	for (uint n = 0; n < figures.size(); n++) { // обращаемся в векторе
		if (figures[n]->m_t == 3) {				// к фигурам разных классов
			TotalArea += ((Triangle*)figures[n])->Area();// (треугольник или четырехугольник)
		}
		if (figures[n]->m_t == 4) {
			TotalArea += ((Rectangle*)figures[n])->Area();
		}
	}
	return TotalArea;
}


void MainMenuOutput(uint32_t& x) {
	std::cout << "\
1. Добавить фигуру в массив\n\
2. Удалить фигуру из массива\n\
3. Распечатать для каждой фигуры в массиве геом центр, координаты вершин, площадь\n\
4. Вычислить общую площадь фигур в массиве\n\
Ctrl-D Выход из программы\n\n" << std::endl;
	std::cin >> x;
	std::cout << std::endl;
}

void FigureMenuOutput(uint32_t& x) {
	std::cout << "\
1. Добавить треугольник\n\
2. Добавить четырехугольник\n\n" << std::endl;
	std::cin >> x;
}

void TriangleInput(std::vector<Figure*>& figures) {
	_2D A, B, C;
	std::cout << "Введите 6 чисел координат сторон треугольника, чередуя X и Y: \n";
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	figures.push_back(new Triangle(A, B, C));
}

void RectangleInput(std::vector<Figure*>& figures) {
	_2D A, B, C, D;
	std::cout << "Введите 8 чисел координат сторон четырехугольника, чередуя X и Y: \n";
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
	if (IsRectangle(A, B, C, D)) {
		figures.push_back(new Rectangle(A, B, C, D));
	}
	else std::cout << "Это не прямоугольник\n";
	if (IsSquare(A, B, C, D)) {
		std::cout << "Данный прямоугольник является квадратом:" << std::endl;
	}
}

void IndexInput(std::vector<Figure*>& figures) {
	uint index;
	std::cout << "Введите индекс элемента в массиве\n" << std::endl;
	std::cin >> index;
	if (index > figures.size() - 1) {
		std::cout << "Недопустимый индекс\n" << std::endl;
	}
	else figures.erase(figures.begin() + index);
	std::cout << std::endl;
}

void FiguresOutput(std::vector<Figure*>& figures) {
	std::cout << "Вывод с всех фигур" << std::endl;
	for (uint n = 0; n < figures.size(); n++) {
		std::cout << "Фигура № " << n << std::endl;
		if (figures[n]->m_t == 3) {				// обращаемся в векторе
			((Triangle*)figures[n])->Output();	// к фигурам разных классов
		}										// (треугольник или четырехугольник)
		if (figures[n]->m_t == 4) {
			((Rectangle*)figures[n])->Output();
		}
		std::cout << "------------------\n" << std::endl;
	}
}

void Area(std::vector<Figure*>& figures) {
	std::cout << "Общая площадь фигур в массиве\n" << std::endl;
	std::cout << TotalArea(figures) << std::endl; 
	std::cout << std::endl;
}
// --------------------

int main()
{
	uint32_t x = 0;
	std::vector<Figure*> figures;
	while (std::cin)
	{
		MainMenuOutput(x);
		if (x == 1) {
			FigureMenuOutput(x);
			if (x == 1) {
				TriangleInput(figures);
			}
			if (x == 2) {
				RectangleInput(figures);
			}
			continue;
		}
		if (x == 2) {
			IndexInput(figures);
			continue;
		}
		if (x == 3) {
			FiguresOutput(figures);
			continue;
		}
		if (x == 4) {
			Area(figures);
		}
	}
	return 0;
}