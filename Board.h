#ifndef BOARD_H
#define BOARD_H

#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "Piece.h"
#include "Port.h"
#include "Tile.h"

using namespace std;

const unsigned int TILES = 19;
const unsigned char alphabet[TILES] = "abcdefghijklmnopqr"; // Note the null terminator as the last intacter
const unsigned int chipNumber[TILES-1] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
const int presetX[TILES] = {-3, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -1, -2, -1, 1, 2, 1, 0};
const int presetY[TILES] = {0, -2, -3, -4, -3, -2, 0, 2, 3, 4, 3, 2, 1, -1, -2, -1, 1, 2, 0};


class Board
{
	public:
		Board()
		{
			random_device device;
			default_random_engine engine(device());
			uniform_int_distribution<unsigned int> distribution(1, 6);

			map<unsigned int, Resource> numberMap; // map random numbers to resource types
			numberMap[1] = Resource::ore;
			numberMap[2] = Resource::grain;
			numberMap[3] = Resource::lumber;
			numberMap[4] = Resource::wool;
			numberMap[5] = Resource::brick;
			numberMap[6] = Resource::desert;

			map<Resource, unsigned int> resources; // map resource types to number of tiles
			resources[Resource::lumber] = 4;
			resources[Resource::wool] = 4;
			resources[Resource::grain] = 4;
			resources[Resource::ore] = 3;
			resources[Resource::brick] = 3;
			resources[Resource::desert] = 1;

			unsigned int chipCount = 0;
			unsigned int presetIndex = 0;
			while (nonEmptyStack(numberMap, resources) && presetIndex < TILES) // while still handing out resource tiles
			{
				unsigned int roll = distribution(engine);
				if (resources[numberMap[roll]] > 0)
				{
					if (numberMap[roll] == Resource::desert)
						tiles.push_back(Tile(numberMap[roll], Number(), presetX[presetIndex], presetY[presetIndex]));
					else
					{
						tiles.push_back(Tile(numberMap[roll], Number(alphabet[chipCount], chipNumber[chipCount]), presetX[presetIndex], presetY[presetIndex]));
						chipCount++;
					}
					resources[numberMap[roll]] -= 1;
					presetIndex++;
				}
			}
			vector<Hex> temp;
			for (unsigned int i = 0; i < TILES; i++) // add corner hexes
			{
				temp = tiles[i].corners();
				for (unsigned int j = 0; j < 6; j++)
					addCorner(temp[j]);
			}
			robberLocation = pair<Robber, Hex*>(Robber(), &(desert()));
		}
		Hex& at(int a, int b) // return Board Hex with specified coordinates
		{
			for (unsigned int i = 0; i < TILES; i++)
				if (tiles[i].getX() == a && tiles[i].getY() == b)
					return tiles[i];
			Hex temp(a, b);
			for (unsigned int i = 0; i < corners.size(); i++)
				if (corners[i] == temp)
					return corners[i];
			throw GameException("Function Board::at(" + to_string(a) + "," + to_string(b) + "): no such Hex exists!");
		}
		Tile& at(unsigned int letter) // lookup using chip letter
		{
			if (letter == '?')
				return desert();
			if (letter < 'a' || letter > 'r')
				throw GameException("Function Board::at(unsigned int letter) - no such tile exists.");
			for (unsigned int i = 0; i < TILES; i++)
				if (tiles[i].getL() == letter)
					return tiles[i];
			throw GameException("Function Board::at(unsigned int letter) - no such tile exists.");
		}
		void buildCity(int x, int y, Color c)
		{
			buildCity(at(x, y), c);
		}
		void buildSettlement(int x, int y, Color c)
		{
			buildSettlement(at(x, y), c);
		}
		bool connectedRoad(Hex& h1, Hex& h2) // should be recursive function
		{
			vector<Hex> v;
			if (roadExists(h1, h2))
				return true;
			v.push_back(h1);
			vector<Hex> temp = h1.corners();
			for (unsigned int i = 0; i < temp.size(); i++)
				if (cornerExists(temp[i]) && roadExists(temp[i], h2) && !dup(temp[i], v))
					return connectedRoad(temp[i], h2, v);
			return false;
		}
		bool cornerExists(Hex& h) // This function differs from Hex::isCorner() - it actually checks to see of the board has said corner
		{
			unsigned int ci = corners.size();
			for (unsigned int i = 0; i < ci; i++)
				if (corners[i] == h)
					return true;
			return false;
		}
		Tile& desert() // return desert Tile; NOTE: IN EXPANDED CATAN GAME THERE ARE TWO DESERT TILES
		{
			for (unsigned int i = 0; i < TILES; i++)	
				if (tiles[i].getR() == Resource::desert)
					return tiles[i];
			throw GameException("Function Board::desert() - no desert exists. This exception should never come up in a regular Catan game.");
		}
		Resource getR(unsigned int letter)
		{
			return at(letter).getR();
		}
		vector<Tile> getTiles(unsigned int n) // return a vector containing tiles whose number matches n
		{
			vector<Tile> t;	
			for (unsigned int i = 0; i < TILES; i++)
				if (tiles[i].getN() == n)
					t.push_back(tiles[i]);
			return t;
		}
		void moveRobber(int x, int y)
		{
			moveRobber(at(x, y));
		}
		void placeRoad(int x1, int y1, int x2, int y2, Color c)
		{
			placeRoad(at(x1, y1), at(x2, y2), c);
		}
		bool roadExists(int x1, int y1, int x2, int y2)
		{
			return roadExists(at(x1, y1), at(x2, y2));
		}
		friend ostream& operator<<(ostream& out, Board& b)
		{
			unsigned int power = floor(log10(TILES));
#if 0
			// ALTERNATE PRINT FORMAT - SET i(below) to 1 and uncomment this statement
			if (TILES > 0)
				cout << "tiles[" << string(power+1, '0') << "] = " << b.tiles[0];
#endif
			for (unsigned int i = 0; i < TILES; i++)
			{
				cout << "tiles[" << string(power - floor(log10(i)), ' ') << i << "]" << " = " << b.tiles[i];
			}
#if 0
			for (unsigned int i = 0; i < b.corners.size(); i++)
				cout << b.corners[i] << endl;
#endif
			return out;	
		}
	private:
		void addCorner(Hex& h) // you may add a public version later
		{
			for (unsigned int i = 0; i < corners.size(); i++)	
				if (corners[i] == h)
					return;
			corners.push_back(h);
		}
		void addPort(Hex& h, Port& p) // you may add a public version later
		{
			if (!cornerExists(h))
				throw GameException("Function addPort(Hex& h, Port& p): h is not a corner!");
			ports[&h] = p;
		}
		bool adjRoads(Road& r1, Road& r2) // you must call this function using roads from the data member 'roads' - MAKE PRIVATE
		{
			if (!roadExists(r1))
				throw GameException("Function adjRoads(Road& r1, Road& r2): r1 doesn't exist!");
			if (!roadExists(r2))
				throw GameException("Function adjRoads(Road& r1, Road& r2): r2 doesn't exist!");
			Hex h1, h2, h3, h4;
			for (auto p = roads.begin(); p != roads.end(); p++)
				if (&(p->second) == &r1)
				{
					h1 = *(p->first.first);
					h2 = *(p->first.second);
				}
			for (auto p = roads.begin(); p != roads.end(); p++)
				if (&(p->second) == &r2)
				{
					h3 = *(p->first.first);
					h4 = *(p->first.second);
				}
			return (h1 == h3 && h2 != h4) || (h1 == h4 && h2 != h3) || (h2 == h3 && h1 != h4) || (h2 == h4 && h1 != h3);
		}
		void buildCity(Hex& h, Color c)
		{
			settlements.at(&h) = City(c); // map::at(key) checks for nonexistent keys
		}
		void buildSettlement(Hex& h, Color c)
		{
			settlements[&h] = Settlement(c);
		}
		bool connectedRoad(Hex& h1, Hex& h2, vector<Hex>& v)
		{
			if (roadExists(h1, h2))
				return true;
			v.push_back(h1);
			vector<Hex> temp = h1.corners();
			for (unsigned int i = 0; i < temp.size(); i++)
				if (cornerExists(temp[i]) && roadExists(temp[i], h2) && !dup(temp[i], v))
					return connectedRoad(temp[i], h2, v);
			return false;
		}
		bool dup(Hex& h, vector<Hex>& v) // if Road is duplicate (i.e. connectedRoad(); we don't want to call it for a corner we've already checked))
		{
			unsigned int s = v.size();
			for (unsigned int i = 0; i < s; i++)
				if (v[i] == h)
					return true;
			return false;
		}
		Road& getRoad(Hex& h1, Hex& h2)
		{
			if (!h1.isCorner())
				throw GameException("Function getRoad(Hex& h1, Hex& h2): h1 is not a corner Hex!");
			if (!h2.isCorner())
				throw GameException("Function getRoad(Hex& h1, Hex& h2): h2 is not a corner Hex!");
			for (auto p = roads.begin(); p != roads.end(); p++)
				if (p->first == pair<Hex*,Hex*>(&h1, &h2) || p->first == pair<Hex*,Hex*>(&h2, &h1))
					return p->second;
			throw GameException("Function getRoad(Hex& h1, Hex& h2): no Road that connects h1 and h2 exists.");
		}
		void moveRobber(Hex& h)
		{
			if (!h.isTile())
				throw GameException("Function moveRobber(Hex& h): h is not a Tile!");
			robberLocation.second = &h;
		}
		bool nonEmptyStack(map<unsigned int, Resource>& a, map<Resource, unsigned int>& b) // helper function to set up game (i.e. in Board constructor)
		{
			for (unsigned int i = 1; i <= 6; i++)
			{
				if (b[a[i]] != 0)
					return true;
			}
			return false;
		}
		void placeRoad(Hex& h1, Hex& h2, Color c)
		{
			if (!h1.isCorner())
				throw GameException("Function placeRoad(Hex& h1, Hex& h2, Color c): h1 is not a corner Hex!");
			if (!h2.isCorner())
				throw GameException("Function placeRoad(Hex& h1, Hex& h2, Color c): h2 is not a corner Hex!");
			roads[pair<Hex*, Hex*>(&h1, &h2)] = Road(c);
		}
		bool roadExists(Hex& h1, Hex& h2)
		{
			if (!h1.isCorner())
				throw GameException("Function roadExists(Hex& h1, Hex& h2): h1 is not a corner Hex!");
			if (!h2.isCorner())
				throw GameException("Function roadExists(Hex& h1, Hex& h2): h2 is not a corner Hex!");
			for (auto p = roads.begin(); p != roads.end(); p++)
				if (p->first == pair<Hex*,Hex*>(&h1, &h2) || p->first == pair<Hex*,Hex*>(&h2, &h1))
					return true;
			return false;
		}
		bool roadExists(Road& r) // note the reference parameter - you need to use getRoad() or some other Road&
		{
			for (auto p = roads.begin(); p != roads.end(); p++)
				if (&(p->second) == &r)
					return true;
			return false;
		}
		bool tileExists(Tile& t) // This function differs from Hex::isTile() - it actually checks to see of the board has said tile
		{
			unsigned int ti = tiles.size();
			for (unsigned int i = 0; i < ti; i++)
				if (tiles[i] == t)
					return true;
			return false;
		}
		vector<Tile> tiles;
		vector<Hex> corners;
		map<pair<Hex*, Hex*>,Road> roads;
		map<Hex*, Settlement> settlements;
		map<Hex*, Port> ports;
		pair<Robber, Hex*> robberLocation;
};
#endif
