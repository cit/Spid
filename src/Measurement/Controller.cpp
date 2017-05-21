// ---------------------------------------------------------------------------
// Controller.cpp
// This is the controller from all the attribute meters.
//
// Author: Florian Adamsky <fa-spid@haktar.org>
// ---------------------------------------------------------------------------
#include "Controller.h"

using namespace std;
using namespace Measurement;

Measurement::Controller::Controller() {
    spid  = Spid::getInstance();
    refDB = new FingerprintDB();

    if (spid->pFingerprintFile)
        refDB->DeserializeFromFile(spid->pFingerprintFile);
}

short
Measurement::Controller::IdentifyFlow(fingerprint* fp) {
    float* kullback_leibler_div = new float[refDB->size]();
    memset(kullback_leibler_div, 0, (refDB->size*sizeof(float)));

    // optimisation: when the program is started, the size of the attributes
    // will never change, so we have to call the method size only once
    if (attributesSize == 0)
        attributesSize = attributes.size();

    for (unsigned short i = 0; i < refDB->size; ++i) {

        if (fp->protocol != refDB->fp[i].protocol)
            continue;

        // if (spid->bDebug)
        //     cout << db[i].name << endl;

        for (unsigned short x = 0; x < attributesSize; ++x) {
            Attributes* attr = attributes.at(x);

            float kl_div = 0.0;
            for (unsigned short y = 0; y < attr->size; ++y) {
                float* db_pro = attr->getFingerprintProEntry(&refDB->fp[i]);
                float* fp_pro = attr->getFingerprintProEntry(fp);

                // calculate the kullback-leibler-divergence
                float extension_one = 0.0;
                if (db_pro[y] > 0)
                    extension_one = (log((db_pro[y] + 0.0))/log(2.0));

                float extension_two = 0.0;
                if (fp_pro[y] > 0)
                    extension_two = (log((fp_pro[y] + 0.0))/log(2.0));

                float result = fp_pro[y] * (extension_two - extension_one);
                if (result < 0)
                    result *= -1;

                kl_div +=result;
            }
            kullback_leibler_div[i] += kl_div;

            // if (spid->bDebug)
            //     cout << typeid(*attr).name() << ": " << kl_div << endl;
        }
        // if (spid->bDebug)
        //     cout << "insgesamt: " << kullback_leibler_div[i] << endl;
    }

    unsigned short smallest = 0;
    float tmp = 100.0;

    for (unsigned short i = 0; i < refDB->size; ++i) {
        if (fp->protocol != refDB->fp[i].protocol)
            continue;
        if (kullback_leibler_div[i] < tmp and kullback_leibler_div[i] >= 0) {
            smallest = i;
            tmp = kullback_leibler_div[i];
        }
    }

    // if (spid->bDebug)
    //     cout << "lowest value is: " << tmp << endl;

    delete [] kullback_leibler_div;

    return (tmp < spid->kThreshold) ? smallest : -1;
}

Measurement::Controller::~Controller( ) {
    if (spid->bLearnModus) {
        refDB->SerializeToFile(spid->pLearnFile);
        refDB->PrintDB();
    }

    delete refDB;
}
