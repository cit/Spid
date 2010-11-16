// ---------------------------------------------------------------------------
// TcpFlow.cpp
// This class represents a tcpflow and handles the states of it.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>

extern "C" {
#include <arpa/inet.h>
}

#include "TcpFlow.h"

using namespace std;

Flow::TcpFlow::TcpFlow() {
    bFirstTime        = true;
    bInspected        = false;
    state             = LISTEN;
    
    size              = 0;
    packetCnt         = 0;
    lastPacketArrived = 0;
}

void Flow::TcpFlow::AddPacket(Ip::V4* pIpv4) {
    lastPacketArrived = pIpv4->timeStamp.tv_sec;

    if (bFirstTime) {
        id.srcIp   = pIpv4->srcIp;
        id.dstIp   = pIpv4->dstIp;
        id.srcPort = pIpv4->pTcp->srcPort;
        id.dstPort = pIpv4->pTcp->dstPort;

        bFirstTime = false;
    }

    size += pIpv4->frameSize;

    // packets that are necessary for establishment or termination doesn't
    // have a payload, therefore there are not interessting for the measurement
    if ((state == ESTABLISHED and pIpv4->pTcp->payloadSize != 0) or
        (state == HALF_CLOSED and pIpv4->pTcp->payloadSize != 0)) {
        packets.push_back(pIpv4);
        packetCnt++;
    }
    else if (IsEstablishmentInProgress(pIpv4->pTcp)) {
        delete pIpv4;
    }
    else if (IsTerminationInProgress(pIpv4->pTcp)) {
        delete pIpv4;
    }
    else {
        delete pIpv4;
    }

}

bool Flow::TcpFlow::IsEstablishmentInProgress(Ip::Tcp* pTcp) {
    if (pTcp->syn and (state == LISTEN)) {
        state = REQUEST;
        seq   = pTcp->seq;
        return true;
    }

    if (state == REQUEST) {
        if (pTcp->synAck and (pTcp->ackSeq == (seq + 1))) {
            state = GRANTED;
            seq = pTcp->seq;
            return true;
        }
         else if (pTcp->rst and (pTcp->ackSeq == (seq + 1))) {
             state = CLOSED;
             return true;
         }
    }

    if (state == GRANTED) {
        if ( pTcp->ack and (pTcp->ackSeq == (seq + 1))) {
            state = ESTABLISHED;
            return true;
        }
    }

    return false;
}

bool Flow::TcpFlow::IsTerminationInProgress(Ip::Tcp* pTcp) {
    if (state == ESTABLISHED and pTcp->fin) {
        state = FIN_RCVD;
        seq = pTcp->seq;
        return true;
    }

    if (state == FIN_RCVD and
        (pTcp->ack and (pTcp->ackSeq == (seq + 1)))) {
        state = HALF_CLOSED;
        return true;
    }

    if (state == HALF_CLOSED and pTcp->fin) {
        state = FIN_RCVD_2;
        seq = pTcp->seq;
        return true;
    }

    if (state == FIN_RCVD_2 and
        (pTcp->ack and (pTcp->ackSeq == (seq + 1)))) {
        state = CLOSED;
        return true;
    }

    return false;
}

bool Flow::TcpFlow::IsEqual(fiveTupel* pId) {
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

void Flow::TcpFlow::printId() {
    if (bFirstTime == false) {
        cout << "Tcp " 
             << inet_ntoa(id.srcIp) << ":" << id.srcPort << " -> ";
        cout << inet_ntoa(id.dstIp) << ":" << id.dstPort << endl;
    }
    else {
        cerr << "Can't print tcp-id, since no packet was added to the flow"
             << endl;
    }
}

Flow::TcpFlow::~TcpFlow() {
    vector<Ip::V4*>::iterator i;
    for (i = packets.begin(); i != packets.end(); ++i)
        delete *i;
    packets.clear();
}
