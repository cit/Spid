// ---------------------------------------------------------------------------
// Controller.cpp
// This is the controller from all the attribute meters. 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
extern "C" {
#include <sys/stat.h>
}

#include "Controller.h"

using namespace std;
using namespace Measurement;

Measurement::Controller::Controller() {
    spid = Spid::getInstance();

    if (spid->pFingerprintFile) {
        db = ReadFingerprintDb(spid->pFingerprintFile);
        // if (spid->bDebug)
        //     PrintFingerprintDb(db);
    }
    else {
        db     = NULL;
        dbSize = 0;
    }
}

short
Measurement::Controller::IdentifyFlow(fingerprint* fp) {
    float* kullback_leibler_div = new float[dbSize]();
    memset(kullback_leibler_div, 0, (dbSize*sizeof(float)));

    // optimisation: when the program is started, the size of the attributes
    // will never change, so we have to call the method size only once
    if (attributesSize == 0)
        attributesSize = attributes.size();
    
    for (unsigned short i = 0; i < dbSize; ++i) {

        if (fp->protocol != db[i].protocol)
            continue;

        // if (spid->bDebug)
        //     cout << db[i].name << endl;

        for (unsigned short x = 0; x < attributesSize; ++x) {
            Attributes* attr = attributes.at(x);
            
            float kl_div = 0.0;
            for (unsigned short y = 0; y < attr->size; ++y) {
                float* db_pro = attr->getFingerprintProEntry(&db[i]);
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
    
    for (unsigned short i = 0; i < dbSize; ++i) {
        if (fp->protocol != db[i].protocol)
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

void
Measurement::Controller::PrintFingerprintDb(fingerprint* fp) {
    unsigned int array_size;

    if (spid->bLearnModus or spid->pFingerprintFile)
        array_size = dbSize;
    else
        array_size = sizeof(*fp) / sizeof(struct fingerprint);
    
    for (unsigned short i = 0; i < array_size; ++i) {
        cout << fp[i].name << " trained with " << fp[i].flowsCnt
             << " flows" << endl;
    }
}


fingerprint*
Measurement::Controller::ReadFingerprintDb(char* file) {
    struct stat file_info;

    // find out what size the file have, to calculate the memory size we need  
    // to reserve
    if (stat(file, &file_info) == 0) 
        dbSize = static_cast<u_int>(file_info.st_size /
                                    (sizeof(struct fingerprint)));
    else {
        fprintf(stderr, "Error: Couldn't open '%s' for reading\n", file);
        exit(EXIT_FAILURE);
    }

    fingerprint* fp = new fingerprint[dbSize];
    ifstream in(file, ios::in | ios::binary);

    if (!in) {
        fprintf(stderr, "Error: Couldn't open '%s' for reading\n", file);
        exit(EXIT_FAILURE);
    }

    in.read((char*) fp, (dbSize * sizeof(struct fingerprint)));
    in.close();

    return fp;
}

void
Measurement::Controller::WriteFingerprintDb(char* file, fingerprint* fp) {
    unsigned int array_size;

    // If we learn a new protocol the size of the array has changed, so we
    // need to calculate new
    if (spid->pFingerprintFile and spid->bLearnModus)
        array_size = sizeof(*fp) * dbSize;
    else
        array_size = sizeof(*fp);    
    
    ofstream out(file, ios::out | ios::binary);
    
    if (!out) {
        fprintf(stderr, "Error: Couldn't open '%s' for writing\n", file);
        exit(EXIT_FAILURE);
    }

    out.write((char*) fp, array_size);
    out.close();
}

Measurement::Controller::~Controller( ) {
    if (spid->bLearnModus) {
        WriteFingerprintDb(spid->pLearnFile, db);
        PrintFingerprintDb(db);
    }
    
    delete [] db;
}
