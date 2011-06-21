#ifndef V4_H
#define V4_H

extern "C" {
#include <netinet/in.h>
}

#include "Tcp.h"
#include "Udp.h"

#include "../enums.h"

namespace Ip {

    class Error {
    public:
        const char* error;
        Error(const char* arg) : error(arg) { }
    };

    class V4 {

      private:
        // private variables

        // private methods

      public:
        // public variables
        in_addr            srcIp;                 
        in_addr            dstIp;
        unsigned short int headerSize;
        unsigned short int ipDatagramSize;
        unsigned short int frameSize;
        timeval            timeStamp;
        Protocol           protocol;
        Direction          direction;
        Tcp*               pTcp;
        Udp*               pUdp;

        // public methods
        explicit V4(const u_char* pPacket, const struct pcap_pkthdr* pHeader);
        void     print();
        ~V4();
        
    };

}

#endif // V4_H
