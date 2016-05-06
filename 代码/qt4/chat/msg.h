#ifndef __MSG_H__
#define __MSG_H__

enum
{
    T_BCAST,
    T_SCAST,
    T_REGIST,
    T_USER
};
enum
{
    C_MSG,
    C_FSTART,
    C_FILE,
    C_FEND,
    C_USERUP,
    C_USERDOWN,
    C_REGOK,
    C_REGERR
};
#define NAMELEN  20
struct msgHead
{
    unsigned int type;
    unsigned int ctype;
    char dname[NAMELEN];
    char sname[NAMELEN];
    unsigned int msgLen;
};//network 

#define HEADLEN  (sizeof(struct msgHead))
#define BUFLEN   ((HEADLEN)+1024)
#define MAXMSGLEN   (BUFLEN-HEADLEN)

#endif
