#include "FirstPacketPerDirectionNibbles.h"

float*
Measurement::FirstPacketPerDirectionNibbles::getFingerprintProEntry(fingerprint *fp) {
    return fp->FirstPacketNibblesPro;
}

int*
Measurement::FirstPacketPerDirectionNibbles::getFingerprintCntEntry(fingerprint *fp) {
    return fp->FirstPacketNibblesCnt;
}
