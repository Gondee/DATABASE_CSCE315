#include "Engine.h"
#include <stdlib.h>
#include <csignal>

Relations Engine::Selection(string new_name, Relations rp, string att, string value, Engine::compare op)
{
	string name_copy = rp.get_name();
	vector<Attribute*> atts = rp.get_att_list();
	vector<string> att_names_copy, domains_copy, key_copy;
	
	Attribute* check;
	int att_int;
	for (int i = 0; i < atts.size(); i++)
	{
		if (att==atts[i]->get_name()){
			check = atts[i];
			att_int = i;
		}
		att_names_copy.push_back(atts[i]->get_name());
		domains_copy.push_back(atts[i]->get_domain());
		if (rp.get_keys()[i])
			key_copy.push_back(atts[i]->get_name());

	}
	DB.create_Table(new_name, att_names_copy, domains_copy, key_copy);

	if (check->get_domain()=="INTEGER")
	{
		//cout << "we're here\n" << value << endl;

	for(int i = 0; i < rp.get_num_rows(); i++)
	{
		vector<string> current_tup = rp.get_tuple_string(i);
		string current_val = current_tup[att_int];
		int curr_int = atoi(current_val.c_str());
		int val_int = atoi(value.c_str());
		switch(op)
		{
		case eq:
			if(curr_int==val_int)
				DB.Insert(new_name, current_tup);
			break;
		case neq:
			if(curr_int!=val_int)
				DB.Insert(new_name, current_tup);
			break;
		case lt:
			if(curr_int<val_int)
				DB.Insert(new_name, current_tup);
			break;
		case gt:
			if(curr_int>val_int)
				DB.Insert(new_name, current_tup);
			break;
		case lte:
			if(curr_int<=val_int)
				DB.Insert(new_name, current_tup);
			break;
		case gte:
			if(curr_int>=val_int)
				DB.Insert(new_name, current_tup);
			break;
		}
		}
	}

	else {
	for(int i = 0; i < rp.get_num_rows(); i++)
	{
		vector<string> current_tup = rp.get_tuple_string(i);
		string current_val = current_tup[att_int];
		switch(op)
		{
		case eq:
			if(current_val==value)
				DB.Insert(new_name, current_tup);
			break;
		case neq:
			if(current_val!=value)
				DB.Insert(new_name, current_tup);
			break;
		}
		}

	}
	return *(DB.get_Relations(new_name));
}
Relations Engine::Selection1(string new_name, Relations rp, string att, string att1, Engine::compare op)
{
	string name_copy = rp.get_name();
	vector<Attribute*> atts = rp.get_att_list();
	vector<string> att_names_copy, domains_copy, key_copy;
	
	Attribute* check;
	Attribute* check1;
	int att_int, att_int1;
	for (int i = 0; i < atts.size(); i++)
	{
		if (att==atts[i]->get_name()){
			check = atts[i];
			att_int = i;
		}

		if (att1==atts[i]->get_name()){
			check1 = atts[i];
			att_int1 = i;
		}
		att_names_copy.push_back(atts[i]->get_name());
		domains_copy.push_back(atts[i]->get_domain());
		if (rp.get_keys()[i])
			key_copy.push_back(atts[i]->get_name());

	}
	DB.create_Table(new_name, att_names_copy, domains_copy, key_copy);

	if (check->get_domain()=="INTEGER")
	{

	for(int i = 0; i < rp.get_num_rows(); i++)
	{
		vector<string> current_tup = rp.get_tuple_string(i);
		string current_val = current_tup[att_int];
		string other_val = current_tup[att_int1];
		int curr_int = atoi(current_val.c_str());
		int val_int = atoi(other_val.c_str());
		switch(op)
		{
		case eq:
			if(curr_int==val_int)
				DB.Insert(new_name, current_tup);
			break;
		case neq:
			if(curr_int!=val_int)
				DB.Insert(new_name, current_tup);
			break;
		case lt:
			if(curr_int<val_int)
				DB.Insert(new_name, current_tup);
			break;
		case gt:
			if(curr_int>val_int)
				DB.Insert(new_name, current_tup);
			break;
		case lte:
			if(curr_int<=val_int)
				DB.Insert(new_name, current_tup);
			break;
		case gte:
			if(curr_int>=val_int)
				DB.Insert(new_name, current_tup);
			break;
		}
		}
	}

	else {
	for(int i = 0; i < rp.get_num_rows(); i++)
	{
		vector<string> current_tup = rp.get_tuple_string(i);
		string current_val = current_tup[att_int];
		string value = current_tup[att_int1];
		switch(op)
		{
		case eq:
			if(current_val==value)
				DB.Insert(new_name, current_tup);
			break;
		case neq:
			if(current_val!=value)
				DB.Insert(new_name, current_tup);
			break;
		}
		}

	}
	return *(DB.get_Relations(new_name));


}

void Engine::chooseParser(vector<string> TOKENS)
{
	if (TOKENS[1]=="<-"){
		queryParser(TOKENS);
		}
	else
		commandParser(TOKENS);

}

void Engine::queryParser(vector<string> TOKENS)
{
	vector<string>::const_iterator a = TOKENS.begin()+2;
	vector<string>::const_iterator b = TOKENS.end();
	vector<string> nextexpression(a,b);
	Relations r = expressionParser(TOKENS[0], nextexpression);
	//DB.add_Relations(&r);
}

