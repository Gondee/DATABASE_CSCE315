#include "Engine.h"
#include <string>
#include <vector>
#include <iostream>

Relations Engine::Difference(string name, string R1, string R2)
{
	Relations* rel1, * rel2;
	rel1 = DB.get_Relations(R1);
	rel2 = DB.get_Relations(R2);
	
	if(!Union_Compatible(*(rel1), *(rel2)))
	{
		cout << rel1->get_name() << " and " << rel2->get_name() << " are not union compatible." << endl;
	}

	vector<string> atts, domain, key;

	vector<Attribute*> temp;
	temp = rel1->get_att_list();

	for(int i = 0; i< rel1->get_att_list_size();i++)
	{
		atts.push_back(temp[i]->get_name());
		domain.push_back(temp[i]->get_domain());
	}
	key = rel1->get_keys_names();

	DB.create_Table(name, atts,domain,key);
	int CheckTuple = 0;
	vector<bool> MatchR1, MatchR2; // Vector of bools that store if a tuple has a match
	MatchR1.resize(rel1->get_num_rows());
	MatchR2.resize(rel2->get_num_rows());
	
	for(int i = 0; i < MatchR1.size(); i++) // Initialize Match vector to false
		MatchR1[i] = false;
	
	for(int i = 0; i < MatchR2.size(); i++)
		MatchR2[i] = false;
	

	for(int i =0; i < rel1->get_num_rows(); i++)
	{
		vector<string*> Tuple;
		Tuple = rel1->get_tuple_line(i);

		for(int j = 0; j < rel2->get_num_rows(); j++)
		{
			vector<string*> TupleTwo;
			TupleTwo = rel2->get_tuple_line(j);

			for(int k = 0; k < Tuple.size(); k++)
				for(int l = 0; l < TupleTwo.size(); l++)
					if(Tuple[k] == TupleTwo[l])
						CheckTuple++;

			if(CheckTuple == Tuple.size())
			{
				MatchR1[i] = true;
				MatchR2[j] = true;
			}
			CheckTuple = 0;
		}
	}

	for(int i = 0; i < rel1->get_num_rows(); i++)
	{
		vector<string> new_Tuple;
		if(!MatchR1[i])
		{
			new_Tuple = rel1->get_tuple_string(i);
			DB.Insert(name, new_Tuple);
		}
	}

	for(int i = 0; i < rel2->get_num_rows(); i++)
	{
		vector<string> new_Tuple;
		if(!MatchR2[i])
		{
			new_Tuple = rel2->get_tuple_string(i);
			DB.Insert(name, new_Tuple);
		}
	}
	return *(DB.get_Relations(name));
}//End of same test if

Relations Engine::Union(string name, string R1, string R2)
{
	Relations* rel1, * rel2;
	rel1 = DB.get_Relations(R1);
	rel2 = DB.get_Relations(R2);
	
	if(!Union_Compatible(*(rel1), *(rel2)))
	{
		cout << rel1->get_name() << " and " << rel2->get_name() << " are not union compatible." << endl;
	}

	vector<string> atts, domain, key;

	vector<Attribute*> temp;
	temp = rel1->get_att_list();

	for(int i = 0; i< rel1->get_att_list_size();i++)
	{
		atts.push_back(temp[i]->get_name());
		domain.push_back(temp[i]->get_domain());
	}
	key = rel1->get_keys_names();

	DB.create_Table(name, atts,domain,key);
	int CheckTuple = 0;
	vector<bool> MatchR1, MatchR2; // Vector of bools that store if a tuple has a match
	MatchR1.resize(rel1->get_num_rows());
	MatchR2.resize(rel2->get_num_rows());
	
	for(int i = 0; i < MatchR1.size(); i++) // Initialize Match vector to false
		MatchR1[i] = false;
	
	for(int i = 0; i < MatchR2.size(); i++)
		MatchR2[i] = false;
	

	for(int i =0; i < rel1->get_num_rows(); i++)
	{
		vector<string*> Tuple;
		Tuple = rel1->get_tuple_line(i);

		for(int j = 0; j < rel2->get_num_rows(); j++)
		{
			vector<string*> TupleTwo;
			TupleTwo = rel2->get_tuple_line(j);

			for(int k = 0; k < Tuple.size(); k++)
				for(int l = 0; l < TupleTwo.size(); l++)
					if(Tuple[k] == TupleTwo[l])
						CheckTuple++;

			if(CheckTuple == Tuple.size())
			{
				MatchR1[i] = true;
				MatchR2[j] = true;
			}
			CheckTuple = 0;
		}
	}

	for(int i = 0; i < rel1->get_num_rows(); i++)
	{
		vector<string> new_Tuple;
		new_Tuple = rel1->get_tuple_string(i);
		DB.Insert(name, new_Tuple);
	}

	for(int i = 0; i < rel2->get_num_rows(); i++)
	{
		vector<string> new_Tuple;
		if(!MatchR2[i])
		{
			new_Tuple = rel2->get_tuple_string(i);
			DB.Insert(name, new_Tuple);
		}
	}
	return *(DB.get_Relations(name));
}//End of same test if

int Engine::Union_Compatible(Relations rel1, Relations rel2)
{
	int sameAttSize = 0;

	vector<Attribute*> temp1;
	temp1 = rel1.get_att_list();

	vector<Attribute*> temp2;
	temp2 = rel2.get_att_list();

	//Test if Relations are comparable
	for(int i = 0; i < rel1.get_att_list_size(); i++)
		for(int j = 0; j < rel2.get_att_list_size(); j++)
			if(temp1[i] == temp2[j])
					sameAttSize++;

	if(sameAttSize == rel1.get_att_list_size())
		return 1;
	else
		return 0;
}



