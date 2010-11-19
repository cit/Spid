// ---------------------------------------------------------------------------
// FingerprintDB.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef FINGERPRINTDB_H
#define FINGERPRINTDB_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cstring>
#include <cstdlib>

#include "structs.h"
#include "Spid.h"

class FingerprintDB {

private:
    Spid* spid;
    
public:
    fingerprint* fp;
    int size;
    
    explicit FingerprintDB();

    // This method adds a new fingerprint to the reference database. 
    void Add(fingerprint& newfp);
    
    // It writes the complete fingerprint database to a binary file. This
    // is necessary if a flow will be learned.
    void SerializeToFile(char* filename);

    // It reads the complete fingerprint database. This database is needed
    // for identification
    void DeserializeFromFile(char* filename);

    // This method prints some information that contains in the fingerprint
    // database. 
    void PrintDB();
};

#endif // FINGERPRINTDB_H
