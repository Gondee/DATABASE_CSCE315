#include "Parser.h"
#include "Engine.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
cout<<" "<<endl;
cout<<"\t Integrated Parser + DBMS system"<<endl;
cout<<"\t -----------"<<endl;

Parse p;
Engine e;

	while(true)
	{
		string command;
		getline (cin, command);
		p.Tokenize(command);
		p.Begin_Parse();
		e.chooseParser(p.get_tokens());

	}

}