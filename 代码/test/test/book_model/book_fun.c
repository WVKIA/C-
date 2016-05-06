#include <stdio.h>
#include "book.h"
void show(struct book * pst)
{
    printf("%s by %s value is %.2f\n",pst -> author,pst -> title,pst -> value);
}

