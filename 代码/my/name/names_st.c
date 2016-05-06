#include <strio.h>
#include "name_st.h"

void get_names(names * pn)
{
    int i = 0;

    printf("Please enter yout first name: ");
    fgets(pn->first, SLEN, stdin);
    while(pn->first[i] != '\n' && pn->first[i] != '\0')
    {
        i++;
    }
    if(pn->first[i] == '\n')
    {
        pn->first[i] = '\0';
    }
    else
    {
        while(getchar() != '\n')
        {
            continue;
        }
    }

    printf("Please enter yout last name: ");
    fgets(pn->first, SLEN, stdin);
    while(pn->last[i] != '\n' && pn->last[i] != '\0')
    {
        i++;
    }
    if(pn->last[i] == '\n')
    {
        pn->last[i] == '\0';
    }
    else
    {
        while(getchar() != '\n')
        {
            continue;
        }
    }
}


void show_names(const names *pn)
{
    printf("%s %s\n",pn->first, pn->last);
}
