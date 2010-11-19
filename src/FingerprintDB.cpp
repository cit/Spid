// ---------------------------------------------------------------------------
// FingerprintDB.cpp
// 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
extern "C" {
#include <sys/stat.h>
}

#include "FingerprintDB.h"

using namespace std;

FingerprintDB::FingerprintDB() {
    spid = Spid::getInstance();
    fp   = NULL;
    size = 0;
}

void FingerprintDB::Add(fingerprint& newfp) {
    // create a new temporary array
    fingerprint* tmp = new fingerprint[size + 1]();
    memset(tmp, 0, (size*sizeof(tmp)));
    
    for (unsigned short i = 0; i < size; ++i) 
        tmp[i] = fp[i];
    delete [] fp;
    
    fp = tmp;
    fp[size] = newfp;

    size++;
}

void FingerprintDB::PrintDB() {
    unsigned int array_size;

    if (spid->bLearnModus or spid->pFingerprintFile)
        array_size = size;
    else
        array_size = sizeof(*fp) / sizeof(struct fingerprint);
    
    for (unsigned short i = 0; i < array_size; ++i) {
        cout << fp[i].name << " trained with " << fp[i].flowsCnt
             << " flows" << endl;
    }
}

void FingerprintDB::DeserializeFromFile(char* file) {
    struct stat file_info;

    // find out what size the file have, to calculate the memory size we need  
    // to reserve
    if (stat(file, &file_info) == 0) 
        size = static_cast<u_int>(file_info.st_size /
                                  (sizeof(struct fingerprint)));
    else {
        cerr << "Error: Couldn't open '" << file << "' for reading" << endl;
        exit(EXIT_FAILURE);
    }

    fp = new fingerprint[size];
    ifstream in(file, ios::in | ios::binary);

    if (!in) {
        cerr << "Error: Couldn't open '" << file << "' for reading" << endl;
        exit(EXIT_FAILURE);
    }

    in.read((char*) fp, (size * sizeof(struct fingerprint)));
    in.close();
}

void FingerprintDB::SerializeToFile(char* file) {
    unsigned int array_size;

    // If we learn a new protocol the size of the array has changed, so we
    // need to calculate it new
    if (spid->pFingerprintFile and spid->bLearnModus)
        array_size = sizeof(*fp) * this->size;
    else
        array_size = sizeof(*fp);    
    
    ofstream out(file, ios::out | ios::binary);
    
    if (!out) {
        cerr << "Error: Couldn't open '" << file << "' for writing" << endl;
        exit(EXIT_FAILURE);
    }

    out.write((char*) fp, array_size);
    out.close();
}
