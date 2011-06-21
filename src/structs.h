#ifndef STRUCTS_H
#define STRUCTS_H

extern "C" {
#include <arpa/inet.h>
}

#include "enums.h"
#include "fp-macro.def"

struct ip_hdr {
    u_int8_t        ip_vhl;          // header length, version    
#define IP_V(ip)    (((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip)   ((ip)->ip_vhl & 0x0f)
    u_int8_t        ip_tos;          // type of service           
    u_int16_t       ip_len;          // total length              
    u_int16_t       ip_id;           // identification            
    u_int16_t       ip_off;          // fragment offset field     
#define IP_DF 0x4000                 // dont fragment flag        
#define IP_MF 0x2000                 // more fragments flag       
#define IP_OFFMASK 0x1fff            // mask for fragmenting bits 
    u_int8_t        ip_ttl;          // time to live              
    u_int8_t        ip_p;            // protocol                  
    u_int16_t       ip_sum;          // checksum                  
    struct in_addr  ip_src, ip_dst;  // source and dest address   
};

// TCP header
typedef u_int tcp_seq;

struct tcp_hdr {
    u_short source;                // source port
    u_short dest;                  // destination port       
    tcp_seq seq;                   // sequence number        
    tcp_seq ack_seq;               // acknowledgement number 
#if BYTE_ORDER == LITTLE_ENDIAN
    u_int th_x2:4,                 // (unused)   
    th_off:4;                      // data offset
#endif
#if BYTE_ORDER == BIG_ENDIAN
    u_int th_off:4,                 // data offset
    th_x2:4;                        // (unused)
#endif
    u_char flags;
#define FIN 0x01
#define SYN 0x02
#define RST 0x04
#define PUSH 0x08
#define ACK 0x10
#define URG 0x20
#define ECE 0x40
#define CWR 0x80
    u_short th_win;                 // window
    u_short th_sum;                 // checksum
    u_short th_urp;                 // urgent pointer
};

struct udp_hdr {
  u_short source;		    // source port
  u_short dest;	         	    // destination port
  u_short uh_ulen;		    // datagram length
  u_short uh_sum;		    // datagram checksum
};

struct fiveTupel {
    Protocol  protocol;
    in_addr   srcIp;
    u_int16_t srcPort;
    in_addr   dstIp;
    u_int16_t dstPort;
};

struct fingerprint {
    char  name[256];
    int   flowsCnt;    
    int   protocol;

#define X(type, name, size) type name[size];
    X_FIELDS
#undef X
};

#endif // STRUCTS_H
