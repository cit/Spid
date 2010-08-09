#include <iostream>

#include "BytePairsReocurring.h"

using namespace std;

float*
Measurement::BytePairsReocurring::getFingerprintProEntry( fingerprint* fp ) {
    return fp->bytePairsReocurringPro;
}

int*
Measurement::BytePairsReocurring::getFingerprintCntEntry( fingerprint* fp ) {
    return fp->bytePairsReocurringCnt;
}
