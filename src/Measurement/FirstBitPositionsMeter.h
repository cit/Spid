// ---------------------------------------------------------------------------
// FirstBitPositionsMeter.h
// The header file from the attribute meter: first bit positions meter
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef FIRSTBITPOSITIONSMETER_H
#define FIRSTBITPOSITIONSMETER_H

#include "Attributes.h"

namespace Measurement { 
    // Especially UDP protocols have a small header, which consists of fields
    // and flags on bit level. This fact makes it hard for the byte frequency
    // meter to detect the particular protocol. This attribute meter counts
    // the frequency of a single bit in connection with its offset. The first
    // 128 bits will be viewed and counted.
    class FirstBitPositionsMeter : public Attributes {

    private:
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
    public:
        #include "FirstBitPositionsMeter.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // FIRSTBITPOSITIONSMETER_H
