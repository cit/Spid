// ---------------------------------------------------------------------------
// UnicodeFrequency.tcc
// This class gets a tcp-flow and counts every unicode byte in the payload of a
// packet and calculates the probability.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> UnicodeFrequency(T* flow) {
    size          = 256;
    count         = new int[size]();
    probabilities = new float[size]();

     // some compiler do not support null initialisation with ={0} or ();
    memset(count,0,(size*sizeof(int)));
    memset(probabilities,0,(size*sizeof(float)));

    for (unsigned char i = 0; i < 5; ++i) {
        if (flow->packets.at(i)->protocol == TCP) {
            p_payload    = flow->packets.at(i)->pTcp->payload;
            payload_size = flow->packets.at(i)->pTcp->payloadSize;
        }
        else {
            p_payload    = flow->packets.at(i)->pUdp->payload;
            payload_size = flow->packets.at(i)->pUdp->payloadSize;
        }

        total_size = payload_size;

        // if (payload_size > 128)
        //     payload_size = 128;

        int  length    = 0;
        bool buchstabe = false;
        
        for (unsigned short y = 0; y < payload_size; ++y) {
            int byte = static_cast<int>(*p_payload);
            
            if (!buchstabe) {
                if ((byte >= 65 and byte <= 90) or
                    (byte >= 97 and byte <= 122)) {
                    length++;
                    buchstabe = true;
                }
                else {
                    if (length > 5 ) {
                        u_char* ptr = p_payload;
                        ptr -= length;
                        for (int x=0; x<length; ++x) {
                            if (*ptr != 0)
                                count[byte]++;
                                //printf("%c", *ptr);
                            ptr++;
                        }
                        //printf("\n");
                    }
                    length=0;
                }
            }
            else {
                if (byte == 0) {
                    length++;
                    buchstabe = false;
                }
            }
            p_payload++;
        }
        
    }
    
    for (unsigned short i = 0; i < size; ++i)
        probabilities[i] = count[i] / static_cast<float>(total_size);

}

