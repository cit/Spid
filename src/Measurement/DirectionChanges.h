// ---------------------------------------------------------------------------
// DirectionChanges.h
// The header file from the attribute meter: direction changes
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef DIRECTIONCHANGES_H
#define DIRECTIONCHANGES_H

#include "Attributes.h"

#include "../Spid.h"

namespace Measurement {
    // It measures how often the protocol or the application communication
    // changes the direction. Interactive protocols like Telnet, SSH or FTP
    // have frequent direction changes, whereas streaming protocols have very
    // few.
    class DirectionChanges : public Attributes {

    public:
        #include "DirectionChanges.tcc"
        float* getFingerprintProEntry( fingerprint* fp );
        int*   getFingerprintCntEntry( fingerprint* fp );
    };

}

#endif // DIRECTIONCHANGES_H
