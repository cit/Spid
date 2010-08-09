// ---------------------------------------------------------------------------
// ActionReactionFirst3ByteHashMeter.h
// The header file from the attribute meter: action reaction first 3 bytes
// hash meter
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef ACTIONREACTIONFIRST3BYTEHASHMETER_H
#define ACTIONREACTIONFIRST3BYTEHASHMETER_H

#include "Attributes.h"

namespace Measurement { 
    // It generates a hash-function of the first 3 bytes of each packet that
    // wasn’t sent in the same direction as the previous one. The idea behind
    // this measurement is to get a connection between a request and a response,
    // especially for command based protocols like HTTP, FTP or POP3.
    class ActionReactionFirst3ByteHashMeter : public Attributes {

    private:
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet 
    public:
        #include "ActionReactionFirst3ByteHashMeter.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
    
}

#endif // ACTIONREACTIONFIRST3BYTEHASHMETER
