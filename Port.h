#ifndef PORT_H
#define PORT_H
#include "Coordinate.h"
#include "Resource.h"

struct Port
{
	public:
		Port() : resource(Resource::wild) {}
		Port(Resource r) : resource(r)
	{

	}
		friend ostream& operator<<(ostream& out, Port& p)
		{
			cout << "Port=" << p.resource;
			return out;
		}
		Resource getR()
		{
			return resource;
		}
	private:
		Resource resource;
};
#endif
