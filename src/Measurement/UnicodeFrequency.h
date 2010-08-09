// ---------------------------------------------------------------------------
// UnicodeFrequency.h
// The header file from the attribute meter: unicode frequency
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef UNICODEFREQUENCY_H
#define UNICODEFREQUENCY_H

#include "Attributes.h"

namespace Measurement {
    // It scans for alphabetical unicode strings in the first five packets and
    // saves the byte frequency for it. Since some protocols like WMV streams
    // or MMS use unicode strings in their protocols.
    class UnicodeFrequency : public Attributes {

    private:
        // private variables
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
        
    public:    
        // public methods
        #include "UnicodeFrequency.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // UNICODEFREQUENCY_H
