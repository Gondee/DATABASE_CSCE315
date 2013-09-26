//Engine for joshua kruger
#include "Engine.h"
#include <string>
#include <fstream>
#include <iostream>
#include <csignal>


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


			if(DB.exist_Relations(TOKENS[1]) ==0) //Internal test
				//cout<<"Relation Doesnt "<<endl;

			Create_Table(TOKENS[1], Atts, Doms, keys); //Creating table

						

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

			for(int x =0; x < tup.size(); x++)
			{	
				file<<tup[x]<<"|";

			}
			file<<endl;

		}


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

			//cout<<"Create done"<<endl;

		} 
		else
			cout<<"Malformed CREATE syntax"<<endl;


	} //End of CREATE

	if(TOKENS[0] == "UPDATE")
	{
		int next = 1;
		vector<string> complement;
		vector<string> attr, newval;
		
		Relations temp = *(DB.get_Relations(TOKENS[next]));
		Relations temp1, temp2;
		next++;
		while (TOKENS[next]!="WHERE"){
		next++;
		attr.push_back(TOKENS[next]);
		next = next + 2;
		newval.push_back(TOKENS[next]);
		next++;
		}
		next++;
		for (; TOKENS[next]!=")"&&next<TOKENS.size(); next++)
		{
			if(TOKENS[next]!="(" && TOKENS[next]!=",")
				complement.push_back(TOKENS[next]);
		}
		temp1 = conditionshandler("temp", temp, complement);
		temp2 = difference("temp", temp, temp1);

		vector<Attribute*> atts = temp1.get_att_list();
		vector<string> domains_copy, key_copy, att_copy;
	
		for (int i = 0; i < atts.size(); i++)
		{
			att_copy.push_back(atts[i]->get_name());
			domains_copy.push_back(atts[i]->get_domain());
			if (temp1.get_keys()[i])
				key_copy.push_back(atts[i]->get_name());

		}

		DB.create_Table("temp", att_copy, domains_copy, key_copy);

		for (int i = 0; i < temp1.get_num_rows(); i++)
		{
			vector<string> whole = temp1.get_tuple_string(i);
		
			for (int k = 0; k < atts.size(); k++){
				for (int j = 0; j < attr.size(); j++)
				{
					if (atts[k]->get_name()==attr[j])
						whole[k]=newval[j];
				}
			}
			DB.Insert("temp", whole);
		}

		unionize(TOKENS[1], *(DB.get_Relations("temp")), temp2);
	}//end of update


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
			string check = TOKENS[Position];
						if (*check.begin()=='"')
						{
						check.erase(check.begin()); check.erase(check.end()-1);
						}

			Tuple.push_back(check);
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
						check = TOKENS[Position+1];
						if (*check.begin()=='"')
						{
						check.erase(check.begin()); check.erase(check.end()-1);
						}	
						Tuple.push_back(check);
						Position+=2; // Move to next , or to )
					}
				}
			}
			Insert(RelationName,Tuple);
		}
	}

	if(TOKENS[0] == "DELETE")
	{
		int next = 2;
		vector<string> complement;
		
		Relations temp = *(DB.get_Relations(TOKENS[next]));
		
		next = next + 2;

		for (; TOKENS[next]!=")"&&next<TOKENS.size(); next++)
		{
			if(TOKENS[next]!="(" && TOKENS[next]!=",")
				complement.push_back(TOKENS[next]);
		}

		Relations other = conditionshandler("temp", temp, complement);
		difference(temp.get_name(), temp, other);
	}//end of delete




}//End commandParser

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



