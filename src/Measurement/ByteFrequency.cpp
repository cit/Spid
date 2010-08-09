#include <iostream>

#include "ByteFrequency.h"

float*
Measurement::ByteFrequency::getFingerprintProEntry(fingerprint* fp) {
    return fp ->byteFreqPro;
}

int*
Measurement::ByteFrequency::getFingerprintCntEntry(fingerprint* fp) {
    return fp->byteFreqCnt;
}
