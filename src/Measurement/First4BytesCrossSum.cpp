#include <iostream>

#include "First4BytesCrossSum.h"

float*
Measurement::First4BytesCrossSum::getFingerprintProEntry(fingerprint* fp) {
    return fp->first4bytescrosssumPro;
}

int*
Measurement::First4BytesCrossSum::getFingerprintCntEntry(fingerprint* fp) {
    return fp->first4bytescrosssumCnt;
}
