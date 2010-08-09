// ---------------------------------------------------------------------------
// ByteFrequencyOtherDirection.tcc
// This class gets a tcp-flow and counts every byte in the payload of a
// packet and calculates the probability.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> ByteFrequencyOtherDirection(T* flow) {
    size          = 256;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    if (flow->packets.at(0)->protocol == TCP) {
        unsigned short direction = 0;
        for (unsigned short i = 0; i < all_packets; ++i) {
            if (flow->packets.at(i)->direction == RESPONDER_TO_ORIGINATOR)
                direction = i;
        }
        
        p_payload    = flow->packets.at(direction)->pTcp->payload;
        payload_size = flow->packets.at(direction)->pTcp->payloadSize;

        // if (payload_size > 128)
        //     payload_size = 128;

        total_size = payload_size;
        
        for (unsigned short y = 0; y < payload_size; ++y) {
            u_int byte = static_cast<u_int>(*p_payload);
            p_payload++;
            
            count[byte]++;
        }
        
        for (unsigned short i = 0; i < size; ++i)
            probabilities[i] = count[i] / static_cast<float>(total_size);
    }
    
}
