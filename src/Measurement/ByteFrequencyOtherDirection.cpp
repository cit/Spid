#include <iostream>

#include "ByteFrequencyOtherDirection.h"

using namespace std;

float*
Measurement::ByteFrequencyOtherDirection::getFingerprintProEntry(fingerprint* fp){
    return fp->byteFreqOtherDirectionPro;
}

int*
Measurement::ByteFrequencyOtherDirection::getFingerprintCntEntry(fingerprint* fp) {
    return fp->byteFreqOtherDirectionCnt;
}
