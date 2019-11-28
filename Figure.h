#pragma once

#ifndef FIGURE_HPP
#define FIGURE_HPP



struct _2D
{
	double x;
	double y;
};


class Figure
{
public:
	unsigned int m_t;	 // количество вершин в фигуре, необходимо для доступа к методам дочерних классов
				// при извлечении из вектора (преобразовываем Figure* в Triangle* или Rectangle* )

	virtual _2D Center() = 0;
	virtual double Area() = 0;
	virtual void Output() = 0;
};

class Triangle: public Figure
{
public:
	_2D m_tops[3];
	Triangle(_2D A, _2D B, _2D C);

	virtual double Area();
	virtual _2D Center();
	virtual void Output();
};

class Square: public Figure
{
public:
	_2D m_tops[4];
	Square(_2D A, _2D B, _2D C, _2D D);
	virtual double Area();
	virtual _2D Center();
	virtual void Output();
};

class Rectangle: public Figure
{
public:
	_2D m_tops[4];
	Rectangle(_2D A, _2D B, _2D C, _2D D);

	virtual double Area();
	virtual _2D Center();
	virtual void Output();
};

#endif
