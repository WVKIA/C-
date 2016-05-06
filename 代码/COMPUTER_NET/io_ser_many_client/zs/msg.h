#ifndef __MSG_H_
#define __MSG_H_
enum
{
    T_BCAST,
    T_SCAST,
    T_REGIST
};
enum
{
    C_MSG,
    C_FSTART,
    C_FILE,
    C_END
};
struct msgHead
{
    unsigned int type;
    unsigned int ctype;
    char dname[20];
    char sname[20];
    unsigned int msglen;
};
#define HEADLEN  sizeof(struct msgHead)
#endif
