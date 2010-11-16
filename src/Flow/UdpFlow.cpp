// ---------------------------------------------------------------------------
// UdpFlow.cpp
// This class 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>

extern "C" {
#include <arpa/inet.h>
}

#include "UdpFlow.h"

using namespace std;

Flow::UdpFlow::UdpFlow() {
    bFirstTime = true;
    bInspected = false;
    packetCnt  = 0;
}

void Flow::UdpFlow::AddPacket(Ip::V4* pIpv4) {
    lastPacketArrived = pIpv4->timeStamp.tv_sec;
    
    if (bFirstTime) {
        id.srcIp   = pIpv4->srcIp;
        id.srcPort = pIpv4->pUdp->srcPort;
        id.dstIp   = pIpv4->dstIp;
        id.dstPort = pIpv4->pUdp->dstPort;

        bFirstTime = false;
    }

    size += pIpv4->frameSize;

    if (pIpv4->pUdp->payloadSize != 0) {
        packets.push_back(pIpv4);
        packetCnt++;
    }
    else
        delete pIpv4;
}

bool Flow::UdpFlow::IsEqual(fiveTupel* pId) {
    if (id.srcPort != pId->srcPort)
        return false;
    else if (id.dstPort != pId->dstPort)
        return false;
    else if (id.srcIp.s_addr != pId->srcIp.s_addr)
        return false;
    else if (id.dstIp.s_addr != pId->dstIp.s_addr)
        return false;

    return true;
}

void Flow::UdpFlow::DeletePackets() {
    vector<Ip::V4*>::iterator i;
    for (i = packets.begin(); i != packets.end(); ++i)
        delete *i;
    packets.clear();
}

void Flow::UdpFlow::printId() {
    if (bFirstTime == false) {
        cout << "Udp "
             << inet_ntoa(id.srcIp) << ":" << id.srcPort << " -> ";
        cout << inet_ntoa(id.dstIp) << ":" << id.dstPort << endl;
    }
    else {
        cerr << "Can't print udp-id, since no packet was added to the flow"
             << endl;
    }
}

Flow::UdpFlow::~UdpFlow() {
    DeletePackets();
}
