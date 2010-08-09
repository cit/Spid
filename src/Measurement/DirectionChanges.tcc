// ---------------------------------------------------------------------------
// DirectionChanges.cpp
// This is an attribute meter and it counts the direction changes from a flow.
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
template <class T> DirectionChanges(T* flow) {
    size          = 1;
    count         = new int[size]();
    probabilities = new float[size]();
    total_size    = all_packets - 1;

    // some compiler do not support null initialisation with ={0} or ();
    count[0] = 0;
    probabilities[0] = 0.0;
    
    for (unsigned char i = 0; i < total_size; ++i) {
        if (flow->packets.at(i)->direction != flow->packets.at(i+1)->direction)
            count[0]++;
    }

    probabilities[0] = count[0] / static_cast<float>(total_size);
}
