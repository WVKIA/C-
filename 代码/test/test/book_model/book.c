#include <stdio.h>
#include "book.h"
int main()
{
    struct book *first;
    first->title = "ittle grace";
    first->author = "st.su";
    first->value = 90.0;
    show(first);
    return 0;
}
