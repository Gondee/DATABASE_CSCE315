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
enum compare{eq = 1, lte, lt, gte, gt, neq};


void commandParser(vector<string>);
void queryParser(vector<string>);
Relations expressionParser(string, vector<string>);
Relations operationsParser(string, vector<string>);

Relations Selection(string,Relations, string, string, compare);
Relations Selection1(string, Relations, string, string, compare);
Relations rename(string, Relations, vector<string>);	//i've already written these functions into my code so i had to have them return something so that everything would compile.
Relations project(string, Relations, vector<string>);	//also if you have to put a temporary table into the database that's ok just make sure its always named "temp"

Relations unionize(string, Relations, Relations);
Relations difference(string, Relations, Relations);
Relations cross_prod(string, Relations, Relations);
int Union_Compatible(Relations, Relations);
bool FileExists(string); //Checks if the DataBase exists and is not open

Relations Union(string, string, string);//Exists in Harrison_Engine.cpp
Relations Difference(string, string, string);//Exists in HArrison_Engine.cpp

public:

int Create_Table(string n, vector<string> a, vector<string> d, vector<string> k)
{
	return DB.create_Table(n, a, d, k);
}

int Insert(string n, vector<string> i)
{
	return DB.Insert(n, i);
}

int Insert_From_Relation(string R1, string R2);

int View(string n)
{
	return DB.show_table(n);
}

void chooseParser(vector<string>);


};






#endif	/* ENGINE_H */
