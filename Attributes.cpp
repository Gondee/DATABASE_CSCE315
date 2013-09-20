#include "Attributes.h"
#include <stdlib.h>
#include <iostream>

Attribute::Attribute(string n, string d)
{
	name = n;
	domain = d;
}

string Attribute::get_name()
{
	return name;
}

void Attribute::set_name(string s)
{
	name = s;
}

//returns domain string, with a check the user should know what king it is
string Attribute::get_domain()
{
	return domain;
}

//stores user domain inside a string, need way to parse this later
void Attribute::set_domain(string d)
{ 
	domain = d;
}

bool Attribute::check_domain(string s)
{
	if(domain == "INTEGER")
	{
		for(int i = 0; i < s.length(); i++)
		{
			if(!isdigit(s[i]))
				return false;
		}
		return true;
	}
	
	if(domain.find("VARCHAR") == 0)
	{
		int first_pos = domain.find('(');
		int last_pos = domain.find(')');
		string char_length = domain.substr(first_pos+1,last_pos-first_pos-1); // stores # of VARCHAR 
		int length = atoi(char_length.c_str());
		if(s.length() > length)
		{
			cout << endl << s << " has too many characters (domain is " << length << " characters";
			return false;
		}
		else	
			return true;
	}
}
		
//returns the list of items in vector format, not by reference
vector<string*> Attribute::get_items()
{ 
	return items; 
}



string* Attribute::get_item(string s)
{	
	string* sp; // pointer to item
	for(int i = 0; i < items.size(); i++)
	{
		if(s == *items[i])
		{
			sp = items[i];
			return sp;
		}
	}
	
	cout << "Item not found"; 
	return NULL; // Need to have error message here in case item is not found
}

int Attribute::items_size()
{
	return items.size();
}

string* Attribute::add_item(string s) 
{ 	
	if(!check_domain(s)) 
		//cout << "FAILED DOMAIN";
	
	for(int i = 0; i < items.size(); i++)
	{
		if(s == *items[i])
			return items[i];
	}
	
// Checks for empty spots in items vector
	for(int i = 0; i < items.size(); i++)
	{
		if(*items[i] == "NULL")
		{
			*items[i] = s;
			return items[i];
		}
	}
	items.push_back(new string(s)); // Inserts item
	return items.back();
}

// Changes item to NULL (therefore vector is kept in tact, all items still have same spot)
int Attribute::remove_item(string s)
{
	int exist = 0;

	for(int i = 0; i < items.size(); i++)
	{
		if(s == *items[i])
		{
			exist = 1;
			*items[i] = "NULL";
		}
	}
	
	if(!exist)
		return 1; //Something went wrong, item did not exist

	return 0;
}	

void Attribute::print_items()
{
	for(int i = 0; i < items.size(); i++)
	{
		cout << items[i] << endl;
	}
}



bool operator== (Attribute &cP1, Attribute &cP2)
{
    
	bool dd = false;
	bool nn = false;
	bool all_values_same = true;
	bool itemVec_size = false;
	//bool ii = false;

	if(cP1.get_name() == cP2.get_name())
	{
		nn = true;
	}
	if(cP1.get_domain() == cP2.get_domain())
	{
		dd = true; 
	}

	if(cP1.get_items().size() == cP2.get_items().size())
	{
		itemVec_size = true;

		for(int i =0; i < cP1.get_items().size(); i++)
		{
			if(cP1.get_items()[i] != cP2.get_items()[i])
			{
				all_values_same = false;

			}


		}

	}


	if(dd==true && nn==true &&all_values_same ==true &&itemVec_size==true)
	{
		return true;
	}


    return false;
}
