#include <stdio.h>

void read(FILE *fp_first, FILE *fp_second);
int main()
{
    FILE * fp_first;
    FILE * fp_second;
    char buf[20];
    printf("enter the first file name\n");
    scanf("%s",&buf);
    fp_first = fopen(buf,"r");
    printf("enter the second file name\n");
    scanf("%s",&buf);
    fp_second = fopen(buf,"r");
    read(fp_first, fp_second);
    return 0;
}
void read(FILE *fp_first, FILE *fp_second)
{
    char line[1024];
    char line1[1024];
    while(1)
    {
    if((fgets(line, 1024, fp_first) != NULL) )
    {
        fprintf(stdout, "%s",line);
       
    }
    
    if(( fgets(line1, 1024, fp_second) != NULL))
    {
        fprintf(stdout,"%s",line1);
    }

    if((fgets(line, 1024, fp_first) == NULL) &&( fgets(line1, 1024, fp_second) == NULL))
    {
        break;
    }
    }
}
