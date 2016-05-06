#include <stdio.h>

char * strtosub(char *str,char *str2,int *index);
int main(void)
{
    char ch[100] ;
    char str2[10] = {"hell o"};

    int index;
    
    
    
    printf("%s %d\n",strtosub(ch,str2,&index),index);

    return 0;
}

/*void mystrlen(char * s1)
  {
  int i = 0;
  while(s[i] != '\0')
  {
  i++;
  }
  return i;

  }
  void cat(char * s1, char * s2)
  {
  char *p = s1;
  int i = 0;
  while(*(p))          // when the pointer find '\0',it stop and live there
  {
  p++;
  }
  while(*(p ++) = *(str +i))      
  {
  i ++;
  }
  return dst;
  }
  char *mystrcopy(char *s1, char *s2)
  {
  int i,j;
  for(i = 0; i < mystrlen(s2);i++)
  {
  s1[i] = s2[i];
  }
  s1[i] = '\0';
  return s1;
  }
//youxiaozhifuzhu
//
*/
/*
   char * secret(char *ch, int n)
   {
   int i;

   if(n > 0)
   {
   for(i = 0; '\0' != ch[i]; i++)
   {
   if(((ch[i] < 'z') && (ch[i] >= 'a')) )
   {

   if(ch[i] + n > 'z')
   {
   ch[i] ='a'+( (ch[i] + n)% 'z');
   }


   }
   else if((ch[i] <'Z') && (ch[i] >= 'A') ) 
   {

   ch[i] = (ch[i] - 'A' + n) % 26;
   }
   ch[i] = ch[i];
   }
   }
   return ch;

   }
   */
/*
   char * encrypt(char *s, int key)
   {
   int i = 0;
   int flag = 0;
   key %= 26;
   while('\0' != s[i])
   {
   if((s[i] >= 'a') && (s[i] <= 'z'))
   {
   flag = (int )s[i] + key;
   if(flag > 'z')
   {
   flag -= 26;
   }
   if(flag < 'a')
   {
   flag +=26;
   }
   s[i] = (char)flag;

   }
   else if((s[i] >= 'A') && (s[i] <= 'Z'))
   {
   flag = (int )s[i] + key;
   if(flag > 'Z')
   {
   flag -= 26;
   }
   if(flag < 'A')
   {
   flag += 26;
   }
   s[i] = (char)flag;
   }
   i++;

   }
   return s;
   }
   */
char * strtosub(char *str,char *str2,int *index)
{
    int i,j;
    for(i = 0; ' ' != str2[i] || '\0' !=str2[i]; i++)
    {
        
        str[i] = str2[i];

    }

    for(; str2[i] ==' ';i ++)
    {
        *index =i ;
    }
    return str;
}
