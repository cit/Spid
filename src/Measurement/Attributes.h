// ---------------------------------------------------------------------------
// Attributes.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "../Flow/TcpFlow.h"
#include "../Flow/UdpFlow.h"
#include "../Spid.h"
    

namespace Measurement {
    // This class is a template for every attribute meter. Is defines the basic
    // methods.
    class Attributes {

    public:
        // public variables
        unsigned int   size;
        unsigned int   total_size;
        unsigned short all_packets;

        // public methods

        // Every attribute meter has a method to return the name of the array
        // from the scruct fingerprint. In this case it returns the name of the
        // propabiliy array.
        Attributes();
        virtual float* getFingerprintProEntry(fingerprint* pDb) = 0;
        
        virtual int* getFingerprintCntEntry(fingerprint* fp) = 0;
        virtual void setFingerprintPtr(int* fpCnt, float* fpPro,
                                       unsigned int arrSize);
        virtual void ImproveApproximation(fingerprint* pDb);
        ~Attributes();

    protected:
        // protected variables
        float* probabilities;
        int*   count;
    };

}

#endif // ATTRIBUTES_H
