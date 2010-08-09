// ---------------------------------------------------------------------------
// ByteFrequencyOtherDirection.h
// The header file from the attribute meter: byte frequency other direction 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef BYTEFREQUENCYOTHERDIRECTION_H
#define BYTEFREQUENCYOTHERDIRECTION_H

#include "Attributes.h"

namespace Measurement {
    // This class is an attribute and inherits from Attributs.h. It measures
    // the bytefrequency of the first packet from the other direction.
    // ByteFrequency measures the bytefrequency from originator to responder and
    // ByteFrequencyOtherDirection measures from responder to originator.
    class ByteFrequencyOtherDirection : public Attributes {
    private:
        // private variables
        u_char* p_payload;                 // pointer to the payload of a packet
        u_int   payload_size;              // size of this packet
        
    public:
        // public methods
        #include "ByteFrequencyOtherDirection.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };

}

#endif // BYTEFREQUENCYOTHERDIRECTION_H
