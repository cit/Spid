// ---------------------------------------------------------------------------
// First32BytesFrequency.h
// The header file from the attribute meter: first 32 bytes frequency
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef FIRST32BYTESFREQUENCY_H
#define FIRST32BYTESFREQUENCY_H

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
    class First32BytesFrequency : public Attributes {

    private:
        // private variables
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
        
    public:
        // public methods
        #include "First32BytesFrequency.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // FIRST32BYTESFREQUENCY_H
