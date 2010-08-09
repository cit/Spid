// ---------------------------------------------------------------------------
// ByteFrequency.h
// The header file from the attribute meter: byte frequency 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef BYTEFREQUENCY_H
#define BYTEFREQUENCY_H

#include "Attributes.h"

#include "../Flow/TcpFlow.h"
#include "../Flow/UdpFlow.h"
#include "../structs.h"
#include "../enums.h"

namespace Measurement {
    // This measurement operates on the first packet of each direction and
    // counts the frequency of a byte in the payload. Encrypted or compressed
    // data appear in an even distribution, whereas data in plain-text show an
    // uneven distribution
    class ByteFrequency : public Attributes {
        
    private:
        // private variables
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
        
    public:
        // public variables
        
        // public methods
        #include "ByteFrequency.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // BYTEFREQUENCY_H
