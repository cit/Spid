#include "AllPacketsFirst8BytesEqualityMeter.h"

float*
Measurement::AllPacketsFirst8BytesEqualityMeter::getFingerprintProEntry(fingerprint* fp) {
    return fp->allPacketsFirst8BytesPro;
}

int*
Measurement::AllPacketsFirst8BytesEqualityMeter::getFingerprintCntEntry(fingerprint* fp) {
    return fp->allPacketsFirst8BytesCnt;
}
