#include <iostream>

#include "DirectionChanges.h"

using namespace std;

float*
Measurement::DirectionChanges::getFingerprintProEntry( fingerprint* fp ) {
    return fp->directionChangesPro;
}

int*
Measurement::DirectionChanges::getFingerprintCntEntry( fingerprint* fp ) {
    return fp->directionChangesCnt;
}
