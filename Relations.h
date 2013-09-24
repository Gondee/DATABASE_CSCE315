/* 
 * File:   Relations.h
 * Author: joshkruger
 *
 * Created on September 9, 2013, 5:22 PM
 */

#ifndef RELATIONS_H
#define	RELATIONS_H

#include "Attributes.h"
#include <vector>
#include <string>

using namespace std;

class Relations 
{
private:
    string table_name;
    vector<vector< string* > > table;
    vector<Attribute*> att_list;
    vector<bool> keys;

public:
    Relations(){} //Do not use default constructor
    Relations(string, vector<Attribute*>, vector<bool>);
	
	string get_name();
    void set_tablename(string);
	int show_table();
	
	vector<Attribute*> get_att_list();
	int get_att_list_size();
	Attribute* get_att(string);
	
	
	vector<bool> get_keys() {return keys;}
	vector<string> get_keys_names();
	int num_of_keys();
	
	int get_num_rows();
	int insert_tuple(vector<string>); 
	vector<string*> get_tuple(string item, Attribute* att);
	vector<string> get_tuple_string(int);
	vector<string*> get_tuple_line(int line_num);
	



};












#endif	/* RELATIONS_H */

