/* 
 * File:   DataBase.h
 * Author: joshkruger
 *
 * Created on September 9, 2013, 5:22 PM
 */

#ifndef DATABASE_H
#define	DATABASE_H


//
//  DataBase.h
//  
//
//  Created by Josh Kruger on 9/3/13 in Xcode
//	SVN Testing from VS Express 2012... Josh Amaku
//  Test by Harrison
// Changed structur of program with guidance in lab
//

#include "Relations.h"
#include <string>
#include <vector>

using namespace std;


class DataBase
{
private:
public:
vector<Attribute*> All_Attributes;
vector<Relations*> All_Relations;

//public: 

Attribute* get_Attribute(string);
Relations* get_Relations(string);

int remove_Relation(string);

void add_Attribute(Attribute* a);
void add_Relations(Relations* r);

int exist_Relations(string); //1 =true
int exist_Attribute(string);

void print_Attribute_Item_List(string);

int create_Table(string, vector<string>, vector<string>, vector<string>);
int Insert(string, vector<string>);

int show_table(string);

};










#endif	/* DATABASE_H */

