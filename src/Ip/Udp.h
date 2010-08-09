// ---------------------------------------------------------------------------
// Udp.h
// It extracts all the udp information and puts it into a class.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef UDP_H
#define UDP_H

extern "C" {
#include <pcap/pcap.h>
}

namespace Ip {

    class Udp {

    private:
        static const unsigned char kUdpHeaderSize;

      public:
        unsigned short srcPort;
        unsigned short dstPort;

        unsigned short int payloadSize;
        u_char* payload;

        explicit Udp(const u_char* pPacket, unsigned short int ipDatagramSize,
                     unsigned short int ipHeaderSize );
        ~Udp();
        void print();
        void printPayload(u_char* payload, int len);
    };
}

#endif // UDP_H
