// ---------------------------------------------------------------------------
// First4BytesCrossSum.h
// The header file from the attribute meter: first 4 bytes cross sum
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef FIRST4BYTESCROSSSUM_H
#define FIRST4BYTESCROSSSUM_H

#include "Attributes.h"

#include <cmath>

namespace Measurement  {
    // The first 4 bytes of the first packet in each direction are very
    // characteristic for most application protocols. For the first 4 bytes
    // a hashvalue is calculated. To simplify matters we make use of a
    // cross-sum. A sample hash function for HTTP is shown:
    //     1: 47 45 54 20 G E T   = 31
    //     2: 48 54 54 50 H T T P = 35
    class First4BytesCrossSum : public Attributes {
    private:
        // private variables
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
        
    public:
        // public variables
        
        // public methods
        #include "First4BytesCrossSum.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
}

#endif // FIRST4BYTESCROSSSUM_H
