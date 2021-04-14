#include <ostream>
#include "Color.h"

using namespace std;

ostream &operator<<(ostream &out, Color &c)
{
    switch (c)
    {
        case Color::RED:
            cout << "RED";
            break;
        case Color::WHITE:
            cout << "WHITE";
            break;
        case Color::BLUE:
            cout << "BLUE";
            break;
        case Color::GREEN:
            cout << "GREEN";
            break;
        case Color::ORANGE:
            cout << "ORANGE";
            break;
        case Color::BROWN:
            cout << "BROWN";
            break;
    }
    return out;
}
