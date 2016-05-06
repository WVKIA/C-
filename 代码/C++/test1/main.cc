#include <iostream>
#include <string.h>
#include "student.h"
using namespace std;
int main()
{
    student st;
    char name[20];
    char age[20]; 
    char id[20];
    char sex;
    struct node nnode;
    for(int i = 1; i< 4;i++)
    {
    cout<<"name";
    cin>>nnode.name;
    cout<<"age";
    cin>>nnode.age;
    cout<<"id";
    cin>>nnode.id;
    cout<<"sex";
    cin>>nnode.sex;

    st.add(&nnode);

}
st.showall();
}
