// ---------------------------------------------------------------------------
// DirectionBytesMeter.cpp
// This class gets a tcp or udp flow and counts the amount of data in each
// direction and calculates the probability.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> DirectionBytesMeter(T* flow) {
    size          = 2;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(int)));

    // 0 = Originator -> Responder
    // 1 = Responder  -> Originator

    for (unsigned char i = 0; i < all_packets; ++i) {
        if (flow->packets.at(i)->direction == ORIGINATOR_TO_RESPONDER) {
            if (flow->packets.at(i)->protocol == TCP)
                count[0] += flow->packets.at(i)->pTcp->payloadSize;
            else
                count[0] += flow->packets.at(i)->pUdp->payloadSize;
        }
        else {
            if (flow->packets.at(i)->protocol == TCP)
                count[1] += flow->packets.at(i)->pTcp->payloadSize;
            else
                count[1] += flow->packets.at(i)->pUdp->payloadSize;
        }
    }

    total_size = count[0] + count[1];
    probabilities[0] = count[0] / static_cast<float>(total_size);
    probabilities[1] = count[1] / static_cast<float>(total_size);
}
