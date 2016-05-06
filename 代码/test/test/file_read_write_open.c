#include <stdio.h>
#include <string.h>

int main(int argc , char *argv[])
{
    int n;
    char buf[1200];
    FILE * fp = NULL;
    if(argc < 2)
    {
        printf("please point your filename\n");
        return -1;
    }
    //fp = fopen(argv[1],"r");
    fp = fopen(argv[1],"w+");
    if(NULL == fp)
    {
        puts("can't open the file");
        return -1;
    }
    while(1)
    {
       /* fgets(buf,1200,fp);
        if(feof(fp) )
        {
            break;
            
        }
        */
   /*     n = fread(buf ,1, 1199,fp);
        if( 0 == n)
        {
            break;
        }
        buf[n] = '\0';
       
        printf("%s",buf);
   */  
        fgets(buf ,1024,stdin);
        if(strcmp(buf,"quit\n") == 0)
        {
            break;
        }
        fwrite(buf,1,strlen(buf),fp);

    }
    fclose(fp);
    return 0;
}
