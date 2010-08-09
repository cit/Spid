// ---------------------------------------------------------------------------
// FirstNonEmptyPayloadSize.h
// The header file from the attribute meter: first non empty payload size
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef FIRSTNONEMPTYPAYLOADSIZE_H
#define FIRSTNONEMPTYPAYLOADSIZE_H

#include "Attributes.h"

#include "../Ip/V4.h"
#include "../structs.h"

namespace Measurement {
    // Payload length of the first packet in a flow [19]. In most cases the
    // first packet contains information for initialisation of a session. The
    // first packet size of a HTTP session is only between 120 and 1000 bytes.
    // POP3 for example is between 10 and 100 bytes.
    class FirstNonEmptyPayloadSize : public Attributes {

    public:
        explicit FirstNonEmptyPayloadSize(Ip::V4* pIpv4);
        float* getFingerprintProEntry(fingerprint* fp);
        int*   getFingerprintCntEntry(fingerprint* fp);
    };

}

#endif // FIRSTNONEMPTYPAYLOADSIZE_H
