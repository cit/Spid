// ---------------------------------------------------------------------------
// V4.cpp
// A class for an internet protocol packet version 4.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>

extern "C" {
#include <arpa/inet.h>
#include <netinet/ip.h>
}

#include "V4.h"

#include "../constants.h"

using namespace std;

Ip::V4::V4(const u_char* pPacket, const struct pcap_pkthdr* pHeader) {
    struct ip* p_ip_header = (struct ip*)(pPacket + ETHERNET_SIZE);
    
    // extract the source and the destination ip-adrress
    srcIp = (in_addr) p_ip_header->ip_src;
    dstIp = (in_addr) p_ip_header->ip_dst;
    
    // convert datagram network byte order to host byte order and calculate
    // the header size
    ipDatagramSize = ntohs(p_ip_header->ip_len);
    headerSize     = p_ip_header->ip_hl << 2;
    
    // check if the headersize is correct
    if (headerSize < 20)
        throw Ip::Error("Warning: Invalid IP header length.");
    
    frameSize = pHeader->len;
    timeStamp = pHeader->ts;
    
    pUdp = NULL; pTcp = NULL;
    
    if (p_ip_header->ip_p == TCP_ID) {
        pTcp     = new Tcp(pPacket, ipDatagramSize, headerSize);
        protocol = TCP;
    }
    else if (p_ip_header->ip_p == UDP_ID) {
        pUdp     = new Udp(pPacket, ipDatagramSize, headerSize);
        protocol = UDP;
    }
    else {
        throw Ip::Error("Warning: Packet received with unsupported protocol-type");
    }
}

void Ip::V4::print( ) {
    cout << "\nProtocol: " <<
        ((protocol == TCP) ? "TCP" : "UDP") << endl;
    cout << "FrameSize: " <<
        frameSize << " Bytes" << endl;
    cout << "Timestamp: " <<
        ctime((const time_t*)&timeStamp.tv_sec);
    
    if (protocol == TCP) {
        cout << "Source: " <<
            inet_ntoa(srcIp) << ":" << pTcp->srcPort << endl;
        cout << "Destination: " <<
            inet_ntoa(dstIp) << ":" << pTcp->dstPort << endl;
        pTcp->print();
    }
    else {
        cout << "Source: " <<
            inet_ntoa(srcIp) << ":" << pUdp->srcPort << endl;
        cout << "Destination: " <<
            inet_ntoa(dstIp) << ":" << pUdp->dstPort << endl;
        pUdp->print();
    }
    
}

Ip::V4::~V4() {
    delete pTcp;
    delete pUdp;
}
