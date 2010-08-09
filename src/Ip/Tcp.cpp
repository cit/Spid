// ---------------------------------------------------------------------------
// Tcp.cpp
// It extracts all the tcp information and puts it into a class.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>
#include <cstring>

extern "C" {
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
}
 
#include "Tcp.h"
#include "V4.h"

#include "../constants.h"

using namespace std;

Ip::Tcp::Tcp(const u_char* pPacket, unsigned short int ipDatagramSize,
             unsigned short int ipHeaderSize) {
    struct tcphdr* p_tcp_header = (struct tcphdr*)(pPacket + ETHERNET_SIZE
                                                   + ipHeaderSize);
    // calculate the tcpheader size (doff * 4)
    headerSize = p_tcp_header->doff << 2;

    // check if the tcp header size is correct
    if (headerSize < 20)
        throw Ip::Error("Warning: Invalid TCP header length.");
    
    // get a char pointer to the tcp payload
    u_char* pPayload = const_cast<u_char*>(pPacket + ETHERNET_SIZE
                                                   + ipHeaderSize
                                                   + headerSize);

    // calculate the size of the payload
    payloadSize = ipDatagramSize - ipHeaderSize - headerSize;

    // if the size of the payload is bigger than 1460, something is wrong
    // with this packet
    if (payloadSize > 1460)
        throw Ip::Error("Warning: malformed tcp packet or jumbo frame received");
    // copy the payload 
    payload = new u_char[payloadSize]();
    memcpy(payload, pPayload, payloadSize);
    
    // set the source and destination ports and convert it from network byte
    // order to host byte order
    srcPort = ntohs(p_tcp_header->source);
    dstPort = ntohs(p_tcp_header->dest);

    // set the tcp flags
    ack = p_tcp_header->ack;
    syn = p_tcp_header->syn;
    fin = p_tcp_header->fin;
    rst = p_tcp_header->rst;
    
    // is true wenn the ack-flag and the syn-flag is set
    synAck = (p_tcp_header->ack and p_tcp_header->syn);

    // initial sequence numbers
    seq    = ntohl(p_tcp_header->seq);
    ackSeq = ntohl(p_tcp_header->ack_seq);
}

void Ip::Tcp::print() {
    cout << "Flags: Syn: " << syn << " Ack: " << ack << " FIN: " << fin
         << " RST: " << rst << endl;
    cout << "Seq: " << seq << " Ack-Seq: " << ackSeq << endl;

    if (payloadSize > 0) {
        cout << "Payload:" << endl;
        printPayload(payload, payloadSize);
    }
    
    printf("\n");
}

void Ip::Tcp::printPayload(u_char* payload, int len) {
    u_char* p_payload = payload;

    for(u_short i = 1; i <=  len; ++i) {
        printf("%02X ", *p_payload);
        p_payload++;

        // print extra space after 8th byte for visual aid 
        if (i%8 == 0)
            printf(" ");

        // after the 16th byte print the characters if possible
        if(i%16 == 0) {

            u_char* foo = p_payload - 16;
            for (int y = 0; y < 16; ++y) {
                if (isprint(*foo))
                    printf("%c", *foo);
		else
                    printf(".");
		foo++;
            }
            
            printf("\n");
        }
        
    }
}

Ip::Tcp::~Tcp() {
    delete [] payload;
}
