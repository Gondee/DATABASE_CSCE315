#ifndef ENGINE_H
#define	ENGINE_H

#include "DataBase.h"
#include <iostream>
#include <vector>

using namespace std;

class Engine {
private:

DataBase DB;
enum express{sel = 1, proj, re};
enum ops{plus=1, cross, diff};
enum compare{eq = 1, neq, lt, gt, lte, gte};

void commandParser(vector<string>){}
Relations expressionParser(string, vector<string>);
Relations operationsParser(string, vector<string>);

Relations Selection(string,Relations, string, string, compare);
Relations Selection1(string, Relations, string, string, compare);
Relations rename(string, Relations, vector<string>);	//i've already written these functions into my code so i had to have them return something so that everything would compile.
Relations project(string, Relations, vector<string>){Relations temp; return temp;}	//also if you have to put a temporary table into the database that's ok just make sure its always named "temp"

Relations unionize(string, Relations, Relations){Relations temp; return temp;}
Relations difference(string, Relations, Relations){Relations temp; return temp;}
Relations cross_prod(string, Relations, Relations);


public:

int Create_Table(string n, vector<string> a, vector<string> d, vector<string> k)
{
	return DB.create_Table(n, a, d, k);
}

int Insert(string n, vector<string> i)
{
	return DB.Insert(n, i);
}

int View(string n)
{
	return DB.show_table(n);
}

bool FileExists(string); //Checks if the DataBase exists and is not open
int Difference(string rel1, string rel2); //Harrison, this must be updated to use new Relations specs...



void chooseParser(vector<string>);


};






#endif	/* ENGINE_H */