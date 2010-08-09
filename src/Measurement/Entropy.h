// ---------------------------------------------------------------------------
// Entropy.h
// The header file from the attribute meter: entropy
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef ENTROPY_H
#define ENTROPY_H

#include "Attributes.h"
#include "../structs.h"

namespace Measurement {
    // This class is an attribute and inherits from Attributes.h. It takes the
    // bytefrequency of each direction and calculates the entropy.
    class Entropy : public Attributes {

    public:
        float* entropy;

        Entropy(fingerprint* fp);
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };

}

#endif // ENTROPY_H
