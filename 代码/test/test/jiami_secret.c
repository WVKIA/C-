#include <stdio.h>
#include <string.h>

void en_secret(char buf[],int n,char key[]);
int main(int argc,char *argv[])
{
    char key[30];
    int n;
    char buf[1024];
    FILE * freadp = NULL;
    FILE * fwritep = NULL;
    
    printf("please enter a key\n");
    scanf("%s",key);
    freadp = fopen(argv[1],"r");
    fwritep = fopen(argv[2],"w");
    if((NULL == freadp) || (NULL == fwritep) )
    {
        puts("cant open the file");
        return -1;
    }
    while(1)
    {
       n= fread(buf,1,1024,freadp);
        if(0 == n)
        {
            break;
        }
        en_secret(buf,n,key);
        fwrite(buf,n,1,fwritep);
        
    }
    fclose(freadp);
    fclose(fwritep);
    return 0 ;

}
void en_secret(char buf[],int n,char key[])
{
    int i;
    int temp = strlen(key);
    int tmp;
    for( i = 0; i < n; i++)
    {
        tmp = i % temp;

        buf[i] = buf[i] ^ key[tmp];

    }
}





















