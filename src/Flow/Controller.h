#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <vector>

#include "../Spid.h"
#include "../Ip/V4.h"
#include "../structs.h"
#include "../Measurement/Controller.h"

#include "TcpFlow.h"
#include "UdpFlow.h"

using namespace std;

namespace Flow {

    class Controller {
    private:
        // private variables
        vector<TcpFlow*>           tcpFlows;
        //vector<TcpFlow*>::iterator tflow;
        vector<UdpFlow*>           udpFlows;
        vector<UdpFlow*>::iterator uflow;
        Measurement::Controller*   pm;
        Spid*                      spid;
        int                        tcpFlowsSize;

        // private methods
        void DeleteTcpFlow(Flow::TcpFlow* tflow, unsigned int i);

    public:
        // public variables

        // public mehtods
        explicit Controller();
        void     AddPacket(Ip::V4* pIpv4);

        ~Controller();
    };
}

#endif // CONTROLLER_H
