// ---------------------------------------------------------------------------
// Attributes.tcc
//
//
// Author: Florian Adamsky <fa-spid@haktar.org>
// ---------------------------------------------------------------------------
#include <iostream>

#include "Attributes.h"

using namespace std;

Measurement::Attributes::Attributes() {
    all_packets = Spid::getInstance()->kNumberOfPacketsToAnalyze;
}

void
Measurement::Attributes::setFingerprintPtr(int* fpCnt, float* fpPro,
                                           u_int arrSize) {
    if (arrSize != size) {
        cerr << "Warning: the size of the two arrays is not identical" << endl;
        exit(EXIT_FAILURE);
    }

    for (u_int i = 0; i < size; ++i) {
        fpCnt[i] = count[i];
        fpPro[i] = probabilities[i];
    }
}

void
Measurement::Attributes::ImproveApproximation(fingerprint* pDb) {
    float* pro = getFingerprintProEntry(pDb);
    int*   cnt = getFingerprintCntEntry(pDb);

    for (u_int i = 0; i < size; ++i) {
        if (pro[i] > 0) {
            pro[i] = (cnt[i] + count[i]) /
                (cnt[i] / pro[i] + total_size);
            cnt[i] += count[i];
        }
        else {
            pro[i] = probabilities[i];
            cnt[i] = count[i];
        }
    }

}

Measurement::Attributes::~Attributes() {
    delete [] probabilities;
    delete [] count;
}
