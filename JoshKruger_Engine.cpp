//Engine for joshua kruger
#include "Engine.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>


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

int Engine::Insert_From_Relation(string R1, string R2)
{
	Relations * rel1,* rel2;
	rel1 = DB.get_Relations(R1);
	rel2 = DB.get_Relations(R2);
	
	if(!Union_Compatible(*rel1, *rel2)) // Check to see if tuple from R2 can be inserted into R1
		return 1;
	
	for(int i = 0; i < rel2->get_num_rows(); i++)
	{
		vector<string> Tuple = rel2->get_tuple_string(i);
		DB.Insert(R1,Tuple);
	}
	
	return 0;
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
		string FileName = TOKENS[1] + ".DB";

		if(FileExists(FileName))
		{
			vector<string> FILE;	
    		string STRING;
    		ifstream infile;
    		
    		infile.open (FileName.c_str());

    		while(getline(infile,STRING)) // To get you all the lines.
    		{
        		FILE.push_back(STRING);
        		
    		}
    		infile.close(); //Done reading, now to parsing vector
			
    		vector<string> keys;
    		vector<string> Atts;
    		vector<string> Doms;
    		vector<string> Ritems;

    		bool keysB = false;
    		bool attlistB = false;
    		bool tableB = false;

    		int POS =0; 
    		while(true)
    		{
    			if(FILE[POS] =="KEYS")
    			{
    				keysB = true;
    				POS++;
    			}

    			if(keysB = true)
    			{
    				keys.push_back(FILE[POS]);
    				POS++;
    			}

    			if(FILE[POS]=="----")
    			{
    				POS++;
    				break;

    			}

    		}


    		string att_name = FILE[POS];
    		POS++;
    		string att_domain = FILE[POS];
    		POS++;


    		while(true)
    		{
    			if(FILE[POS]=="-----")
    			{
    				//cout<<"ENDOF attributes"<<endl;
    				break;
    			}

    			//cout<<"LOOP"<<endl;
    		Ritems.push_back(FILE[POS]);
    		POS++;



    		if(FILE[POS] == "---") //Add relation and check for another
    		{	
    			//cout<<"ATTRBUTE"<<endl;

    			//cout<<"Attribute name: "<<att_name<<" domain: "<<att_domain<<endl;
    			DB.add_Attribute(new Attribute(att_name,att_domain));
    			Atts.push_back(att_name);
    			Doms.push_back(att_domain);

    			for(int i =0;i<Ritems.size();i++)
    			{
    			DB.get_Attribute(att_name)->add_item(Ritems[i]);
    			}

    			if(FILE[POS+1]=="-----")
    			{
    				//cout<<"ENDOF attributes"<<endl;
    				break;
    			}

    			POS++;
    			att_name = FILE[POS];
    			POS++;
    			att_domain = FILE[POS];
    			POS++;
    			Ritems.clear();

    		}

    		}//end of Attributes and items list


    		
    		POS++;//--- (3) //markers in file
    		POS++;//----- (5)
    		
    		vector<string> TUPLES;
    		while(FILE[POS] != "--") //pulling tokens
    		{
    			TUPLES.push_back(FILE[POS]);
    			POS++;

    		}
			POS =0;


			if(DB.exist_Relations(TOKENS[1]) ==0)
				cout<<"Relation Doesnt still"<<endl;
<<<<<<< HEAD

			Create_Table(TOKENS[1], Atts, Doms, keys); //Creating table

			//cout<<DB.get_Relations(TOKENS[1])->get_att_list_size()<<endl;

 			View(TOKENS[1]);			

    		while(POS < TUPLES.size())
    		{
    			vector<string> tup;
    			string t = TUPLES[POS];
    			POS++;
    			string item_build ="";

    			for(int i =0; i<t.length(); i++)
    			{
    				if(t[i] != '|')
    				{
    					item_build += t[i];
    				}
    				else if(t[i]=='|')
    				{

    					tup.push_back(item_build);
    					item_build ="";
    				}

    			}
    			DB.Insert(TOKENS[1],tup);
=======
>>>>>>> f9ffa672f88b1699527368eb67ab3894f53dbdf7

			Create_Table(TOKENS[1], Atts, Doms, keys); //Creating table

			//cout<<DB.get_Relations(TOKENS[1])->get_att_list_size()<<endl;

 			View(TOKENS[1]);			

<<<<<<< HEAD
=======
    		while(POS < TUPLES.size())
    		{
    			vector<string> tup;
    			string t = TUPLES[POS];
    			POS++;
    			string item_build ="";

    			for(int i =0; i<t.length(); i++)
    			{
    				if(t[i] != '|')
    				{
    					item_build += t[i];
    				}
    				else if(t[i]=='|')
    				{

    					tup.push_back(item_build);
    					item_build ="";
    				}

    			}
    			DB.Insert(TOKENS[1],tup);




>>>>>>> f9ffa672f88b1699527368eb67ab3894f53dbdf7
    		}



    		cout<<"\n OPEN SUCCESSFUL!"<<endl;
		}
		else 
			{
				cout<<"REALTION DOES NOT EXIST"<<endl;
			}
	}//Endof OPEN

	if(TOKENS[0] == "CLOSE")
	{

		if(DB.remove_Relation(TOKENS[1]) ==0)
			cout<<"\n CLOSE SUCCESSFUL!"<<endl;

	}//Endof CLOSE

	if(TOKENS[0] == "WRITE")
	{

		
		cout<<" \n WRITING"<<TOKENS[1]<<endl;
		string FileName = TOKENS[1] + ".DB";
		ofstream file (FileName.c_str());

		vector<Attribute*> Alist;
		Alist = (DB.get_Relations(TOKENS[1])->get_att_list()); //Gets the table

		file<<"KEYS"<<endl;//Signifing keys are starting


			//ADDING KEYS

		vector<bool> keybool; 
		keybool = DB.get_Relations(TOKENS[1])->get_keys();

		for(int i = 0; i < Alist.size(); i++)
		{
			if(keybool[i] == true)
			{
				file<<Alist[i]->get_name()<<endl; //Writing name of key!
			}

		}

			//KEYS ADDED
		file<<"----"<<endl; //Shows end of keys, usful for reading

			//ADDING ATTRIBUTES
		for(int i=0; i<Alist.size(); i++)
		{
			file <<Alist[i]->get_name()<< endl;
			file <<Alist[i]->get_domain()<< endl;
			vector<string*> tempitems;
			tempitems = Alist[i]->get_items();

			for(int x =0; x < Alist[i]->get_items().size(); x++)
			{
				file<<*(tempitems[x])<<endl;

			}
			file<<"---"<<endl;
    		
		}

		file<<"-----"<<endl;//(5) -'s means end of Attributes
		
		for(int i =0; i < DB.get_Relations(TOKENS[1])->get_num_rows(); i++)
		{
			vector<string> tup;
			tup = DB.get_Relations(TOKENS[1])->get_tuple_string(i);
<<<<<<< HEAD

			for(int x =0; x < tup.size(); x++)
			{	
				file<<tup[x]<<"|";
=======

			for(int x =0; x < tup.size(); x++)
			{	
				file<<tup[x]<<"|";

			}
			file<<endl;

		}
>>>>>>> f9ffa672f88b1699527368eb67ab3894f53dbdf7

			}
			file<<endl;

<<<<<<< HEAD
		}


=======
>>>>>>> f9ffa672f88b1699527368eb67ab3894f53dbdf7
		file<<"--"<<endl;
  		file.close();
  		cout<<"\n WRITE COMPLETE"<<endl;
		

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
		//show-cmd ::== SHOW atomic-expr 
		//Relations expressionParser(string, vector<string>);

		vector<string> Atomic_Expr; 
		for(int i = 0; i < TOKENS.size();i++)
		{
			if(TOKENS[i] != "SHOW")
			{
				Atomic_Expr.push_back(TOKENS[i]);
			}

		}

		Relations temp = expressionParser("temp",Atomic_Expr);
		temp.show_table(); //WORK please
		cout<<"\n SHOW SUCCESSFUL!"<<endl;


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
		int Position = 0;
		string RelationName;
		
		RelationName = TOKENS[Position+2]; //Items will be inserted into this relation
		Position+=5; //Move position forward past INTO, relation name, and VALUES FROM
		
		if(TOKENS[Position] == "RELATION")
		{
			Position++; // Move position to first (
			
			vector<string> Insert_Expression;
			Insert_Expression.push_back(TOKENS[Position]);
			Position++;
			int parenthesis_count = 1;
			
			while(parenthesis_count != 0)
			{			
				if(TOKENS[Position] == "(")
					parenthesis_count++;
				if(TOKENS[Position] == ")")
					parenthesis_count--;
				
				Insert_Expression.push_back(TOKENS[Position]);
				Position++;
			}
			
			Relations temp = expressionParser("temp", Insert_Expression);
			Insert_From_Relation(RelationName, "temp");	
			
		}
		else
		{
			vector<string> Tuple;
			Position++; // Move position to first value
			Tuple.push_back(TOKENS[Position]);
			Position++; // Move to , or )
			while(TOKENS[Position] != ")")
			{
				if(TOKENS[Position] == ",")
				{
					if(TOKENS[Position+1] == ")")
					{
						Position++;
					}
					else
					{
						Tuple.push_back(TOKENS[Position+1]);
						Position+=2; // Move to next , or to )
					}
				}
			}
			Insert(RelationName,Tuple);
		}
	}

	if(TOKENS[0] == "DELETE") //Not Done
	{
		int Position =0;
		Position++;
		string RN; //RelationName
		string Att; //Attribute in Question
		string OPP; //Operation to be peformed 
		string Number; //INTEGER to be computed against

		if(TOKENS[Position] == "FROM")
		{
			Position++;
			RN = TOKENS[Position];
			Position++;//"WHERE"
			Position++;//"("

			Position++;//ATT
			Att = TOKENS[Position];
			Position++;
			OPP = TOKENS[Position];
			Position++;
			Number = TOKENS[Position];

			vector<string> Condition_Expression;
			Condition_Expression.push_back("select");
			Condition_Expression.push_back("(");
			Condition_Expression.push_back(Att);
			Condition_Expression.push_back(OPP);
			Condition_Expression.push_back(Number);
			Condition_Expression.push_back(")");

			Relations temp = expressionParser("temp", Condition_Expression);
			

			Condition_Expression.clear();
			Condition_Expression.push_back("select");
			Condition_Expression.push_back(RN);

			Relations Original = expressionParser("tempone", Condition_Expression);


			Relations temp_Diff = difference("RDiff", temp, Original);




		}

		
		
	}





}//End commandParser



