#include "Figure.h"
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>


//------------------- математика------------------------------
// площадь прямоугольника
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
	_2D vector1, vector2, vector3;
	vector1.x = mas[1].x - mas[0].x; vector1.y = mas[1].y - mas[0].y;
	vector2.x = mas[2].x - mas[1].x; vector2.y = mas[2].y - mas[1].y;
	vector3.x = mas[3].x - mas[2].x; vector3.y = mas[3].y - mas[2].y;
	// проверяем два угла скалярными произведениями и равенство сторон	
	if (((vector1.x * vector2.x + vector1.y * vector2.y) == 0) && ((vector3.x * vector2.x + vector3.y * vector2.y) == 0) && ((vector4.x * vector3.x + vector4.y * vector3.y) == 0) && (d1 == d2)){
		return true;
	}
	else { return false; }
}


double RectangleArea(_2D A, _2D B, _2D C, _2D D)
{
	_2D mas[4] = { A, B, C, D };
	qsort(mas, 4, sizeof(_2D), comp); // для введения точек в произвольном порядке	
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
double TriangleArea(_2D A, _2D B, _2D C)
{
	_2D mas[3] = { A, B, C };
	qsort(mas, 3, sizeof(_2D), comp); // для введения точек в произвольном порядке
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
_2D RectangleCenter(_2D A, _2D B, _2D C, _2D D) {
	_2D Center;
	Center.x = (A.x + B.x + C.x + D.x) / 4;
	Center.y = (A.y + B.y + C.y + D.y) / 4;
	return Center;
}
// центр треугольника
_2D TriangleCenter(_2D A, _2D B, _2D C) {
	_2D Center;
	Center.x = (A.x + B.x + C.x) / 3;
	Center.y = (A.y + B.y + C.y) / 3;
	return Center;
}
// ---------------- конец математики ----------------------

// ---------------- классы --------------------------------

//Triangle kek

Triangle::Triangle(_2D A, _2D B, _2D C){
		m_tops[0].x = A.x;			m_tops[0].y = A.y;
		m_tops[1].x = B.x;			m_tops[1].y = B.y;
		m_tops[2].x = C.x;			m_tops[2].y = C.y;
		m_t = 3;
	}

	double Triangle::Area() {
		return TriangleArea(m_tops[0], m_tops[1], m_tops[2]);
	}
	 _2D Triangle::Center() {
		return TriangleCenter(m_tops[0], m_tops[1], m_tops[2]);
	}
	void Triangle::Output() {
		std::cout << "Координаты вершин:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		for (int number = 0; number < m_t; number++) {
			std::cout << "\t" << m_tops[number].x << "\t" << m_tops[number].y << std::endl;
		}
		std::cout << "Координаты центра:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		_2D m_center = Center();
		std::cout << "\t" << m_center.x << "\t" << m_center.y << std::endl;

		std::cout << "Площадь треугольника:" << std::endl;
		std::cout << "\t" << Area() << std::endl;
	}


//Square kek

Square::Square(_2D A, _2D B, _2D C, _2D D){
		m_tops[0].x = A.x;			m_tops[0].y = A.y;
		m_tops[1].x = B.x;			m_tops[1].y = B.y;
		m_tops[2].x = C.x;			m_tops[2].y = C.y;
		m_tops[3].x = D.x;			m_tops[3].y = D.y;
		m_t = 4;
	}
	double Square::Area() {
		return RectangleArea(m_tops[0], m_tops[1], m_tops[2], m_tops[3]);
	}
	_2D Square::Center() {
		return RectangleCenter(m_tops[0], m_tops[1], m_tops[2], m_tops[3]);
	}
	void Square::Output() {
		std::cout << "Координаты вершин:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		for (int number = 0; number < m_t; number++) {
			std::cout << "\t" << m_tops[number].x << "\t" << m_tops[number].y << std::endl;
		}
		std::cout << "Координаты центра:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		_2D m_center = Center();
		std::cout << "\t" << m_center.x << "\t" << m_center.y << std::endl;

		std::cout << "Площадь квадрата:" << std::endl;
		std::cout << "\t" << Area() << std::endl;
	}

//Rectangle kek

Rectangle::Rectangle(_2D A, _2D B, _2D C, _2D D){
		m_tops[0].x = A.x;			m_tops[0].y = A.y;
		m_tops[1].x = B.x;			m_tops[1].y = B.y;
		m_tops[2].x = C.x;			m_tops[2].y = C.y;
		m_tops[3].x = D.x;			m_tops[3].y = D.y;
		m_t = 4;
	}

	double Rectangle::Area() {
		return RectangleArea(m_tops[0], m_tops[1], m_tops[2], m_tops[3]);
	}

	_2D Rectangle::Center() {
		return RectangleCenter(m_tops[0], m_tops[1], m_tops[2], m_tops[3]);
	}
	
	void Rectangle::Output() {
		std::cout << "Координаты вершин:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		for (int number = 0; number < m_t; number++) {
			std::cout << "\t" << m_tops[number].x << "\t" << m_tops[number].y << std::endl;
		}
		std::cout << "Координаты центра:" << std::endl;
		std::cout << "\t" << "X" << "\t" << "Y" << std::endl;
		_2D m_center = Center();
		std::cout << "\t" << m_center.x << "\t" << m_center.y << std::endl;

		std::cout << "Площадь прямоугольника:" << std::endl;
		std::cout << "\t" << Area() << std::endl;

		if (IsSquare(m_tops[0], m_tops[1], m_tops[2], m_tops[3])) {
			std::cout << "Данный прямоугольник является квадратом:" << std::endl;
		}
	}