#ifndef PIECES_H
#define PIECES_H
#include "Color.h"
#include <iostream>
using namespace std;

struct Piece
{
public:
    explicit Piece(Color c);
	Color color;
};

struct Road : public Piece
{
	explicit Road(Color c);
};

struct Settlement : public Piece
{
public:
	explicit Settlement(Color c);
	static const unsigned int POINT_VALUE = 1;
	friend ostream& operator<<(ostream& out, Settlement& s)
	{
		cout << "Settlement(Color=" << s.color << ")";
		return out;
	}
};

struct City : public Settlement
{
	explicit City(Color c);
    static const unsigned int POINT_VALUE = 2;
	friend ostream& operator<<(ostream& out, City& s)
	{
		cout << "City(Color=" << s.color << ")";
		return out;
	}
};

struct Robber : public Piece
{
	Robber();
	friend ostream& operator<<(ostream& out, Robber& r)
	{
		cout << "Robber";
		return out;
	}
};
#endif
