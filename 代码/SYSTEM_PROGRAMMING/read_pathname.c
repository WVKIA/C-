#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


char * translate(mode_t num,char *p);
int main(int argc,char *argv[])
{
    int n = 0;
    struct stat st_t;
     DIR * pdir = NULL;
    struct dirent *pent = NULL;
    struct stat st;
    int tr = 0;
    char * ch = NULL;
    char  p[10];
    char * current = NULL;
    if(argc < 2)
    {
        current = ".";
      
    }
    else
    {
        current = argv[1];
    }
    tr = stat(current ,&st);
    if(tr < 0)
    {
        fprintf(stderr,"can't not access file%s\n",current);
        return -1;
    }
    if(S_ISDIR(st.st_mode))
    {
        pdir = opendir(current);
        if(NULL == pdir)
        {
            printf("can't open the file\n");
            return -1;
        }
        pent  = readdir(pdir);
        if(NULL == pent)
        {
            printf("can;t read the file\n");
            return -1;
        }
        while(NULL != pent)
        {
            
            printf("%-16s ",pent->d_name);
            ch = pent->d_name;
            n = lstat(ch,&st_t);
            /*
             * if(current [strlen(current )-1] != '/')
             * {
             * sprintf(path,"%s/%s",current,pent->d_name);
             * }
             * else
             * {
             * sprintf(path,"%s%s",current,pent->d_name);
             * }
             *
             */
            if(n < 0)
            {
                break;
            }
            if(S_ISDIR(st_t.st_mode))
            {
                printf("/           ");
            }
            else if(S_ISREG(st_t.st_mode))
            {
                printf("regular     ");
            }
            else if(S_ISLNK(st_t.st_mode))
            {

                printf("symbol link     ");
            }
            translate(st_t.st_mode,p);
            printf("%-16s ",p);
         
            printf("\n");
            pent = readdir(pdir);
        }
        printf("\n");
        closedir(pdir);
    }
    else
    {
        printf("%-10s",current);
    }
}

char * translate(mode_t num,char *ch)
{
    if((num & S_IRUSR))
    {
        ch[0] = 'r';
    }
    else
    {
        ch[0] = '-';
    }
    if(num & S_IWUSR)
    {
        ch[1] = 'w';
    }
    else
    {
        ch[1] = '-';
    }
    if(num & S_IXUSR)
    {
        ch[2] = 'x';
    }
    else
    {
        ch[2] = '-';
    }
    if(num & S_IRGRP)
    {
        ch[3] = 'r';
    }
    else
    {
        ch[3] = '-';
    }
    if(num & S_IWGRP)
    {
        ch[4] = 'w';
    }
    else
    {
        ch[4] = '-';
    }
    if(num & S_IXGRP)
    {
        ch[5] = 'x';
    }
    else
    {
        ch[5] = '-';
    }
    if(num & S_IROTH)
    {
        ch[6] = 'r';
    }
    else
    {
        ch[6] = '-';
    }
    if(num & S_IWOTH)
    {
        ch[7] = 'w';
    }
    else
    {
        ch[7] = '-';
    }
    if(num & S_IXOTH)
    {
        ch[8] = 'x';
    }
    else
    {
        ch[8] = '-';
    }
    ch[9] = '\0';
   
}
