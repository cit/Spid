#include <iostream>

#include "First32BytesFrequency.h"

float*
Measurement::First32BytesFrequency::getFingerprintProEntry(fingerprint* fp) {
    return fp->first32bytesFreqPro;
}

int*
Measurement::First32BytesFrequency::getFingerprintCntEntry(fingerprint* fp) {
    return fp->first32bytesFreqCnt;
}
