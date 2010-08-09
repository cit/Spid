// ---------------------------------------------------------------------------
// FirstPacketPerDirectionNibbles.h
// The header file from the attribute meter: first packet per direction nibble
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------

#ifndef FIRSTPACKETPERDIRECTIONNIBBLES_H
#define FIRSTPACKETPERDIRECTIONNIBBLES_H

#include "Attributes.h"

namespace Measurement {
    // This measurement calculates the nibbler for each direction
    class FirstPacketPerDirectionNibbles : public Attributes {

    public:
        // public methods
        #include "FirstPacketPerDirectionNibbles.tcc"
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };
}

#endif // FIRSTPACKETPERDIRECTIONNIBBLES_H
