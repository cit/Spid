#ifndef STRUCTS_H
#define STRUCTS_H

extern "C" {
#include <arpa/inet.h>
}

#include "enums.h"
#include "fp-macro.def"

struct fiveTupel {
    Protocol  protocol;
    in_addr   srcIp;
    u_int16_t srcPort;
    in_addr   dstIp;
    u_int16_t dstPort;
};

struct fingerprint {
    char  name[256];
    int   flowsCnt;    
    int   protocol;

#define X(type, name, size) type name[size];
    X_FIELDS
#undef X
};

#endif // STRUCTS_H
