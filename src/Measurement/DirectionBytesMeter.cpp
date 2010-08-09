#include <iostream>

#include "DirectionBytesMeter.h"

float*
Measurement::DirectionBytesMeter::getFingerprintProEntry( fingerprint* fp ) {
    return fp->directionBytesMeterPro;
}

int*
Measurement::DirectionBytesMeter::getFingerprintCntEntry( fingerprint* fp ) {
    return fp->directionBytesMeterCnt;
}
