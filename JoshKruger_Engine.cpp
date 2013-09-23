//Engine for joshua kruger
#include "Engine.h"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;


bool Engine::FileExists(string filename) //Checks for existance of DataBase/Relations, ourside of currently opened
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

		/*
		
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
			cout<<"Relation Does not exist"<<endl;
	*/


	}//Endof OPEN

	if(TOKENS[0] == "CLOSE")
	{
		DataBase temp; 
		DB = temp;
		cout<<"\n CLOSE SUCCESSFUL!"<<endl;
	}//Endof CLOSE

	if(TOKENS[0] == "WRITE")
	{
		/*
		cout<<" \n WRITING"<<TOKENS[1]<<endl;

		string FileName = TOKENS[1] + ".DB";

		ofstream file (FileName.c_str());

		//Writing DB all commands needed to re make database later
		for(int i=0; i<DB_COMMANDS.size(); i++)
    		file << DB_COMMANDS[i] << endl;

  		
  		file.close();
  		cout<<"\n WRITE COMPLETE"<<endl;
		*/
	}//Endof WRITE

	if(TOKENS[0] == "EXIT")
	{
		cout<<"\n----------"<<endl;
		cout<<"\n   DONE   "<<endl;
		cout<<"\n----------"<<endl; 
		exit(0);
	}//Endof EXIT

	if(TOKENS[0] == "SHOW")
	{
		
	}

	if(TOKENS[0] == "CREATE")
	{

		//CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )


		int Position =0; //Position in command entry
		string RelationName;


		
		if(TOKENS[Position+1] == "TABLE")
		{
			RelationName = TOKENS[Position+2]; //Relation name used to create
			Position+=4; //Move position forard to first value after Parenthesis
			
			
			vector<string> items;
			vector<string> domain;
			vector<string> keys;

			while(true)
			{
				items.push_back(TOKENS[Position]);
				Position++;

				if(TOKENS[Position] == "INTEGER")
				{
					domain.push_back("INTEGER");
					Position++;
				}
				if(TOKENS[Position] == "VARCHAR")
				{
					string varchar = "VARCHAR(";
					Position++;
					Position++;//moving to Value

					varchar+=TOKENS[Position];
					varchar+=TOKENS[Position+1];//Adding closing parenthesis
					domain.push_back(varchar);
					

					Position++;//Closing Parenthesis
					Position++;//next item

				}
				if(TOKENS[Position] == ")") //Ending condidition 
				{
					break;
				}
				if(TOKENS[Position] == ",") //Continue condidtion
				{
					Position++; //Moving to next attribute
				}

			}//Endof finding att-list
			
			Position++;//"PRIMARY"
			Position++;//"KEY"
			Position++;//"("
			Position++;
			while(true) //Key Attributes
			{
				keys.push_back(TOKENS[Position]);
				Position++;

				if(TOKENS[Position] == ",")
				{
					Position++;
				}
				if(TOKENS[Position] ==")")
				{
					break;
				}

			}//END of key atts

			


			if(Create_Table(RelationName,items,domain,keys) == 0) //Creating relation
				cout<<"\n CREATE SUCCESSFUL!"<<endl;

			

		} 
		else
			cout<<"Malformed CREATE syntax"<<endl;


	} //End of CREATE

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



