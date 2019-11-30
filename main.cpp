#include "Figure.h"
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>

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