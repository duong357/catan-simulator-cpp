#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "Color.h"
#include "Piece.h"
#include "Resource.h"
#include "Port.h"
#include "Number.h"
#include "DevCard.h"
using namespace std;

const Resource resourceSet[5] = {Resource::ore, Resource::grain, Resource::lumber, Resource::wool, Resource::brick};

class Game
{
	public:
		Game(unsigned int nop) : numOfPlayers(nop)
	{
		if (numOfPlayers < 2 || numOfPlayers > 4)
			cerr << "Illegal number of players";
		players.push_back(Player("RED", Color::RED));
		players.push_back(Player("BLUE", Color::BLUE));
		if (nop > 2)
			players.push_back(Player("WHITE", Color::WHITE));
		if (nop > 3)
			players.push_back(Player("ORANGE", Color::ORANGE));
		for (unsigned int i = 0; i < 5; i++)
			resources[resourceSet[i]] = 19;
		for (unsigned int i = 0; i < numOfPlayers; i++)
			order.push(players[i]);
	}
		void go(Player& p)
		{
			vector<Tile> tiles = board.getTiles(p.roll());
			unsigned int k = tiles.size();
			for (unsigned int i = 0; i < numOfPlayers; i++) // for each player
			{
				for (unsigned int j = 0; j < k; j++) // gather resources
				{
					break;
				}
				shift();
			}
			if (p.move() == 1) // end game
				exit(0);
			shift();
		}
		void trade(Player& p1, Player& p2, Resource give, Resource take)
		{

		}
		~Game()
		{
		}
	private:
		void shift()
		{
			order.push(order.front());
			order.pop();
		}
		map<Resource, unsigned int> resources;
		vector<Player> players;
		unsigned int numOfPlayers;
		Board board;
		queue<Player> order;
};
#endif
