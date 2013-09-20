
#include "Relations.h"
#include <iostream>
#include <iomanip>

Relations::Relations(string s, vector<Attribute*> v, vector<bool> k)
{
    
    
	table_name = s;
	att_list = v; 
	keys = k;
         //cout<<"Table size: "<<table.size()<<endl;
         
	for(int i = 0; i < att_list.size(); i++)
	{
            //cout<<"Run"<<i<<endl;
		vector<string*> newvector;
		table.push_back(newvector);
                
	}   
        
}

void Relations::set_tablename(string s)
{
	table_name = s;
}

string Relations::get_name()
{
	return table_name;
}

vector<Attribute*> Relations::get_att_list()
{
	return att_list;
}

int Relations::get_att_list_size()
{
	return att_list.size();
}

Attribute* Relations::get_att(string name)
{
	for(int i = 0; i < att_list.size(); i++)
	{
		if(name == att_list[i]->get_name())
			return att_list[i];
	}
	cout << endl << name << " does not exist in " << get_name();
}

int Relations::show_table()
{	
    
        for(int i = 0; i < att_list.size(); i++)
		cout << setw(10) << att_list[i]->get_name();
    
    
	for(int j = 0; j < table[0].size(); j++)
	{
		cout << endl;
                
		for(int i = 0; i < table.size(); i++)
                {
			cout << setw(10) << *table[i][j];
                }
	}
    
    
	return 0;
}	

int Relations::insert_tuple(vector<string> items)
{
	// Checks for unique key values
	
	for(int i = 0; i < table.size(); i++) 
	{
		if(keys[i]) 
		{
			for(int j = 0; j < table[i].size(); j++)
			{
				if(items[i] == *table[i][j])
				{
					cout << endl <<  items[i] << " is already a key, please insert a new value in " << get_name();
					cout << " please insert a new tuple";			
					return 1;
				}
			}
		}
	}

	for(int i = 0; i < table.size(); i++)
		table[i].push_back(att_list[i]->add_item(items[i]));
		
	return 0;
}

vector<string*> Relations::get_tuple(string item, Attribute* att)
{
	vector<string*> temp;
	int row_num;
	char found = 'n';
	for(int i = 0; i < att_list.size(); i++)
	{
		if(att->get_name() == att_list[i]->get_name())
		{
			for(int j = 0; j < table[i].size(); j++)
			{
				if(item == *table[i][j])
				{
					row_num = j;
					found = 'y';
				}
			}
			
		}
	}
	
	if(found = 'y')
	{
		for(int i = 0; i < att_list.size(); i++)
			temp.push_back(table[i][row_num]);
	}
	if(found = 'n')
	{
		cout << endl << "Tuple not found ";
	}
	
	return temp;
}

int Relations::get_num_rows()
{
	return table[0].size();
}

vector<string*> Relations:: get_tuple_line(int line_num)
{
	vector<string*> temp;
	for(int i = 0; i < att_list.size(); i++)
			temp.push_back(table[i][line_num]);
	return temp;
}
<<<<<<< .mine


		
=======

vector<string> Relations::get_tuple_string(int line_num)
{
	vector<string*> temp = get_tuple_line(line_num);
	vector<string> tuple;
	for (int i = 0; i < temp.size(), i++)
		tuple.push_back(*temp[i]);
	return tuple;

}
>>>>>>> .r66
			
			
			
			
			
			





