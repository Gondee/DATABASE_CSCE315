
#include "DataBase.h"

Attribute* DataBase::get_Attribute(string name)
{
	for(int i = 0; i < All_Attributes.size(); i++)
	{
		if(name == All_Attributes[i]->get_name())
			return All_Attributes[i];
	}
	// Need error message
} 

Relations* DataBase::get_Relations(string name)
{
	for(int i = 0; i < All_Relations.size(); i++)
	{
		if(name == All_Relations[i]->get_name())
			return All_Relations[i];
	}
	// Need error message
} 

void DataBase::add_Attribute(Attribute* a)
{
	All_Attributes.push_back(a);
}

void DataBase::add_Relations(Relations* r)
{
	bool not_added = true;
	for (int i = 0; i < All_Relations.size(); i++)
	{
		if (r->get_name()==All_Relations[i]->get_name()){
			All_Relations[i] = r;
			not_added = false;}
	}
	if (not_added)
		All_Relations.push_back(r);
}

int DataBase::exist_Relations(string name) // 1 means the relation exists, 0 means it does not exist
{
	char exist = 'n';
	
	for(int i = 0; i < All_Relations.size(); i++)
	{
		if(name == All_Relations[i]->get_name())
			exist = 'y';
	}
		
	if(exist = 'n')
		return 0;
	else
		return 1;
}
int DataBase::exist_Attribute(string name)
{
	char exist = 'n';
	
	for(int i = 0; i < All_Attributes.size(); i++)
		{
			if(name == All_Attributes[i]->get_name())
				exist = 'y';
		}
		
	if(exist = 'n')
		return 0;
	else
		return 1;
}

void DataBase::print_Attribute_Item_List(string name)
{
	Attribute* temp_a;
	temp_a = get_Attribute(name);
	temp_a->print_items();
	delete temp_a;
}

int DataBase::create_Table(string name, vector<string> att_names, 
								vector<string> domains, vector<string> key)
{
	char exist = 'n';
	vector<Attribute*> rel_atts;
	vector<bool> keys;
	//checks for which attributs are keys
	for(int i = 0; i < att_names.size(); i++)
	{
		for(int j = 0; j < key.size(); j++)
		{
			if(att_names[i] == key[j])
			{
				exist = 'y';
				keys.push_back(true);
			}				
		}
		
		if(exist == 'n')
			keys.push_back(false);
			
		exist = 'n';
		for(int j = 0; j < All_Attributes.size(); j++) //No attribuets in list yet
		{
			if(att_names[i] == All_Attributes[j]->get_name())
			{
				exist = 'y';
				rel_atts.push_back(All_Attributes[j]);
			}				
		}
		if(exist == 'n')
		{
			add_Attribute( new Attribute(att_names[i], domains[i]));
			rel_atts.push_back(All_Attributes.back());
		}
	}
	
	add_Relations(new Relations(name, rel_atts, keys));
	
	return 0;
}

int DataBase::Insert(string name, vector<string> items)
{
	Relations* temp_r;	
	temp_r = get_Relations(name);
	
	if(items.size() != temp_r->get_att_list_size())
		return 2; // Didn't enter correct amount of items
		
	return temp_r->insert_tuple(items);
	return 0;
}	

int DataBase::show_table(string name)
{	
	Relations* temp_r;
	temp_r = get_Relations(name);			
	temp_r->show_table();
}
	
		





