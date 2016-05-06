#ifndef __BOOK_H__
#define __BOOK_H__
struct book
{
    char title[20];
    char author[20];
    float value;
    
};

void show( struct book * pst);

#endif
