#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Jacob Christensen\nCS3060\n\n";

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			cout << argv[i] << '\n';
		}
		cout << '\n';
	}
	else
	{
		cout << "no arguments specified\n";
	}
	
	return 0;
}

