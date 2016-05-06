#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/ioctl.h>
#include <features.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/if_ether.h>
#include <netpacket/packet.h>

void printfpackage(unsigned char buf[],int n)
{
    printf(" destination:%x %x %x %x %x\n",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
    printf("source%x %x %x %x %x\n",buf[6],buf[7],buf[8],buf[9],buf[11]);
    printf("type:%x %x \n",buf[12],buf[13]);
   // printf("another : %x %x %x %x",buf[]);
}
int main()
{
	int sfd;
    int i = 0;
    int n;
    struct sockaddr_ll ll;
    int len = sizeof(ll);
    unsigned char buf[1000];
    sfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(-1 == sfd)
    {
        fprintf(stderr,"can't socket\n");
        return -1;
    }
    while(1)
    {
        n = recv(sfd,buf,1000,0);
        printfpackage(buf,n);
    }

}
