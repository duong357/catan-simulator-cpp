#ifndef gEXCEPTION
#define gEXCEPTION
#include <iostream>
#include <string>
using namespace std;
class GameException
{
	public:
		GameException(string s) : message(s)
	{
		cout << "GameException: " << s << endl << "Abort program!" << endl;
	}
	private:
		string message;
};
#endif
