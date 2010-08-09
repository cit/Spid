// ---------------------------------------------------------------------------
// Entropy.tcc
// This class gets a tcp or udp flow and calculates the entropy of the data.
// 
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <cmath>

#include "Entropy.h"

using namespace std;

Measurement::Entropy::Entropy(fingerprint* fp) {
    size          = 2;
    total_size    = 8;                  // this is the max value of an entropy
                                        // of 2^8 = 256
    entropy       = new float[size]();
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));
    memset(entropy,0,(size*sizeof(float)));
    
    for (unsigned short i = 0; i < 256; ++i) {
        if (fp->byteFreqPro[i] != 0) 
            entropy[0] += -(fp->byteFreqPro[i]
                            * ((log(fp->byteFreqPro[i] + 0.0
                                    / log(2.0))) ));
        
        if (fp->byteFreqOtherDirectionPro[i] != 0) 
            entropy[1] += -(fp->byteFreqOtherDirectionPro[i]
                            * ((log(fp->byteFreqOtherDirectionPro[i] + 0.0
                                   / log(2.0))) ));

    }

    count[0] = static_cast<int>(floor(entropy[0]+0.5));
    count[1] = static_cast<int>(floor(entropy[1]+0.5));

    probabilities[0] = count[0] / static_cast<float>(total_size);
    probabilities[1] = count[1] / static_cast<float>(total_size);

    delete [] entropy;
 }

float* Measurement::Entropy::getFingerprintProEntry(fingerprint* fp) {
    return fp->entropyPro;
}

int* Measurement::Entropy::getFingerprintCntEntry(fingerprint* fp) {
    return fp->entropyCnt;
}
