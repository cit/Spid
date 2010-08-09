// ---------------------------------------------------------------------------
// First4BytesCrossSum.tcc
// This class gets a tcp or udp flow and tooks the first 4 bytes and calculates
// the cross-sum
// 
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> First4BytesCrossSum(T* flow) {
    size          = 76;                // By 1 Byte the highest crosssum can
                                       // be 199 = 19   =>   19 * 4 = 76
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    for (unsigned char i = 0; i < 2; ++i) {
        if (flow->packets.at(0)->protocol == TCP) {
            p_payload    = flow->packets.at(i)->pTcp->payload;
            payload_size = flow->packets.at(i)->pTcp->payloadSize;
        }
        else {
            p_payload    = flow->packets.at(i)->pUdp->payload;
            payload_size = flow->packets.at(i)->pUdp->payloadSize;
        }
        
        if (payload_size > 4)
            payload_size = 4;
        
        total_size = payload_size;
        unsigned char crosssum = 0;
        for (unsigned char y = 0; y < payload_size; ++y) {
            unsigned char byte = static_cast<u_int>(*p_payload);
            unsigned char rest = 0;
            do {
                rest = byte%10;
                byte = byte/10;
                crosssum += rest;
            } while (byte > 0);
            p_payload++;
        }
        count[crosssum]++;
    }

    for (unsigned char i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
}
