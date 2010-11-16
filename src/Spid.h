// ---------------------------------------------------------------------------
// Spid.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef SPID_H
#define SPID_H

#include <list>
#include <string>

extern "C" {
#include <pcap/pcap.h>
}

#include "IObserver.h"
#include "structs.h"

class Spid {
    // In this list, all classes were saved, which want to be notified,
    // if there is a identifed flow.
    std::list<IObserver*> _observers;
    
    typedef std::list<IObserver*>::iterator _iterator;

private:
    static Spid* instance;
    pcap_t* pPcapHandler;
    
    // Constructor of this class
    Spid();
    Spid(const Spid& spid);

public:
    static const float          kThreshold;
    static const unsigned short kMaxTrainedFlows;
    static const unsigned short kNumberOfPacketsToAnalyze;
    static const unsigned int   kTimeout;
    
    char* pPcapFilename;          // filename for the pcap-file
    char* pFingerprintFile;       // pointer to the fingerprint file
    char* pInterface;             // pointer to the network device
    char* pLearnFile;             // pointer to the learn file
    char* pProtocolName;          // pointer to the name of the protocol

    bool  bPromiscuousMode;       // promiscous mode
    bool  bLiveModus;             // default mode is live capturing
    bool  bLearnModus;
    bool  bDebug;

    static Spid* getInstance();
    
    void addObserver(IObserver& ref);
    void removeObserver(IObserver& ref);
    void notifyObservers(fiveTupel flow, char* protocol);

    void setLearnModus(char* filename);
    void setPcapFile(char* filename);
    void setPromiscuousMode(bool value);
    void setInterface(char* interface);
    void setFingerprintFile(char* filename);
    void setProtocolName(char* name);
    
    void startIdentifcation();
    static void processPacket(u_char* pArg, const struct pcap_pkthdr* pHeader,
                       const u_char* pPacket);

    // Deconstructor of this class
    void Destroy();
};

#endif // SPID_H
