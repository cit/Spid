// ---------------------------------------------------------------------------
// BytePairsReoccuring.h
// The header file from the attribute meter: byte pairs reoccuring
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef BYTEPAIRSREOCURRING_H
#define BYTEPAIRSREOCURRING_H

#include "Attributes.h"

namespace Measurement {
    // This measurement identifies bytes that occur more than once within the
    // first 16 bytes of the first packet. E.g. it identifies the “SS” in the
    // SSH-banner or the “TT” in the HTTP GET and POST request.
    class BytePairsReocurring : public Attributes {

    public:
        #include "BytePairsReocurring.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
}

#endif // BYTEPAIRSREOCURRING_H
