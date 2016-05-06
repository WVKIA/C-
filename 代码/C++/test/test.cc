#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
using namespace std;
int main()
{
    map< string,int> ihash;
    int offset;
    char id[20];
    cout<<"offset";
    cin>>offset;
    cout<<"id";
    cin>>id;
    cout<<offset<<  "     "<<id<<endl; 

    ihash.insert(pair< string,int> (string(id),offset));
    cout<<"offset";
    cin>>offset;
    cout<<"id";
    cin>>id;
    cout<<offset<<  "     "<<id<<endl;  
   
    map<string,int>::iterator it;
    ihash.insert(pair< string,int>(string(id) ,offset));
    for(it = ihash.begin(); it != ihash.end(); it++)
    {
        cout<<(*it).first<<"            "<<(*it).second<<endl;
    }
}
