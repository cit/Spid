#ifndef TCPFLOW_H
#define TCPFLOW_H

#include <vector>

#include "../Ip/V4.h"
#include "../Ip/Tcp.h"

#include "../enums.h"
#include "../structs.h"

using namespace std;

namespace Flow{
    class TcpFlow {

      private:
        // private variables
        unsigned long  seq;
        unsigned long  size;

        bool           bFirstTime;

        // private methods
        bool IsEstablishmentInProgress(Ip::Tcp* pTcp);
        bool IsTerminationInProgress(Ip::Tcp* pTcp);

      public:
        // public variables
        vector<Ip::V4*> packets;
        TcpStates       state;
        fiveTupel       id;
        unsigned int    lastPacketArrived;
        bool            bInspected;
        unsigned short packetCnt;

        // public methods
        explicit TcpFlow();
        void     AddPacket(Ip::V4* pIpv4);
        bool     IsEqual(fiveTupel* pId);
        void     printId();
        ~TcpFlow();
        
    };
}

#endif // TCPFLOW_H
