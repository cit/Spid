// ---------------------------------------------------------------------------
// ActionReactionFirst3ByteHashMeter.cpp
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> ActionReactionFirst3ByteHashMeter(T* flow) {
    size          = 256;
    total_size    = 57;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    u_char*        p_payload_one;
    u_char*        p_payload_two;
    unsigned short payload_size_one;
    unsigned short payload_size_two;

    Direction last_direction = ORIGINATOR_TO_RESPONDER;

    for (unsigned short i = 1; i < all_packets; ++i) {
        if (last_direction != flow->packets.at(i)->direction) {

            last_direction = flow->packets.at(i)->direction;

            if (flow->packets.at(i)->protocol == TCP) {
                p_payload_one    = flow->packets.at(i-1)->pTcp->payload;
                payload_size_one = flow->packets.at(i-1)->pTcp->payloadSize;
                p_payload_two    = flow->packets.at(i)->pTcp->payload;
                payload_size_two = flow->packets.at(i)->pTcp->payloadSize;
            }
            else {
                p_payload_one    = flow->packets.at(i-1)->pUdp->payload;
                payload_size_one = flow->packets.at(i-1)->pUdp->payloadSize;
                p_payload_two    = flow->packets.at(i)->pUdp->payload;
                payload_size_two = flow->packets.at(i)->pUdp->payloadSize;
            }


            unsigned char smaller = 0;
            if (payload_size_one < payload_size_two)
                smaller = payload_size_one;
            else
                smaller = payload_size_two;
            
            if (smaller > 3) {
                smaller = 3;
            }

            unsigned char crosssum_one = 0;
            unsigned char crosssum_two = 0;

            for (unsigned char y = 0; y < smaller; ++y) {
                unsigned short byte_one =
                    static_cast<unsigned short>(*p_payload_one);
                unsigned short byte_two =
                    static_cast<unsigned short>(*p_payload_two);

                unsigned short rest = 0;
                do {
                    rest = byte_one%10;
                    byte_one = byte_one/10;
                    crosssum_one += rest;
                } while (byte_one > 0);

                rest = 0;
                do {
                    rest = byte_two%10;
                    byte_two = byte_two/10;
                    crosssum_two += rest;
                } while (byte_two > 0);
                
                p_payload_one++;
                p_payload_two++;
            }

            count[crosssum_one]++;
            count[crosssum_two]++;
        }
        
    }
    
    for (unsigned short i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
}
