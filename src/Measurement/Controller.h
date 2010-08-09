// ---------------------------------------------------------------------------
// Controller.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <typeinfo>

#include "../Flow/TcpFlow.h"
#include "../Flow/UdpFlow.h"

#include "../structs.h"
#include "../Spid.h"

#include "ByteFrequency.h"
#include "ByteFrequencyOtherDirection.h"
#include "FirstNonEmptyPayloadSize.h"
#include "DirectionBytesMeter.h"
#include "DirectionChanges.h"
#include "BytePairsReocurring.h"
#include "Entropy.h"
//#include "ByteDistance.h"
#include "First4BytesCrossSum.h"
#include "FirstPacketPerDirectionNibbles.h"
#include "First32BytesFrequency.h"
#include "ActionReactionFirst3ByteHashMeter.h"
#include "FirstBitPositionsMeter.h"
#include "AllPacketsFirst8BytesEqualityMeter.h"
#include "UnicodeFrequency.h"

namespace Measurement {
    
    class Controller {

      private:
        // private variables
        vector<Attributes*>           attributes;
        vector<Attributes*>::iterator iter;
        fingerprint*                  db;
        Spid*                         spid;
        unsigned int                  dbSize;
        unsigned short attributesSize;

      public:
        // Constructor of this file
        explicit Controller();

        // This file contains the template methods
        #include "Controller.tcc"

        // In this method the actual identification happens
        short IdentifyFlow(fingerprint* fp);

        // This method calculates the kullback–leibler divergence, which is
        // necessary for identification.
        float KullbackLeiblerDivergence(float* dbPro, float* fpPro);

        // This method prints some information that contains in the fingerprint
        // database. 
        void PrintFingerprintDb(fingerprint* fp);

        // It writes the complete fingerprint database to a binary file. This
        // is necessary if a flow will be learned.
        void WriteFingerprintDb(char* file, fingerprint* fp);

        // It reads the complete fingerprint database. This database is needed
        // for identification
        fingerprint* ReadFingerprintDb(char* file);

        // Deconstructor of this class
        ~Controller();
    };
}

#endif // CONTROLLER_H
