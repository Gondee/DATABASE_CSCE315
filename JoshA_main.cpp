/* 
 * File:   main.cpp
 * Author: joshkruger
 *
 * Created on September 9, 2013, 5:21 PM
 */

#include <cstdlib>
#include "Engine.h"
#include <iostream>
using namespace std;

/*
 * 
 */
int main() {
    
Engine test;
vector<string> items, domain, key;
string name;

items.push_back("model");
items.push_back("car");
items.push_back("price");


key.push_back("model");
key.push_back("car");

domain.push_back("VARCHAR(20)");
domain.push_back("VARCHAR(20)");
domain.push_back("INTEGER");

name = "dealership";
string name1 = "Table2";

test.Create_Table(name,items,domain,key);

//cout << test.All_Attributes[0]->get_name();
//cout << test.All_Relations[0]->get_name();


vector<string> values, values1;
values.push_back("Ford");
values.push_back("Mustang");
values.push_back("24000");

values1.push_back("Infiniti");
values1.push_back("G35");
values1.push_back("18000");


test.Insert("dealership",values);
test.Insert("dealership",values1);
test.View("dealership");


cout<<"\n"<<endl;
test.Create_Table(name1,items,domain,key);
test.Insert("Table2",values);
test.Insert("Table2",values1);
test.View("Table2");

string instruction[] = {"American", "<-", "select", "(", "car", "==", "\"Mustang\"",")", "dealership", ";"};
vector<string> line(instruction,instruction+10);
cout << endl;
for (int i = 0; i < line.size(); i++)
	cout << line[i] << " ";
cout << endl;
test.chooseParser(line);
//test.create_table("test_table",

//cout << *tablep.table[0][0];

    
    
    
    

    return 0;
}

