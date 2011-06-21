// ---------------------------------------------------------------------------
// Udp.cpp
// It extracts all the udp information and puts it into a class.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>
#include <cstring>

extern "C" {
#include <arpa/inet.h>
}

#include "Udp.h"
#include "V4.h"

#include "../constants.h"
#include "../structs.h"

using namespace std;

const unsigned char Ip::Udp::kUdpHeaderSize = 8; // UDP header size is always
                                                 // 8 bytes

Ip::Udp::Udp(const u_char* pPacket, unsigned short int ipDatagramSize,
             unsigned short int ipHeaderSize) {
    struct udp_hdr* p_udp_hdr = (struct udp_hdr *)(pPacket + ETHERNET_SIZE
                                                              + ipHeaderSize);

    // get a char pointer to the tcp payload
    u_char* pPayload = const_cast<u_char*>(pPacket + ETHERNET_SIZE
                                                   + ipHeaderSize
                                                   + kUdpHeaderSize);
    
    // calculate the payload size. UDP header has always a size of 8 bytes
    payloadSize = ipDatagramSize - ipHeaderSize - kUdpHeaderSize;

    // check if the payload is malformed
    if (payloadSize > 1460)
        throw Ip::Error("Warning: malformed udp packet or jumbo frame received");
    // copy the payload 
    payload = new u_char[payloadSize]();
    memcpy(payload, pPayload, payloadSize);

    // set the source and destination ports
    srcPort = ntohs(p_udp_hdr->source);
    dstPort = ntohs(p_udp_hdr->dest);
}

void Ip::Udp::print() {
    if (payloadSize > 0) {
        cout << "Payload:" << endl;
        printPayload(payload, payloadSize);
    }
    
    printf("\n");
}

void Ip::Udp::printPayload(u_char* payload, int len) {
    u_char* p_payload = payload;

    for(int i = 1; i <= len; ++i) {
        printf("%02X ", *p_payload);
        p_payload++;

        // print extra space after 8th byte for visual aid 
        if (i%8 == 0)
            printf(" ");

        // after the 16th byte print the characters if possible
        if(i%16 == 0) {

            u_char* foo = p_payload - 16;
            for (unsigned short y = 0; y < 16; ++y) {
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

Ip::Udp::~Udp() {
    delete [] payload;
}
