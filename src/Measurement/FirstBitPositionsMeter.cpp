#include "FirstBitPositionsMeter.h"

float*
Measurement::FirstBitPositionsMeter::getFingerprintProEntry(fingerprint* fp) {
    return fp->firstBitPositionsMeterPro;
}

int*
Measurement::FirstBitPositionsMeter::getFingerprintCntEntry(fingerprint* fp) {
    return fp->firstBitPositionsMeterCnt;
}
