/* 
 * File:   main.cpp
 * Author: joshkruger
 *
 * Created on September 9, 2013, 5:21 PM
 */

#include <cstdlib>
#include "Engine.h"
#include "Parser.h"
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


vector<string> values, values1, values2, values3, values4, values5;
values.push_back("Ford");
values.push_back("Mustang");
values.push_back("24000");

values1.push_back("Infiniti");
values1.push_back("G35");
values1.push_back("18000");

values2.push_back("Bugatti");
values2.push_back("Veyron");
values2.push_back("2000000");

values3.push_back("Toyota");
values3.push_back("Corolla");
values3.push_back("12000");

values4.push_back("blah");
values4.push_back("blah");
values4.push_back("10");

values5.push_back("blahje");
values5.push_back("blahje");
values5.push_back("10000000");


test.Insert("dealership",values);
test.Insert("dealership",values1);
test.Insert("dealership",values2);
test.Insert("dealership",values3);
test.Insert("dealership",values4);
test.Insert("dealership",values5);


//test.View("dealership");

//cout<<"\n"<<endl;
test.Create_Table(name1,items,domain,key);
test.Insert("Table2",values);
test.Insert("Table2",values1);
//test.View("Table2"); //Commented out by joshk for testing command parser


//string instruction[] = {"American", "<-", "dealership", "*", "Table2"};
//vector<string> line(instruction,instruction+5);
/*
cout << endl;
for (int i = 0; i < line.size(); i++)
	cout << line[i] << " ";
cout << endl;
*/


//----------------josh kruger testing
vector<string> line; 
line.push_back("EXIT");
line.push_back(";");

//test.chooseParser(line);

Parse p;
vector<string> list;
list.push_back("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    for(int i =0; i< list.size();i++)
    {
        
        p.Tokenize(list[i]);
        p.Begin_Parse();
        
    }
    vector<string> toke = p.get_tokens();

    for(int x =0; x < toke.size(); x++)
    {
    	cout<<toke[x]<<endl;
    }





//------------------

//test.View("American");
//test.create_table("test_table",

//cout << *tablep.table[0][0];

    
    
    
    

    return 0;
}

