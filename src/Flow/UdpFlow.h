#ifndef UDPFLOW_H
#define UDPFLOW_H

#include <vector>

#include "../Ip/V4.h"
#include "../structs.h"

using namespace std;

namespace Flow {

    class UdpFlow {

      private:
        // private variables
        unsigned long size;
        bool          bFirstTime;

        // private methods

      public:
        // public variables
        vector<Ip::V4*> packets;
        fiveTupel       id;
        unsigned int    lastPacketArrived;
        bool            bInspected;
        unsigned long packetCnt; 

        // public methods
        explicit UdpFlow();
        void     AddPacket(Ip::V4* pIpv4);
        bool     IsEqual(fiveTupel* pId);
        void     DeletePackets();
        void     printId();
        ~UdpFlow();

    };

}

#endif // UDPFLOW_H
