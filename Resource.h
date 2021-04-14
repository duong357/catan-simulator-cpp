#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>
using namespace std;

enum class Resource
{
	ore, grain, lumber, wool, brick, desert, sea, wild 
};

ostream& operator<<(ostream& out, Resource r)
{
	switch (r)
	{
		case Resource::ore:
			cout << "rock";
			break;
		case Resource::grain:
			cout << "wheat";
			break;
		case Resource::lumber:
			cout << "wood";
			break;
		case Resource::wool:
			cout << "sheep";
			break;
		case Resource::brick:
			cout << "brick";
			break;
		case Resource::desert:
			cout << "desert";
			break;
		default:
			cout << "none";
			break;
	}
	return out;
}
#endif
