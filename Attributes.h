/* 
 * File:   Attributes.h
 * Author: joshkruger
 *
 * Created on September 9, 2013, 5:21 PM
 */

#ifndef ATTRIBUTES_H
#define	ATTRIBUTES_H


#include <vector>
#include <string>

using namespace std;

class Attribute
{

private:
    string name;
    vector<string*> items;
    string domain;

public:    
    Attribute(){}
    Attribute(string, string); //Fill all private memebers

	string get_name();
    void set_name(string);
	
    string get_domain();
    void set_domain(string);
	bool check_domain(string);

	vector<string*> get_items();
	string* get_item(string);
	int items_size();
    string* add_item(string);
    int remove_item(string);
	void print_items();
	

    

    //Someone needs to operator overloading for == **** -josh
    friend bool operator== (Attribute &cP1, Attribute &cP2);

    
};




#endif	/* ATTRIBUTES_H */

