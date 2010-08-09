#ifndef ENUMS_H
#define ENUMS_H

enum Protocol {
    TCP,
    UDP
};

enum TcpStates {
    LISTEN,
    REQUEST,
    GRANTED,
    ESTABLISHED,
    FIN_RCVD,
    HALF_CLOSED,
    FIN_RCVD_2,
    CLOSED
};


enum Direction {
    ORIGINATOR_TO_RESPONDER = -1,
    RESPONDER_TO_ORIGINATOR = 1
};

#endif
