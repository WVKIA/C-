#include <stdio.h>

int main(int argc,char *argv[])
{
    int n;
    char buf[1024];
    FILE * freadp = NULL;
    FILE * fwritep = NULL;
    
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
        fwrite(buf,n,1,fwritep);
        
    }
    fclose(freadp);
    fclose(fwritep);
    return 0 ;

}
