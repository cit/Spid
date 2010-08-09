// ---------------------------------------------------------------------------
// FirstNonEmptyPayloadSize.cpp
// This class gets a IP version 4 packet and counts the size and calculates the
// probability. 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include "FirstNonEmptyPayloadSize.h"

Measurement::FirstNonEmptyPayloadSize::FirstNonEmptyPayloadSize(Ip::V4* pIpv4){
    size          = 1;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));
    
    if (pIpv4->protocol == TCP) {
        count[0]   = pIpv4->pTcp->payloadSize;
        total_size = 1460;
    }
    else {
        count[0]   = pIpv4->pUdp->payloadSize;
        total_size = 1476;
    }

    probabilities[0] = count[0] / static_cast<float>(total_size);
}

float*
Measurement::FirstNonEmptyPayloadSize::getFingerprintProEntry(fingerprint* fp){
    return fp->firstNonEmptyPayloadSizePro;
}

int*
Measurement::FirstNonEmptyPayloadSize::getFingerprintCntEntry(fingerprint* fp){
    return fp->firstNonEmptyPayloadSizeCnt;
}
