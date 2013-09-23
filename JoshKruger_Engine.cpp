//Engine for joshua kruger
#include "Engine.h"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;


bool Engine::FileExists(string filename)
{
   ifstream f(filename.c_str());
    if (f.good()) 
    {
        f.close();
        return true;
    } 
    else 
    	{
        	f.close();
        	return false;
    	}  
}



void Engine::commandParser(vector<string> TOKENS)
{

	//( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd ) ;

	if(TOKENS[0] == " " || TOKENS[0] == "" || TOKENS[0] == ";")
	{
		cout<<" \n BAD COMMAND"<<endl;
		//Error system goes here
	}

	if(TOKENS[0] == "OPEN")
	{
		cout<<" \n OPENING"<<TOKENS[1]<<endl;
		if(FileExists(TOKENS[1]))
		{
			DB_COMMANDS.clear();

			
    		string STRING;
    		ifstream infile;
    		string FileName = TOKENS[1] + ".DB";
    		infile.open (FileName.c_str());
    		while(getline(infile,STRING)) // To get you all the lines.
    		{
        		DB_COMMANDS.push_back(STRING);
        		//cout<<STRING<<endl;
    		}
    		infile.close();

		}
		else 
			cout<<"DataBase Does not exist"<<endl;


	}

	if(TOKENS[0] == "CLOSE")
	{
		cout<<" \n CLOSING"<<TOKENS[1]<<endl;
		DataBase temp; 
		DB = temp;
	}

	if(TOKENS[0] == "WRITE")
	{
		cout<<" \n WRITING"<<TOKENS[1]<<endl;

		string FileName = TOKENS[1] + ".DB";

		ofstream file (FileName.c_str());

		//Writing DB all commands needed to re make database later
		for(int i=0; i<DB_COMMANDS.size(); i++)
    		file << DB_COMMANDS[i] << endl;

  		
  		file.close();
  		cout<<"\n WRITE COMPLETE"<<endl;
		
	}

	if(TOKENS[0] == "EXIT")
	{
		cout<<"\n----------"<<endl;
		cout<<"\n   DONE   "<<endl;
		cout<<"\n----------"<<endl; 
		exit(0);
	}

	if(TOKENS[0] == "SHOW")
	{
		
	}

	if(TOKENS[0] == "CREATE")
	{
		
	}

	if(TOKENS[0] == "UPDATE")
	{
		
	}

	if(TOKENS[0] == "INSERT")
	{
		
	}

	if(TOKENS[0] == "DELETE")
	{
		
	}





}//End commandParser



