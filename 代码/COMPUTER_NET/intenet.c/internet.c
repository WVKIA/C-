#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/if.h>
#include <linux/ioctl.h>
#include <netinet/ip.h>
#include <linux/sockios.h>

#include <features.h>
#if __GLIBC__>= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethrnet.h>
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#endif

struct arphead
{

    unsigned short ht;
    unsigned short pt;
    unsigned char hs;
    unsigned char ps;
    unsigned short op;
    unsigned char smc[6];
    unsigned char sip[4];
    unsigned char dmc[6];
    unsigned char dip[4];
};
int main()
{
    int ip;
    int fd;
    char buf[64] = {0};
    struct arphead *arp;
    char smac[] = {1,2,3,4,5,6};
    
    int len;
    struct sockaddr_ll ll;
    len = sizeof(ll);
    struct ifreq ifr;
    memset(&ll,0,sizeof(struct sockaddr_ll));
    memset(buf,0xff,6);
    memcpy(buf+6,smac,6);
    buf[12] = 0x8;
    buf[13]= 0x6;
    arp =(struct arphead *)( buf+14);
    arp->ht = htons(1);
    arp->pt = htons(0x800);
    arp->hs = 0x6;
    arp->ps = 0x4;
    arp->op = htons(1);
    memcpy(arp->smc,smac,6);
    memset(arp->dmc,0,6);
    ip = inet_addr("192.168.100.100");
    memcpy(arp->sip,&ip,4);
    ip = inet_addr("192.168.100.101");
    memcpy(arp->dip,&ip,4);

    fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(fd == -1)
    {
        fprintf(stderr,"can't socket\n");
        return -1;
    }
    memset(&ifr,0,sizeof(ifr));
    strcpy(ifr.ifr_name,"eth0");
    if(ioctl(fd,SIOCGIFINDEX,&ifr) < 0)
    {
        printf("ioctnl failed\n");
        return -1;
    }
    memset(&ll,0,len);

    ll.sll_family = PF_PACKET;
    ll.sll_ifindex = ifr.ifr_ifindex;
    while(1)
    {
	sleep(3);
        sendto(fd,buf,64,0,(struct sockaddr *)&ll,len);
    }
    close(fd);
}
