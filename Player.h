#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <vector>

#include "Color.h"
#include "DevCard.h"
using namespace std;

const unsigned int POINTS_TO_WIN = 10;
enum class strategy // mb = master builder, dev = dev cards, sea = ports
{
	cities, mb, dev, sea
};

class Player
{
	public:
		Player() {}
		Player(string n, Color c) : points(0), name(n), color(c)
	{

	}
		unsigned int roll()
		{
			random_device device;
			default_random_engine engine(device());
			uniform_int_distribution<unsigned int> distribution(1, 6);
			return distribution(engine) + distribution(engine);
		}
		void playDevCard(DevCard card)
		{
			switch (card.type)
			{
				case Type::knight:
					break;
				case Type::road:
					break;
				case Type::monopoly:
					break;
				case Type::year:
					break;
				case Type::point:
					points++;
					break;
				default:
					break;
			}
		}
		int eval()
		{
			return 0;
		}
		int move()
		{
			unsigned int r = roll();
			if (rolls.size() <= 7)
				rolls.push(r);
			else
			{
				rolls.pop();
				rolls.push(r);
			}
			if (points >= POINTS_TO_WIN)
				return 1;
			return 0;
		}
		void addSettlement(Hex * h, settlement& s)
		{
			settlements[h] = &s;
		}
		void addCity(Hex * h, city& c)
		{
			cities[h] = &c;
		}
		void addResource(R r)
		{
			cards[r] += 1;
		}
		bool hasSettlement(Hex * h)
		{
			for (auto p = settlements.begin(); p != settlements.end(); p++)
				if (p->first == h)
					return true;
			return false;
		}
		bool hasCity(Hex * h)
		{
			for (auto p = cities.begin(); p != cities.end(); p++)
				if (p->first == h)
					return true;
			return false;
		}
		void exchange(R given, R taken)
		{
			// DON'T FORGET THE PORTS
			if (cards.at(given) >= 4)
			{
				(cards[given]) -= 4;
			}
			(cards[taken])++;
		}
	private:
		string name;
		Color color;
		map<R, unsigned int> cards;
		map<Hex*, settlement*> settlements;
		map<Hex*, city*> cities;
		queue<unsigned int> rolls;
		unsigned int points;
};
#endif
