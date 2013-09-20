/* 
 * File:   main.cpp
 * Author: joshkruger
 *
 * Created on September 12, 2013, 12:53 PM
 */

#include <cstdlib>
#include "Parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    cout<<"Starting reading of file"<<endl;
    cout<<"------------------------"<<endl;

    //ofstream outfile ("PRASE.txt");
    //outfile.close();
    vector<string> list;
    string STRING;
    ifstream infile;
    infile.open ("PRASE.txt");
    while(getline(infile,STRING)) // To get you all the lines.
    {
        list.push_back(STRING);
        //cout<<STRING<<endl;
    }
    infile.close();

    Parse p;
    for(int i =0; i< list.size();i++)
    {
        
        p.Tokenize(list[i]);
        p.Begin_Parse();
        cout<<"Parse ["<<i<<"] complete"<<endl;
    }
    
    return 0;
}

