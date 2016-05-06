#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include <string.h>
enum
{
    ADD,
    DEL,
    SHOW,
    FIND,
    FINDN,
    SAVE,
    QUIT,
    NONE
};
char *cmdstring[] = {
    "add",
    "del",
    "show",
    "find",
    "findn",
    "save",
    "quit"
};
int getcmd(char *cmd)
{
    int i;
    int n=sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i])==0)
        {
            break;
        }
    }
    return i;
}
int main()
{
    int cmd;
    int quit = 0;
    char buf[1024];
    struct student *phead = NULL;
    while(0 == quit)
    {
        fgets(buf,1024,stdin);
        buf[strlen(buf) - 1] = '\0';
        cmd = getcmd(buf);
        switch(cmd)
        {
            case ADD:
                
                        addstu(&phead);
                        break;
            case DEL:
                        // delstu();
                        break;
            case SHOW:
                        show(phead);
                        break;
            case FIND:
                        // find();
                        break;
            case FINDN:
                        // findn();
                        break;
            case SAVE:
                        // save();
                        break;
            case QUIT:
                        quit = 1;
                        break;
            default :
                        printf("the %s is'n a cmd!\n",buf);
                        break;
        }
        destroy(phead);

    }




}
