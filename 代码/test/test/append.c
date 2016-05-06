#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 1024
#define SLEN 81
void append(FILE *source, FILE *dest);

int main()
{
    FILE *fa, *fs;
    int files = 0;
    char file_app[SLEN];
    char file_src[SLEN];
    puts("enter name of destination file:");
    scanf("%s",&file_app);
    if(NULL == (fa = fopen(file_app,"a")))
    {
        fprintf(stderr,"can't open %s",file_app);
        exit(3);
    }
    puts("enter name of first source file (empty line to quit): ");
    while((scanf("%s",&file_src)) == 1 && file_src[0] != '\0')
    {
        if(strcmp(file_src,file_app) == 0)
        {
            fputs("can't append file to intself\n",stderr);
        }
        else if((fs = fopen(file_src, "r")) == NULL)
        {
            fprintf(stderr,"can't open %s\n",file_src);
        }
        else
        {
            if(setvbuf(fs,NULL ,_IOFBF,BUFSIZE) != 0)
            {
                fputs("can't create input buffer\n",stderr);
                continue;
            }
            append(fs,fa);
            if(ferror(fs) != 0)
            {
                fprintf(stderr,"Error in reading file %s\n",file_src);
            }
            if(ferror(fa) != 0)
            {
                fprintf(stderr,"Error in writing file %s\n",file_app);
            }
            fclose(fs);
            files ++;
            printf("File %s append\n",file_src);
            puts("Next file (empty line to quit): ");
        }
    }
    print("Done %s file appended\n",files);
    fclose(fa);
    return 0;
}

void append(FILE *source, FILE *dest)
{
    size_t bytes;
    static char temp[BUFSIZE];

    while((bytes = fread(temp,sizeof(char),BUFSIZE, source)) > 0)
    {
        fwrite(temp ,sizeof(char),bytes,dest);
    }
}
