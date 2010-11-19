template <class T> char* InspectFlow(T* flow) {    
    fingerprint* fp = new fingerprint;
    unsigned short arraySize = 0;

    flow->bInspected = true;

    fp->flowsCnt = 1;
    if (flow->packets.at(0)->protocol == TCP)
        fp->protocol = TCP;
    else
        fp->protocol = UDP;

    // copy the protocolname to the fingerprint structure
    if (spid->bLearnModus and spid->pProtocolName)
        strncpy(fp->name, spid->pProtocolName, 256);

    // measures the frequency of every byte in the payload in each direction
    attributes.push_back(new ByteFrequency(flow));
    arraySize = sizeof(fp->byteFreqCnt) / sizeof(fp->byteFreqCnt[0]);
    attributes.back()->setFingerprintPtr(fp->byteFreqCnt,
                                         fp->byteFreqPro,
                                         arraySize);
    attributes.push_back(new ByteFrequencyOtherDirection(flow));
    arraySize = sizeof(fp->byteFreqOtherDirectionCnt) /
        sizeof(fp->byteFreqOtherDirectionCnt[0]);
    attributes.back()->setFingerprintPtr(fp->byteFreqOtherDirectionCnt,
                                         fp->byteFreqOtherDirectionPro,
                                         arraySize);
    attributes.push_back(new First32BytesFrequency(flow));
    arraySize = sizeof(fp->first32bytesFreqCnt) /
        sizeof(fp->first32bytesFreqCnt[0]);
    attributes.back()->setFingerprintPtr(fp->first32bytesFreqCnt,
                                         fp->first32bytesFreqPro,
                                         arraySize);
        
    //measure the first non empty payload size
    attributes.push_back(new FirstNonEmptyPayloadSize(flow->packets.at(0)));
    arraySize = sizeof(fp->firstNonEmptyPayloadSizeCnt) /
        sizeof(fp->firstNonEmptyPayloadSizeCnt[0]);
    attributes.back()->setFingerprintPtr(fp->firstNonEmptyPayloadSizeCnt,
                                         fp->firstNonEmptyPayloadSizePro,
                                         arraySize);

    // measure the payload size of each direction
    attributes.push_back(new DirectionBytesMeter(flow));
    arraySize = sizeof(fp->directionBytesMeterCnt) /
        sizeof(fp->directionBytesMeterCnt[0]);
    attributes.back()->setFingerprintPtr(fp->directionBytesMeterCnt,
                                         fp->directionBytesMeterPro,
                                         arraySize);

    // measure how many direction changes are in one flow
    attributes.push_back(new DirectionChanges(flow));
    arraySize = sizeof(fp->directionChangesCnt) /
        sizeof(fp->directionChangesCnt[0]); 
    attributes.back()->setFingerprintPtr(fp->directionChangesCnt,
                                         fp->directionChangesPro,
                                         arraySize);

    // TODO
    attributes.push_back(new BytePairsReocurring(flow));
    arraySize = sizeof(fp->bytePairsReocurringCnt) /
        sizeof(fp->bytePairsReocurringCnt[0]); 
    attributes.back()->setFingerprintPtr(fp->bytePairsReocurringCnt,
                                         fp->bytePairsReocurringPro,
                                         arraySize);

    // TODO
    // attributes.push_back(new ByteDistance(flow));
    // arraySize = sizeof(fp->byteDistanceCnt) / sizeof(fp->byteDistanceCnt[0]); 
    // attributes.back()->setFingerprintPtr(fp->byteDistanceCnt,
    //                                      fp->byteDistancePro,
    //                                      arraySize);

    // TODO
    attributes.push_back(new First4BytesCrossSum(flow));
    arraySize = sizeof(fp->first4bytescrosssumCnt) /
        sizeof(fp->first4bytescrosssumCnt[0]); 
    attributes.back()->setFingerprintPtr(fp->first4bytescrosssumCnt,
                                         fp->first4bytescrosssumPro,
                                         arraySize);

    // measures the entropy of the first packet in each direction.
    attributes.push_back(new Entropy(fp));
    arraySize = sizeof(fp->entropyCnt) / sizeof(fp->entropyCnt[0]); 
    attributes.back()->setFingerprintPtr(fp->entropyCnt,
                                         fp->entropyPro,
                                         arraySize);

    // TODO
    attributes.push_back(new FirstPacketPerDirectionNibbles(flow));
    arraySize = sizeof(fp->FirstPacketNibblesCnt) /
        sizeof(fp->FirstPacketNibblesCnt[0]); 
    attributes.back()->setFingerprintPtr(fp->FirstPacketNibblesCnt,
                                         fp->FirstPacketNibblesPro,
                                         arraySize);

    attributes.push_back(new ActionReactionFirst3ByteHashMeter(flow));
    arraySize = sizeof(fp->actionReactionFirst3bytesCnt) /
        sizeof(fp->actionReactionFirst3bytesCnt[0]);
    attributes.back()->setFingerprintPtr(fp->actionReactionFirst3bytesCnt,
                                         fp->actionReactionFirst3bytesPro,
                                         arraySize);

    attributes.push_back(new FirstBitPositionsMeter(flow));
    arraySize = sizeof(fp->firstBitPositionsMeterCnt) /
        sizeof(fp->firstBitPositionsMeterCnt[0]);
    attributes.back()->setFingerprintPtr(fp->firstBitPositionsMeterCnt,
                                         fp->firstBitPositionsMeterPro,
                                         arraySize);

    // measures the equality of the first 8 bytes in all packets
    attributes.push_back(new AllPacketsFirst8BytesEqualityMeter(flow));
    arraySize = sizeof(fp->allPacketsFirst8BytesCnt) /
        sizeof(fp->allPacketsFirst8BytesCnt[0]);
    attributes.back()->setFingerprintPtr(fp->allPacketsFirst8BytesCnt,
                                         fp->allPacketsFirst8BytesPro,
                                         arraySize);

    attributes.push_back(new UnicodeFrequency(flow));
    arraySize = sizeof(fp->unicodeFreqCnt) /
        sizeof(fp->unicodeFreqCnt[0]);
    attributes.back()->setFingerprintPtr(fp->unicodeFreqCnt,
                                         fp->unicodeFreqPro,
                                         arraySize);

    short identfiedProtocol = -1;

    // if only the fingerprintfile is defined identify the flow
    if (spid->pFingerprintFile and not spid->bLearnModus) {
        identfiedProtocol = IdentifyFlow(fp);
    }

    if (spid->bLearnModus) {
        bool b_found = false;

        for (unsigned short i = 0; i < refDB->size; ++i) {
            if (strcmp(refDB->fp[i].name, fp->name) == 0) {
                b_found = true;

                bool learn = true;
                if (spid->kMaxTrainedFlows > 0) {
                    if (refDB->fp[i].flowsCnt >= spid->kMaxTrainedFlows)
                        learn = false;
                }

                if (learn) {
                    refDB->fp[i].flowsCnt++;

                    for (unsigned short y = 0; y < attributes.size(); ++y) {
                        Attributes* attr = attributes.at(y);
                        attr->ImproveApproximation(&refDB->fp[i]);
                    }
                    break;
                }
                
            }
        }

        // if protocol where not found resize the array and save the database
        // again
        if (not b_found)
            refDB->Add(*fp);
    }

    delete fp;
    for (iter = attributes.begin(); iter != attributes.end(); ++iter)
        delete *iter;
    attributes.clear();

    return (identfiedProtocol != -1) ? refDB->fp[identfiedProtocol].name : NULL;
}
