#ifndef COLOR_H
#define COLOR_H
#include <iostream>
using namespace std;

enum class Color
{
	RED, WHITE, BLUE, GREEN, ORANGE, BROWN
};

ostream& operator <<(ostream& out, Color& c);
#endif
