// ---------------------------------------------------------------------------
// Tcp.h
// It extracts all the tcp information and puts it into a class.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef TCP_H
#define TCP_H

extern "C" {
#include <pcap/pcap.h>
}

namespace Ip {
    // This class takes from libpcap a pointer to a packet and extracts all
    // the informations of a tcp-packets and puts it into a class.
    class Tcp {
        
      public:
        u_short srcPort;                    // source port number
        u_short dstPort;                    // destination port number
        bool ack, syn, synAck, fin, rst;    // flags of a tcp packet
        u_long seq;                         // sequence number
        u_long ackSeq;                      // ack sequence number
        u_short headerSize;                 // size of the header
        u_short payloadSize;                // size of the payload
        u_char* payload;                    // the payload itself

        // Constructor of this class
        Tcp(const u_char* pPacket,u_short ipDatagramSize,u_short ipHeaderSize);

        // This method prints all the extracted information from this packet
        void print();

        // This method prints the whole payload as ascii and hexadecimal
        void printPayload(u_char*payload, int len);

        // Deconstructor of this class
        ~Tcp();
        
    };
}

#endif // TCP_H
