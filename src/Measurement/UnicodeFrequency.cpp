#include <iostream>

#include "UnicodeFrequency.h"

float*
Measurement::UnicodeFrequency::getFingerprintProEntry(fingerprint* fp) {
    return fp->unicodeFreqPro;
}

int*
Measurement::UnicodeFrequency::getFingerprintCntEntry(fingerprint* fp) {    
    return fp->unicodeFreqCnt;
}
