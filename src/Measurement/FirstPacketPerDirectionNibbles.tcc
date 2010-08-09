// ---------------------------------------------------------------------------
// FirstPacketPerDirectionNibbles.tcc
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> FirstPacketPerDirectionNibbles(T* flow) {
    size          = 256;
    count         = new int[size]();
    probabilities = new float[size]();

    // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    u_char* p_payload;
    unsigned short payload_size;
    unsigned short found = 0;

    total_size = size;

    for (unsigned char i = 0; i < all_packets; ++i) {
        if (flow->packets.at(0)->protocol == TCP) {
            p_payload    = flow->packets.at(i)->pTcp->payload;
            payload_size = flow->packets.at(i)->pTcp->payloadSize;
        }
        else {
            p_payload    = flow->packets.at(i)->pUdp->payload;
            payload_size = flow->packets.at(i)->pUdp->payloadSize;
        }

        if ((flow->packets.at(i)->direction == ORIGINATOR_TO_RESPONDER)
            and (found == 0)) {
            for (unsigned char y = 0; y < 8; ++y) {

                if (payload_size < 8) 
                    continue;
                
                u_int byte  = static_cast<u_int>(*p_payload);
                u_int index = static_cast<u_int>((128+y*16 + byte) / 2);
                count[index]++;
                p_payload++;
            }
            found=1;
        }
        else if ((flow->packets.at(i)->direction == RESPONDER_TO_ORIGINATOR)
                 and (found == 1)) {
            for (unsigned char y = 0; y < 8; ++y) {

                if (payload_size < 8)
                    continue;
                
                u_int byte  = static_cast<int>(*p_payload);
                u_int index = static_cast<int>((y*16 + byte) / 2);
                count[index]++;
                p_payload++;
                //cout << index << endl;
            }
            break;
        }
    }

    for (unsigned short i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);
}
