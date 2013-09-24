/* 
 * File:   Parcer.h
 * Author: josh kruger
 *
 * Created on September 12, 2013, 12:54 PM
 */

#ifndef PARCER_H
#define	PARCER_H
#include "Engine.h"

#include <iostream>
#include <string>
#include <vector>
#include <iostream> 

using namespace std;


//
//Tested with Test parse file
//
//
//
class Parse
{
   //Tokenizes the input string into recursive decent tree
private:
    
    
    string INPUT;
    int POSITION;
    string CURRENT_TOKEN;
    vector<string> TOKENS; //Holds broken up tokens
    
   
    
public:
    
    void set_input(string s){INPUT = s;}
    vector<string> get_tokens(){ return TOKENS; }
    int Tokenize(string);
    bool getToken();
    
    bool Begin_Parse(); //Begins Parsing Process
    
    bool Expecting(string);
    bool Validate(string);
    bool RelationsWord(); //relations/key words
    bool ListedAttributes();
    bool Type();
    bool Integer();
    
    
    //Commands
    bool Command_Check();
    bool C_Close();
    bool C_Write();
    bool C_Exit();
    bool C_Show();
    bool C_Create();
    bool C_Update();
    bool C_Insert();
    bool C_Delete();
    
    //Querys
    bool Query_Check();
    bool Create_AttList();//List checker just for table CREATE
    
    bool alphaCheck(char);
    bool digitCheck(char);
    
    bool AtomicExpr();
    bool Expression();
    
    
    bool Operation(); //Determins if is operation ie => or == 
    bool Projection();
    bool Selection();
    bool Union();
    bool Renaming();
    bool Difference();
    bool Product();
};





#endif	/* PARCER_H */

