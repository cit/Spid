// ---------------------------------------------------------------------------
// AllPacketsFirst8BytesEquality.h
// The header file from the attribute meter: All packets first 8 bytes equality
// meter
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef ALLPACKETSFIRST8BYTESEQUALITYMETER_H
#define ALLPACKETSFIRST8BYTESEQUALITYMETER_H

#include "Attributes.h"

namespace Measurement { 

    class AllPacketsFirst8BytesEqualityMeter : public Attributes {

    private:
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
    public:
        #include "AllPacketsFirst8BytesEqualityMeter.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // ALLPACKETSFIRST8BYTESEQUALITYMETER
