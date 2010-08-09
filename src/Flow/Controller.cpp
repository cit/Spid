// ---------------------------------------------------------------------------
// Controller.cpp
// This class handles all the flows.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>

extern "C" {
#include <time.h>
}

#include "Controller.h"

#include "../enums.h"

using ::Spid;

Flow::Controller::Controller() {
    spid = Spid::getInstance();
    pm   = new Measurement::Controller();
}

void Flow::Controller::AddPacket(Ip::V4* pIpv4) {
    bool b_found           = false;
    bool b_direction_found = false;

    fiveTupel azub;
    azub.srcIp = pIpv4->srcIp;
    azub.dstIp = pIpv4->dstIp;

    fiveTupel bzua;
    bzua.srcIp = pIpv4->dstIp;
    bzua.dstIp = pIpv4->srcIp;

    switch (pIpv4->protocol) {
    case UDP:
        azub.protocol = bzua.protocol = UDP;
        azub.srcPort  = pIpv4->pUdp->srcPort;
        azub.dstPort  = pIpv4->pUdp->dstPort;

        bzua.srcPort  = pIpv4->pUdp->dstPort;
        bzua.dstPort  = pIpv4->pUdp->srcPort;

        //for (uflow = udpFlows.begin(); uflow != udpFlows.end(); ++uflow) {
        for (unsigned int i = 0; i < udpFlows.size(); ++i) {
            Flow::UdpFlow *uflow = udpFlows.at(i);

            // if the time between the last packet from the tflow and the next
            // packet cross the timeout then delete it.
            if ((pIpv4->timeStamp.tv_sec - uflow->lastPacketArrived)
                >= spid->kTimeout) {
                udpFlows.erase(udpFlows.begin() + i);    
                delete uflow;
                continue;
            }

            // check if a udp-flow exist for that packet and check from which
            // direction it comes from. 
            if (uflow->IsEqual(&azub)) {
                b_direction_found = true;
                pIpv4->direction = ORIGINATOR_TO_RESPONDER;
            }
            else if (uflow->IsEqual(&bzua)) {
                b_direction_found = true;
                pIpv4->direction = RESPONDER_TO_ORIGINATOR;
            }

            if (b_direction_found) {
                b_found = true;

                uflow->AddPacket(pIpv4);

                if (uflow->packetCnt == spid->kNumberOfPacketsToAnalyze
                    and uflow->bInspected == false) {

                    char* proto = pm->InspectFlow(uflow);
                    
                    // notify all observers about the result
                    if (!spid->bLearnModus) {

                        if (pIpv4->direction == ORIGINATOR_TO_RESPONDER)
                            spid->notifyObservers(azub, proto);
                        else
                            spid->notifyObservers(bzua, proto);
                    }

                    // Since udp has no states, it's not possible to delete
                    // the whole flow, because it would repeat the identifaction
                    // on the the same flow as before. To safe memory we only
                    // delete all packets
                    uflow->DeletePackets();
                }

                break;
            }
        }

        if (not b_found) {
            UdpFlow* udpFlow = new UdpFlow();
            udpFlow->AddPacket(pIpv4);
            udpFlows.push_back(udpFlow);
        }

        break;

    case TCP:
        azub.protocol = bzua.protocol = TCP;
        azub.srcPort  = pIpv4->pTcp->srcPort;
        azub.dstPort  = pIpv4->pTcp->dstPort;

        bzua.srcPort  = pIpv4->pTcp->dstPort;
        bzua.dstPort  = pIpv4->pTcp->srcPort;


        //for (tflow = tcpFlows.begin(); tflow < tcpFlows.end(); ++tflow) {
        for (unsigned int i = 0; i < tcpFlows.size(); ++i) {
            Flow::TcpFlow *tflow = tcpFlows.at(i);

            // if the time between the last packet from the tflow and the next
            // packet cross the timeout then delete it.
            if ((pIpv4->timeStamp.tv_sec - tflow->lastPacketArrived)
                >= spid->kTimeout) {
                DeleteTcpFlow(tflow, i);
                continue;
            }

            // check if a tcp-flow exist for that packet and check from which
            // direction it comes from. 
            if (tflow->IsEqual(&azub)) {
                b_direction_found = true;
                pIpv4->direction = ORIGINATOR_TO_RESPONDER;
            }
            else if (tflow->IsEqual(&bzua)) {
                b_direction_found = true;
                pIpv4->direction = RESPONDER_TO_ORIGINATOR;
            }

            if (b_direction_found) {
                
                if (tflow->state == CLOSED) {
                    DeleteTcpFlow(tflow, i);
                    continue;
                }
                
                b_found = true;
                
                // analyse packet if it is relevant
                tflow->AddPacket(pIpv4);

                // check when the number of packets to analyse is arrived and
                // if so then try to identify it
                if (tflow->packetCnt == spid->kNumberOfPacketsToAnalyze
                    and tflow->bInspected == false) {

                    char* proto = pm->InspectFlow(tflow);

                    // notify all observers about the result
                    if (!spid->bLearnModus) {

                        if (pIpv4->direction == ORIGINATOR_TO_RESPONDER)
                            spid->notifyObservers(azub, proto);
                        else
                            spid->notifyObservers(bzua, proto);
                    }
                    
                    // delete the flow, after the identifcation,
                    DeleteTcpFlow(tflow, i);
                }

                break;
            }
        }

        if (not b_found)  {
            TcpFlow* tcpFlow = new TcpFlow();
            tcpFlow->AddPacket(pIpv4);
            tcpFlows.push_back(tcpFlow);
        }

        break;
    }

}

void Flow::Controller::DeleteTcpFlow(Flow::TcpFlow* tflow, unsigned int i) {
    tcpFlows.erase(tcpFlows.begin() + i);
    delete tflow;
}

Flow::Controller::~Controller() {
    vector<TcpFlow*>::iterator tcp;
    for (tcp = tcpFlows.begin(); tcp != tcpFlows.end(); ++tcp)
        delete *tcp;
    tcpFlows.clear();

    vector<UdpFlow*>::iterator udp;
    for (udp = udpFlows.begin(); udp != udpFlows.end(); ++udp)
        delete *udp;
    udpFlows.clear();

    delete pm;
}
