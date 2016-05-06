
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/if.h>
#include <linux/ioctl.h>
#include <netinet/ip.h>
#include <linux/sockios.h>


#include <features.h> /* 需要里面的 glibc 版本号 */
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h> /* 链路层（L2）协议 */
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h> /* 链路层协议 */
#endif


int getIndex(int sfd,char *name)
{
    struct ifreq ifr;
    memset(&ifr, 0, sizeof (ifr));
    strcpy(ifr.ifr_name,name);
    if(ioctl(sfd,SIOCGIFINDEX,&ifr) < 0) 
    {
        printf("ioctl() failed to get index %s\n",name);
        return -1;
    }
    return ifr.ifr_ifindex;
}

struct arpHead
{
    unsigned short ht;
    unsigned short pt;
    unsigned char  hs;
    unsigned char  ps;
    unsigned short op;
    unsigned char  smac[6];
    unsigned char  sip[4];
    unsigned char  dmac[6];
    unsigned char  dip[4];
};

int main(int argc,char *argv[])
{
    int sfd;
    int i = 0;
    int n;
    int ip;
    struct arpHead *arp;
    struct sockaddr_ll ll;
    int len = sizeof(ll);
    char buf[64] = {0};
    char smac[6] = {0,1,2,3,4,5};
    struct ifreq ifr;
    memset(buf,0xff,6);
    memcpy(buf+6,smac,6);
    buf[12] = 0x8;
    buf[13] = 0x6;
    arp = (struct arpHead *)(buf+14);
    arp->ht = htons(1);
    arp->pt = htons(0x800);
    arp->hs = 6;
    arp->ps = 4;
    arp->op = htons(1);
    memcpy(arp->smac,smac,6);
    memset(arp->dmac,0,6);
    ip = inet_addr("192.168.100.101");
    memcpy(arp->sip,&ip,4);
    ip = inet_addr("192.168.100.102");
    memcpy(arp->dip,&ip,4);
    sfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(-1 == sfd)
    {
        fprintf(stderr,"can not create socket\n");
        return -1;
    }
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name,"eth0");
    if(ioctl(sfd,SIOCGIFINDEX,&ifr) < 0) 
    {
        printf("ioctl() failed to get index %s\n","eth0");
        return -1;
    }
    memset(&ll,0,len);
    ll.sll_family = PF_PACKET;
    ll.sll_ifindex = ifr.ifr_ifindex;//getIndex(sfd,"eth0");

    while(1)
    {
        sleep(3);
        sendto(sfd,buf,64,0,(struct sockaddr *)&ll,len);
    }
    close(sfd);
    return 0;
}

