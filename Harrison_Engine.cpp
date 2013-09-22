#include "Engine.h"





















//Below is no longer needed -joshk

/*
int Engine::Create_Table(string n, vector<string> a, vector<string> d, vector<string> k)
{
	if(exist_Relations(n))
		return 1; // A relation with that name already exists
		
	return DB.create_Table(n, a, d, k);
}

int Engine::Insert(string n, vector<string> i)
{
	Relations* temp;
	
	if(!exist_Relations(n))
		return 1; // A relation with name n does not exist
		
	temp = DB.get_Relations(n);
	if(temp->get_att_list_size() != i.size())
		return 1; // Tuple does not contain all the required strings (# of attributes != # of strings)
		
	return DB.Insert(n, i);
}

int Engine::View(string n)
{
	if(exist_Relations(n))
		return 1; // A relation with that name already exists
		
	return DB.show_table(n);
}
*/

//int Engine::Difference(string rel1, string rel2);