Relations Engine::expressionParser(string newname, vector<string> expression)
{
	express curr_exp;
	vector<string> complement;
	Relations temp;
	int next = 0;
	while (expression[next]=="(")	//first token that is not (
		next++;
	vector <string> all_exp, all_comp;
	string list[] = { "select", "project", "rename"};
	all_exp.insert(all_exp.end(), list, list+3);
	string newlist[] = {"==", "!=", "<", ">", "<=", ">="};
	all_comp.insert(all_comp.end(), newlist, newlist+6);
	if (expression[next]=="select"||expression[next]=="project"||expression[next]=="rename")	//don't know about this line
	{
		//cout << "tasting\n";
		for (int i = 0; i < all_exp.size(); i++){
			if (expression[next]==all_exp[i])
				curr_exp = express(i+1);
		}
		next++;
		for (; expression[next]!=")"; next++)
		{
			if(expression[next]!="(" && expression[next]!=",")
				complement.push_back(expression[next]);
		}

		vector<string>::const_iterator a = expression.begin()+(++next);
		vector<string>::const_iterator b = expression.end();
		vector<string> nextexpression(a,b);
		
		temp = expressionParser("temp", nextexpression);
		//raise(SIGABRT);
		
		switch(curr_exp)
		{
		case sel:
			{
			compare curr_comp;
			for (int i = 0; i < all_comp.size(); i++){
			if (complement[1]==all_comp[i])
				curr_comp = compare(i+1);}
			string check = complement[2];
			std::string::const_iterator it = check.begin();
			while (it != check.end() && std::isdigit(*it)) ++it;
			if (it == check.end() || *check.begin()=='"'){
				if (*check.begin()=='"'){
					check.erase(check.begin()); check.erase(check.end()-1);}
				return Selection(newname, temp, complement[0], check, curr_comp);}
			else{
				return Selection1(newname, temp, complement[0], check, curr_comp);}
			}
		case re:
			return rename(newname, temp, complement);
		case proj:
			return project(newname, temp, complement);
		}
	}

	else
	{
		temp = operationsParser(newname, expression);
		return temp;
	}	

}

Relations Engine::operationsParser(string newname, vector<string> expression)
{
	ops curr_op;
	vector<string> complement;
	Relations temp, first, second;
	vector <string> all_ops;
	string list[] = { "+", "*", "-"};
	all_ops.insert(all_ops.end(), list, list+3);

	int next = 0;
	while (expression[next]=="(")	//first token that is not (
		next++;
	if (expression.size() < 3){	//not an operation, just a table
		return *(DB.get_Relations(expression[next]));
	}

	int i = 0;
	while (i < 3)
		{
			if(expression[next]!="(" && expression[next]!="," && expression[next]!=")" ){
				complement.push_back(expression[next]);
				next++; i++;
			}
		}

	

	for (int i = 0; i < all_ops.size(); i++){
		if (complement[1]==all_ops[i])
				curr_op =ops(i+1);}
	
	first = *(DB.get_Relations(complement[0]));
	second = *(DB.get_Relations(complement[2]));
	
	
	switch (curr_op)
	{
	case plus:
		temp = unionize(newname, first, second);
	case diff:
		temp = difference(newname, first, second);
	case cross:
		temp = cross_prod(newname, first, second);
		
	}

	//raise(SIGABRT);
	while (next < expression.size())
	{
	while (expression[next]==")")	//first token that is not )
		next++;

	if (expression[next]=="+"||expression[next]=="-"||expression[next]=="*"){

		for (int i = 0; i < all_ops.size(); i++){
		if (expression[next]==all_ops[i])
			curr_op =ops(i+1);}
		vector<string>::const_iterator a = expression.begin()+(++next);
		vector<string>::const_iterator b = expression.end();
		vector<string> nextexpression(a,b);
		Relations newtable = expressionParser("temp", nextexpression);
		switch (curr_op)
		{
		case plus:
			return unionize(newname, temp, newtable);
		case diff:
			return difference(newname, temp, newtable);
		case cross:
			return cross_prod(newname, temp, newtable);
		}
	}
	}
	
	return temp;

}

Relations Engine::cross_prod(string newname, Relations first, Relations second)
{
	
	string first_copy = first.get_name();
	string second_copy = second.get_name();
	vector<Attribute*> firstatts = first.get_att_list();
	vector<Attribute*> secondatts = second.get_att_list();
	vector<string> att_names_copy, domains_copy, key_copy;
	
	for (int i = 0; i < firstatts.size()+secondatts.size(); i++)
	{
		string newatt;
		if (i < firstatts.size()){
			newatt = first_copy;
			newatt += ".";
			newatt += firstatts[i]->get_name();
			att_names_copy.push_back(newatt);

			domains_copy.push_back(firstatts[i]->get_domain());
			if (first.get_keys()[i])
				key_copy.push_back(firstatts[i]->get_name());
		}

		else
		{
			newatt = second_copy;
			newatt += ".";
			newatt += secondatts[i-firstatts.size()]->get_name();
			att_names_copy.push_back(newatt);

			domains_copy.push_back(secondatts[i-firstatts.size()]->get_domain());
			if (second.get_keys()[i-firstatts.size()])
				key_copy.push_back(secondatts[i-firstatts.size()]->get_name());
		}

	}
	
	DB.create_Table(newname, att_names_copy, domains_copy, key_copy);
	
	
	for (int i = 0; i < second.get_num_rows(); i++)
	{
		vector<string> part2 = second.get_tuple_string(i);

		for (int j = 0; j < first.get_num_rows(); j++)
		{
			vector<string> part1 = first.get_tuple_string(j);
			part1.insert(part1.end(), part2.begin(), part2.end());
			DB.Insert(newname, part1);
		}


	}

	return *(DB.get_Relations(newname));
}