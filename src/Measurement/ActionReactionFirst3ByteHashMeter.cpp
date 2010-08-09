#include "ActionReactionFirst3ByteHashMeter.h"

float*
Measurement::ActionReactionFirst3ByteHashMeter::getFingerprintProEntry(fingerprint* fp) {
    return fp->actionReactionFirst3bytesPro;
}

int*
Measurement::ActionReactionFirst3ByteHashMeter::getFingerprintCntEntry(fingerprint* fp) {
    return fp->actionReactionFirst3bytesCnt;
}
