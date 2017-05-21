// ---------------------------------------------------------------------------
// FingerprintDB.cpp
//
// This class handles the connection to the reference database. Every flow will
// be compared with this database in case of identification. This class provides
// methods to load and save a database to a file.
//
// Author: Florian Adamsky <fa-spid@haktar.org>
// ---------------------------------------------------------------------------
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
    ifstream in(file, ios::in);

    if (!in) {
        cerr << "Error: Couldn't open '" << file << "' for reading" << endl;
        exit(EXIT_FAILURE);
    }

    // get length of file:
    in.seekg (0, std::ios::end);
    long length = in.tellg();
    in.seekg (0, std::ios::beg);

    // allocate memory:
    char *buffer = new char[length];

    // read data as a block:
    in.read (buffer,length);

    // create string stream of memory contents
    string str(buffer);

    // delete temporary buffer
    delete [] buffer;

    // close filestream
    in.close();

    // the first integer in the file is the size of the database
    size = trim<int>(str);

    // allocate memory for the database
    fp = new fingerprint[size];

    for (int i = 0; i < size; ++i) {
        strncpy(fp[i].name, str.substr(0, str.find_first_of(";")).c_str(), 256);
        str.erase(0, str.find_first_of(";") + 1);

        fp[i].flowsCnt = trim<int>(str);
        fp[i].protocol = trim<int>(str);

#define X(type, name, size)                     \
        for(int y=0; y < size; ++y) {           \
            fp[i].name[y] = trim<type>(str);    \
        }
        X_FIELDS
#undef X
            }
    this->PrintDB();
}

void FingerprintDB::SerializeToFile(char* file) {
    unsigned int array_size;

    // If we learn a new protocol the size of the array has changed, so we
    // need to calculate it new
    if (spid->pFingerprintFile and spid->bLearnModus)
        array_size = sizeof(*fp) * this->size;
    else
        array_size = sizeof(*fp);

        // Writing
    ofstream out(file, ios::out);

    if (!out) {
        cerr << "Error: Couldn't open '" << file << "' for writing" << endl;
        exit(EXIT_FAILURE);
    }

    // the first integer is the size of the database
    out << size << ';';

    for (int i = 0; i < size; ++i) {
        out << fp[i].name << ";" << fp[i].flowsCnt << ";"
            << fp[i].protocol << ";";

#define X(type, name, size)                     \
        for(int y=0; y < size; ++y) {           \
            out << fp[i].name[y] << ";";        \
        }
        X_FIELDS
#undef X

    }
    out.close();
}
