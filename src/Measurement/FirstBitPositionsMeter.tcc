// ---------------------------------------------------------------------------
// FirstBitPositionMeter.tcc
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> FirstBitPositionsMeter(T* flow) {
    size          = 64;
    count         = new int[size]();
    probabilities = new float[size]();
    total_size    = size;

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    const unsigned char byteCnt = 4;

    for (unsigned char i = 0; i < all_packets; ++i) {
        if (flow->packets.at(0)->protocol == TCP) {
            p_payload    = flow->packets.at(i)->pTcp->payload;
            payload_size = flow->packets.at(i)->pTcp->payloadSize;
        }
        else {
            p_payload    = flow->packets.at(i)->pUdp->payload;
            payload_size = flow->packets.at(i)->pUdp->payloadSize;
        }

        if (payload_size > byteCnt)
            payload_size = byteCnt;

        for (unsigned char y = 0; y < payload_size; ++y) {

            unsigned char ret = 0;
            // covert byte to single bits
            for (unsigned char x = 0; x < 8; ++x ) {
                ret = (ret << 1) | (*p_payload & 1);
                *p_payload >>= 1;
            }

            // ... TODO
            for (unsigned char x = 0; x < 8; ++x) {
                unsigned char offset = (y*8)+x;
                unsigned char index  = offset*2 + (!!(ret&1));
                count[index]++;
                ret >>= 1;
            }

        }
        
    }

    for (unsigned char i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
    
}
