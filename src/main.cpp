#include <iostream>
#include <cstdlib>

extern "C" {
#include <getopt.h>
}

#include "Spid.h"
#include "IObserver.h"
#include "structs.h"

using namespace std;

class Qosilan : public IObserver {
public:
    virtual void handleEvent(fiveTupel flow, char* protocol) {
        cout << ((flow.protocol == 0) ?  "TCP " : "UDP ")
             << inet_ntoa(flow.srcIp) << ":" << flow.srcPort << " -> " 
             << inet_ntoa(flow.dstIp) << ":" << flow.dstPort << endl;
        
        if (protocol != NULL)
            cout << "I guess it is " << protocol << endl;
        else
            cout << "I guess it is unknown" << endl;
    }
};

void usage(char* pProgName) {
    fprintf(stderr,
            "Usage: %s options\n"
            "  -p, --promiscous              enables promiscous mode\n"
            "  -r, --read-pcap <pcap_file>   reads an pcap file in\n"
            "  -i, --interface <interface>   sets the interface to listen on\n\n"

            "  -l, --learn <db_file>         write new statistics to the file\n"
            "  -n, --name <name>             name of the protocol or category\n"
            "  -f, --fingerprintdb <db_file> database to identifiy\n\n"

            "  -m, --max <number>            maximal numbers of trained flows\n"

            "  -d, --debug                   print additionl debug messages\n"
            "  -h, --help                    print this help page\n"
            "  -v, --version                 print version number\n\n",
            pProgName);
}

int main(int argc, char *argv[]) {
    Qosilan qosilan;
    Spid*   spid;
    
    spid = Spid::getInstance();

    static const struct option long_options[] = {
        { "read-pcap",     required_argument, 0, 'r'  },
        { "interface",     required_argument, 0, 'i'  },
        { "learn",         required_argument, 0, 'l', },
        { "name",          required_argument, 0, 'n', },
        { "fingerprintdb", required_argument, 0, 'f', },
        { "max",           required_argument, 0, 'm', },
        { "promiscous",    no_argument,       0, 'p'  },
        { "debug",         no_argument,       0, 'd'  },
        { "help",          no_argument,       0, 'h'  },
        { "version",       no_argument,       0, 'v'  },
        { 0,               0,                 0,  0   },
    };

    while (optind < argc) {
        int index  = -1;
        int result = getopt_long(argc, argv, "hdvpl:n:r:i:f:m:",
                                 long_options, &index);
        struct option * opt = NULL;
        
        if (result == -1)
            break; // end of list
        
        switch (result) {
        case 'l':
            spid->setLearnModus(optarg);
            break;
        case 'n':
            spid->setProtocolName(optarg);
            break;
        case 'f':
            spid->setFingerprintFile(optarg);
            break;
        case 'r':
            spid->setPcapFile(optarg);
            break;
        case 'i':
            spid->setInterface(optarg);
            break;
        case 'p':
            spid->setPromiscuousMode(true);
            break;
        case 'm':
            //cfg->fThreshold = static_cast<int>(atol(optarg));
            // cfg->MaxTrainedFlows = static_cast<int>(atol(optarg));
            // cfg->NumberOfPacketsToAnalyze = static_cast<int>(atol(optarg));
            break;
        case 'd':
            spid->bDebug = true;
            break;
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        case 'v':
            //printf("%s\n", VERSION);
            exit(EXIT_SUCCESS);
        case 0:
            opt = (struct option *)&(long_options[index]);
            printf("'%s' was specified.",
                   opt->name);
            if (opt->has_arg == required_argument)
                printf("Arg: <%s>", optarg);
            printf("\n");
            break;
        default:
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    spid->addObserver(qosilan);
    spid->startIdentifcation();
    spid->removeObserver(qosilan);
    
    spid->Destroy();
    
    return 0;
}
