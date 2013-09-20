#ifndef ENGINE_H
#define	ENGINE_H

#include "DataBase.h"

class Engine {
private:

DataBase DB;

public:

int Create_Table(string n, vector<string> a, vector<string> d, vector<string> k);


int Insert(string n, vector<string> i);


int View(string n);


int Difference(string rel1, string rel2);
int Union(string rel1, string rel2);

/*

int Selection(string rel, string att, int value);
int Selection(string rel, string att, string att1);

int Projection(string rel, vector<strings> att);

int Rename(string rel, string new_rel, vector<string> new_att);
int Update(string rel);


int Cross_Product(string rel1, string rel2);
*/
};






#endif	/* ENGINE_H */