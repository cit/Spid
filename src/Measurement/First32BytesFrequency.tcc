// ---------------------------------------------------------------------------
// First32BytesFrequency.tcc
// This class gets a udp-flow and counts 32 byte in the payload of a
// packet and calculates the probability. 
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> First32BytesFrequency(T* flow) {
    size          = 256;
    total_size    = 32;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    if (flow->packets.at(0)->protocol == TCP) {
        p_payload    = flow->packets.at(0)->pTcp->payload;
        payload_size = flow->packets.at(0)->pTcp->payloadSize;
    }
    else {
        p_payload    = flow->packets.at(0)->pUdp->payload;
        payload_size = flow->packets.at(0)->pUdp->payloadSize;
    }

    if (payload_size < total_size)
        total_size = payload_size;

    for (unsigned short y = 0; y < total_size; ++y) {
        u_int byte = static_cast<u_int>(*p_payload);
        p_payload++;
        
        count[byte]++;
    }

    for (unsigned short i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
    
}
