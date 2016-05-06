#include <stdio.h>
#include "student1.h"
#include <string.h>
#include <stdlib.h>
/*void  addstu(struct allstudent * allstu, struct student * stu)
  {
  int i = allstu -> number;

  strcpy(allstu -> allstu[i].name,stu -> name);
  strcpy(allstu -> allstu[i].id,stu -> id);
  allstu -> allstu[i].age = stu -> age;
  allstu -> allstu[i].sex = stu -> sex;
  allstu -> number ++;

//memcpy(&allstu -> allstu[i],stu,sizeof(struct student)); 
//
//
//
//
allstu -> allstu[i] = *stu;  // zhijiefuzhi
allstu -> number ++;

}
*/
int  initallstudent(struct allstudent *allstu)
{
    allstu -> number = 0;
    allstu->space = 1;
    allstu->allstu = malloc(sizeof(struct student *));
    printf("this is initallstudent malloc\n");
}
int destroyallstudent(struct allstudent *allstu)
{
    int i;
    for(i = 0; i < allstu->number; i++)
    {
        free((allstu->allstu[i]));
        printf("free %d stuent",i);
        allstu->allstu[i] = NULL;
    }
    allstu->number = 0;
    allstu->space = 0;
    
    free(allstu->allstu);
    printf("free zuihou de zhizehn\n");
    allstu->allstu = NULL;
}
void show(struct allstudent * allstu)
{
    int j ;
    int i = (allstu -> number);
    if(0 == i)
    {
        printf("The student is none!\n");
        return ;
    }
    printf("there are %d student!\n",allstu->number);
    for( j =0;j < i;j++)
    {
        
        printf(" %d. name is :%s    id is :%s     age is :%d      sex is:%c    \n",j+1,(*(allstu ->allstu [j])).name,(*(allstu->allstu[j])).id,(*(allstu->allstu[j])).age,(*(allstu->allstu[j])).sex);
    }

}
void show_find(struct allstudent * allstu,int i)
{
    printf("name : %s, id :%s ,age :%d , sex : %c\n",(*(allstu->allstu[i])).name,(*(allstu->allstu[i])).id,(*(allstu->allstu[i])).age,(*(allstu->allstu[i])).sex);
}




struct student * findstu(struct allstudent * allstu,char *id)
{
    int temp = (allstu -> number);
    int j;
    for(j = 0; j < temp; j++)
    {
        if(strcmp(((*(allstu->allstu[j]))).id,id) == 0)
        {
            show_find(allstu,j);
            return (allstu->allstu[j]);

        }
    }
    return NULL;

}

void delstu(struct allstudent * allstu,char *id)
{
    int temp = (allstu -> number);
    int j,i;
    for(j=0;j<temp;j++)
    {
        if(strcmp(((*(allstu->allstu[j]))).id,id) == 0)
        {
           
            allstu->allstu[j] = NULL;
            memcpy((allstu->allstu[j]),(allstu->allstu[j+1]), sizeof(struct student *) * (temp - j - 1));
        }
    }
    free(allstu->allstu[allstu->number]);
    printf("free delstu \n");
    allstu->number--;
}
//for(pstu = find();pstu < allstu->allstu + allstu -> number - 1; pstu ++)

//{
//   *pstu = *(pstu + 1);
//}
//memcpy(pstu, pstu + 1; allstu->allstu + allstu->number - 1);




struct student * find_name(struct allstudent * allstu,char * name,struct student *pre)
{
    int temp = allstu->number;
    int j =  0;
    if(NULL == pre)
    {
        pre = *(allstu->allstu);
    }
    else
    {
        pre ++;
    }
    for(pre; pre <* (allstu->allstu) + allstu->number; pre++)
    {
        if(strcmp(pre->name,name) == 0)
        {
            return pre;
        }
    }
    return NULL;

}



int addstu(struct allstudent *allstu,struct student *stu)


{
    int i;
    if(allstu->space == allstu->number)
    {
        struct student **p = NULL;
        p = malloc((allstu->space*2) * sizeof(struct student *));
        memcpy(p,(allstu->allstu),allstu->space*sizeof(struct student *));
        allstu->space *= 2;
    
        free(allstu->allstu);
        printf("free addstu \n");
        printf("this addstu 's free\n");
        allstu->allstu = NULL;
        allstu->allstu = p;
        p = NULL;
        

    }
    allstu->allstu[allstu->number] = stu;
    allstu->number ++;

}


int readfile(struct allstudent * allstu,char * filename)
{
    struct student *pstu = NULL;
    int num = 0;
    int n;
    struct student stu;
    FILE * fp = fopen(filename, "r");
    if(NULL == fp)
    {
        return num;
    }
    while(1)
    {
        pstu = malloc(sizeof(struct student));
        if(NULL ==pstu)
        {
           return -1;
        }
        n = fread(pstu,sizeof(struct student),1,fp);
        if(0 == n)
        {
            free(pstu);
            pstu = NULL;
            break;
        }
        addstu(allstu,pstu);
        num ++;
    }
    fclose(fp);
    return num;
}
int savefile(struct allstudent * allstu,char *filename)
{
    int num = 0;
    int i;
    FILE * fp = fopen(filename,"w");
    if(NULL == fp)
    {
        return -1;
    }
    for(i = 0;i < allstu->number;i++)
    {

        fwrite((allstu->allstu[i]),sizeof(struct student),1,fp);
        num ++;
    }
    fclose(fp);
    return num;
}


//void add_list(struct allstudent *allstu,)
