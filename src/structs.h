#ifndef STRUCTS_H
#define STRUCTS_H

extern "C" {
#include <arpa/inet.h>
}

#include "enums.h"


struct fiveTupel {
    Protocol  protocol;
    in_addr   srcIp;
    u_int16_t srcPort;
    in_addr   dstIp;
    u_int16_t dstPort;
};

struct fingerprint {
    char     name[256];
    int      flowsCnt;    
    Protocol protocol;

    float unicodeFreqPro[256];
    int unicodeFreqCnt[256];

    float allPacketsFirst8BytesPro[8];
    int   allPacketsFirst8BytesCnt[8];

    float firstBitPositionsMeterPro[64];
    int   firstBitPositionsMeterCnt[64];

    float actionReactionFirst3bytesPro[256];
    int   actionReactionFirst3bytesCnt[256];

    float first32bytesFreqPro[256];
    int   first32bytesFreqCnt[256];

    float FirstPacketNibblesPro[256];
    int   FirstPacketNibblesCnt[256];

    float first4bytescrosssumPro[76];
    int   first4bytescrosssumCnt[76];
    
    float entropyPro[2];
    int   entropyCnt[2];

    float directionChangesPro[1];
    int   directionChangesCnt[1];
    
    float firstNonEmptyPayloadSizePro[1];
    int   firstNonEmptyPayloadSizeCnt[1];
    
    float directionBytesMeterPro[2];
    int   directionBytesMeterCnt[2];

    float bytePairsReocurringPro[256];
    int   bytePairsReocurringCnt[256];

    //float byteDistancePro[256];
    //int   byteDistanceCnt[256];

    float byteFreqPro[256];
    int   byteFreqCnt[256];
    
    float byteFreqOtherDirectionPro[256];
    int   byteFreqOtherDirectionCnt[256];

};

#endif // STRUCTS_H
