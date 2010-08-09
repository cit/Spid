// ---------------------------------------------------------------------------
// AllPacketsFirst8BytesEqualityMeter.tcc
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> AllPacketsFirst8BytesEqualityMeter(T* flow) {
    size          = 8;
    total_size    = all_packets;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    for (unsigned char i = 0; i < size; ++i) {
        // the hightest number of a crosssum with 265 (1 Byte) is 199 = 19
        unsigned short maxCrossSum = total_size * 19;
        u_int* cnt = new u_int[maxCrossSum]();
        memset(cnt, 0, (maxCrossSum*sizeof(u_int)));
        
        for (unsigned char y = 0; y < total_size; ++y) {
            if (flow->packets.at(0)->protocol == TCP) {
                p_payload    = flow->packets.at(y)->pTcp->payload + i;
                payload_size = flow->packets.at(y)->pTcp->payloadSize;
            }
            else {
                p_payload    = flow->packets.at(y)->pUdp->payload + i;
                payload_size = flow->packets.at(y)->pUdp->payloadSize;
            }

            if (payload_size < 8)
                continue;
            
            unsigned char byte = static_cast<int>(*p_payload);
            unsigned char rest     = 0;
            unsigned char checksum = 0;
            do {
                rest = byte%10;
                byte = byte/10;
                checksum += rest;
            } while (byte > 0);
            
            cnt[checksum]++;
        }

        unsigned short tmp = 0;
        for (unsigned short x = 0; x < maxCrossSum; ++x) {
            if (cnt[x] > tmp)
                tmp = cnt[x];
        }

        count[i] = tmp;
        delete [] cnt;
    }

    for (unsigned char i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
}
