#include "Engine.h"

#include <iostream>
#include <string>
#include <vector>

//josh k- This function will have to be updatd to new Engine.H specs

int Engine::Difference(string rel1, string rel2)
{
	Relations* R1;
	Relations* R2; 
	R1 = DB.get_Relations(rel1);
	R2 = DB.get_Relations(rel2);

	int sameAttSize =0;
	//Test if Relations are comparable 
	for(int i = 0; i < R1->get_att_list().size(); i++)
	{
		vector<Attribute*> temp;
		temp = R1->get_att_list();

		vector<Attribute*> temp2;
		temp2 = R2->get_att_list();

		if(temp[i] == temp2[i])
		{
			sameAttSize++;

		}

	}


	vector<string> items, domain, key;
if(sameAttSize == (R1->get_att_list().size()))
{
	//vector<string> items, domain, key;
	vector<Attribute*> temp;
	temp = R1->get_att_list();

	for(int i = 0; i< R1->get_att_list().size();i++)
	{
		items.push_back(temp[i]->get_name());
		domain.push_back(temp[i]->get_domain());
		key.push_back(temp[i]->get_name());

	}





	DB.create_Table("Difference", items,domain,key);

	for(int i =0; i < R1->get_num_rows(); i++)
	{
		vector<string*> Tuple;
		Tuple = R1->get_tuple_line(i);

		for(int j = 0; j < R2->get_num_rows(); j++)
		{
			vector<string*> TupleTwo;
			TupleTwo = R2->get_tuple_line(j);

			if(*Tuple[i] != *TupleTwo[j])
			{
				vector<string> new_Tuple;
				for(int x =0; x < Tuple.size(); x++)
				{
					new_Tuple.push_back(*Tuple[i]);

				}

				DB.Insert("Difference", new_Tuple);

			}


		}



	}
}//End of same test if




}