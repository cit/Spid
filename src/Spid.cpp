#include <iostream>
#include <cstdlib>

#include "Spid.h"
#include "Flow/Controller.h"
#include "Ip/V4.h"
#include "constants.h"

Spid* Spid::instance = NULL;

const float          Spid::kThreshold                = 13.0;
const unsigned short Spid::kMaxTrainedFlows          = 30;
const unsigned short Spid::kNumberOfPacketsToAnalyze = 20;
const unsigned int   Spid::kTimeout                  = 64000; // 64 seconds

Spid::Spid() {
    pPcapFilename    = NULL;    // filename for the pcap-file
    pInterface       = NULL;    // pointer to the network device
    pLearnFile       = NULL;    // pointer to the new reference database file
    pFingerprintFile = NULL;    // pointer to the reference database file
    pProtocolName    = NULL;    // the name of the protocol that will be learned
    pPcapHandler     = NULL;    // network interface handler

    bPromiscuousMode = false;   // promiscous mode
    bDebug           = false;   // enable debug mode
    bLiveModus       = true;    // default mode is live capturing
    bLearnModus      = false;   // enable learn modus 
}

Spid* Spid::getInstance() {
    if (!instance)
        instance = new Spid();

    return instance;
}

void Spid::notifyObservers(fiveTupel flow, char* protocol){
    for(_iterator it = _observers.begin(); it != _observers.end(); ++it)
        (*it)->handleEvent(flow, protocol);
}

void Spid::addObserver(IObserver& ref){
    _observers.push_back(&ref);
}
    
void Spid::removeObserver(IObserver& ref){
    _observers.remove(&ref);
}

void Spid::setLearnModus(char* filename) {
    bLearnModus = true;
    pLearnFile  = filename;
}

void Spid::setInterface(char* interface) {
    pInterface = interface;
}

void Spid::setPromiscuousMode(bool value) {
    bPromiscuousMode = value;
}

void Spid::setPcapFile(char* filename) {
    bLiveModus    = false;
    pPcapFilename = filename;
}

void Spid::setFingerprintFile(char* filename) {
    pFingerprintFile = filename;
}

void Spid::setProtocolName(char* name) {
    pProtocolName = name;
}
    
void Spid::startIdentifcation(){
    char                errbuf[PCAP_ERRBUF_SIZE]; // error buffer for pcap
    Flow::Controller*   flowController = new Flow::Controller();
    struct bpf_program  filter;
    
    // live capturing modus
    if (bLiveModus) {
        if (pInterface == NULL)
            if ((pInterface = pcap_lookupdev(errbuf)) == NULL) {
                cerr << "Error: " << errbuf << endl;
                exit(EXIT_FAILURE);
            }

        // open network device for live packet capturing
        if ((pPcapHandler = pcap_open_live(pInterface, MAX_BYTES_2_CAPTURE,
                                           bPromiscuousMode, 1000, errbuf))
            == NULL) {
            cerr << "Can't open device: " << errbuf << endl;
            exit(EXIT_FAILURE);
        }
    }

    // read a pcap-file in
    else {
        cout << "file: " << pPcapFilename << endl;
         if ((pPcapHandler = pcap_open_offline(pPcapFilename, errbuf)) == NULL) {
             cerr << "Error: " << errbuf << endl;
             exit(EXIT_FAILURE);
         }
     }

    // compiles the filter expression into a BPF filter program.
    // ip and (tcp or udp) filters only ip version 4 packets with tcp or udp
    if (pcap_compile(pPcapHandler, &filter,
                     "ip and (tcp or udp)", 1, 0) == -1) {
        cerr << "Error bpf: " << pcap_geterr(pPcapHandler) << endl;
        exit(EXIT_FAILURE);
    }

    // load the filter program into the packet capture device.
    if (pcap_setfilter(pPcapHandler, &filter) == -1) {
        cerr << "Error filter: " << pcap_geterr(pPcapHandler) << endl;
        exit(EXIT_FAILURE);
    }

    // free up allocated memory pointed to by a bpf_program
    pcap_freecode(&filter);

    // entering the capturing loop
    pcap_loop(pPcapHandler, -1, processPacket,
              reinterpret_cast<u_char*>(flowController)); //== -1)
    
    // clean the whole mess up
    pcap_close(pPcapHandler);
    delete flowController;
}

void Spid::processPacket(u_char* pArg, const struct pcap_pkthdr* pHeader,
                         const u_char* pPacket) {
    Flow::Controller* pFlowController = (Flow::Controller*) pArg;
    Ip::V4* pIpv4 = NULL;

    try {
        pIpv4 = new Ip::V4(pPacket, pHeader);
    }
    catch(Ip::Error& e) {
        cerr << e.error << endl;
    }

    if(pIpv4 != NULL)
        pFlowController->AddPacket(pIpv4);
}

void Spid::Destroy() {
    for(_iterator it = _observers.begin(); it != _observers.end(); ++it)
        delete *it;
    _observers.clear();

    if (instance) {
        delete instance;
        instance = NULL;
    }

}
