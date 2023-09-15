#pragma once
#include <WinSock2.h>
/* �����Э������ */
#define IP       0x0800
#define ARP      0x0806

/* ��������� */
#define TRANS_ICMP       0x01
#define TRANS_TCP        0x06
#define TRANS_UDP        0x11

#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN    4321

//mac֡���Ͷ���
#define MAC_IP  0x0800
#define MAC_ARP 0x0806

/* Ӧ�ò����� */
#define HTTP       0x50
#define DNS        0x35 

//Mac֡ͷ 14�ֽ�
typedef struct eth_hdr
{
#if defined(LITTLE_ENDIAN)
    u_char dest[6];
    u_char src[6];
#elif defined(BIG_ENDIAN)
    u_char src[6];
    u_char dest[6];
#endif
    u_short type;
}eth_hdr;

//ARPͷ
typedef struct arp_hdr
{
#ifdef LITTLE_ENDIAN
    u_short ar_hrd : 8;
    u_short ar_unused : 8;
#elif defined(BIG_ENDIAN)
    u_short ar_unused : 8;
    u_short ar_hrd : 8;
#endif
    //u_short ar_hrd;						//Ӳ������
    u_short ar_pro;						//Э������
    u_char ar_hln;						//Ӳ����ַ����
    u_char ar_pln;						//Э���ַ����
    u_short ar_op;						//�����룬1Ϊ���� 2Ϊ�ظ�
    u_char ar_srcmac[6];			    //���ͷ�MAC
    u_char ar_srcip[4];				    //���ͷ�IP
    u_char ar_destmac[6];			    //���շ�MAC
    u_char ar_destip[4];  			//���շ�IP
}arp_hdr;

//IPv4 �ײ� 
typedef struct ip_hdr
{
#if defined(LITTLE_ENDIAN)
    u_char ip_ihl : 4;
    u_char ip_version : 4;
#elif defined(BIG_ENDIAN)
    u_char ip_version : 4;
    u_char  ip_ihl : 4;
#endif
    //u_char  ip_ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)
    u_char  ip_tos;            // ��������(Type of service)
    u_short ip_tlen;           // �ܳ�(Total length)
    u_short ip_id;              // ��ʶ(Identification)
    u_short ip_flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����
                                //(Fragment offset) (13 bits)
    u_char  ip_ttl;            // ����ʱ��(Time to live)
    u_char  ip_type;           // Э��(Protocol)
    u_short ip_crc;            // �ײ�У���(Header checksum)
    u_char ip_src[4];	      // Դ��ַ(Source address)
    u_char ip_dest[4];       // Ŀ�ĵ�ַ(Destination address)
    u_int   ip_op_pad;         // ѡ�������(Option + Padding)
}ip_hdr;

//TCPͷ��
typedef struct tcp_hdr
{
    u_short tcp_sport;			//Դ�˿ں�
    u_short tcp_dport;			//Ŀ�Ķ˿ں�
    u_long tcp_seq;				//���к�
    u_long tcp_ack;				//ȷ�Ϻ�
#if defined(LITTLE_ENDIAN)
    u_short res1 : 4,
        doff : 4,
        fin : 1,
        syn : 1,
        rst : 1,
        psh : 1,
        ack : 1,
        urg : 1,
        ece : 1,
        cwr : 1;
#elif defined(BIG_ENDIAN)
    u_short doff : 4,
        res1 : 4,
        cwr : 1,
        ece : 1,
        urg : 1,
        ack : 1,
        psh : 1,
        rst : 1,
        syn : 1,
        fin : 1;
#endif
    u_short th_win;				//���ڴ�С
    u_short th_ckecksum;				//У���
    u_short th_urp;				//��������ָ��
}tcp_hdr;

//UDPͷ��
typedef struct udp_hdr
{
    u_short udp_sport;			//Դ�˿ں�
    u_short udp_dport;			//Ŀ�Ķ˿ں�
    u_short udp_ulen;			//UDP���ݱ�����
    u_short udp_checksum;				//У���
}udp_hdr;

//����ICMP
typedef struct icmp_hdr
{
    u_char icmp_type;			//8λ ����
    u_char icmp_code;			//8λ ����
    u_char icmp_seq;				//���к� 8λ
    u_char icmp_chksum;			//8λУ���
}icmp_hdr;

//DNS�ײ�
typedef struct dns_hdr {
    u_short dns_id;             // ��ʶ��
    u_short dns_flags;          // ��־
    u_short dns_qcount;         // ��ѯ��¼��
    u_short dns_ancount;        // �ش��¼��
    u_short dns_nscount;        // ��Ȩ�ش��¼��
    u_short dns_arcount;        // ������Ϣ��¼��
} DNSHDR, * pDNSHDR;

//�����ṹ��
typedef struct pktcount
{
    int n_ip;
    int n_arp;
    int n_tcp;
    int n_udp;
    int n_icmp;
    int n_dns;
    int n_sum;
};

//���ṹ��
typedef struct pkt_T
{
    char  pktType[8];					//������
    int time[6];						//ʱ��
    int len;							//����

    struct eth_hdr* eth_h;				//��·���ͷ

    struct arp_hdr* arp_h;				//ARP��ͷ
    struct ip_hdr* ip_h;					//IP��ͷ

    struct icmp_hdr* icmp_h;		//ICMP��ͷ
    struct udp_hdr* udp_h;		//UDP��ͷ
    struct tcp_hdr* tcp_h;		//TCP��ͷ

    struct dns_hdr* dns_h;	//DNS��ͷ

    void* app_hdr;							//Ӧ�ò��ͷ
    unsigned char data[65536];					//���ݰ�����
};