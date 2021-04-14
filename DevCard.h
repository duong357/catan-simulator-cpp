#ifndef DEVCARD_H
#define DEVCARD_H
#include "Player.h"
#include "Card.h"

enum class Type
{
	knight, road, monopoly, year, point
};

struct DevCard : public Card
{
	public:
		DevCard(Type t) : type(t)
	{

	}
		Type type;
};
#endif
