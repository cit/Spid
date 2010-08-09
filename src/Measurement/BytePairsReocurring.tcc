// ---------------------------------------------------------------------------
// BytePairsReoccuring.tcc
// This class gets a tcp or an udp flow and looks how often a byte occurs and
// calculates the probability.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> BytePairsReocurring(T* flow) {
    size          = 256;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));
    
    u_char* p_payload_one;
    u_char* p_payload_two;
    unsigned short payload_size_one;
    unsigned short payload_size_two;

    if (flow->packets.at(0)->protocol == TCP) {
        p_payload_one = flow->packets.at(0)->pTcp->payload;
        p_payload_two = flow->packets.at(1)->pTcp->payload;

        payload_size_one = flow->packets.at(0)->pTcp->payloadSize;
        payload_size_two = flow->packets.at(1)->pTcp->payloadSize;
    }
    else {
        p_payload_one = flow->packets.at(0)->pUdp->payload;
        p_payload_two = flow->packets.at(1)->pUdp->payload;

        payload_size_one = flow->packets.at(0)->pUdp->payloadSize;
        payload_size_two = flow->packets.at(1)->pUdp->payloadSize;
    }

    unsigned char smaller = 0;
    if (payload_size_one < payload_size_two)
        smaller = payload_size_one;
    else
        smaller = payload_size_two;
    
    if (smaller > 32)
        smaller = 32;

    total_size = smaller;

    for (unsigned char i = 0; i < (smaller-1); ++i) {
        if ( (*p_payload_one == *p_payload_two) and
             (*(p_payload_one +1) == *(p_payload_two +1)) ) {
            u_int byte =  static_cast<u_int>(*p_payload_one);
            //printf("FOO: %02X %02X\n",
            //         *p_payload_one, *(p_payload_one+1));
            count[byte]++;
        }
        
        p_payload_one++;
        p_payload_two++;
    }
    
    for (unsigned short i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
}
