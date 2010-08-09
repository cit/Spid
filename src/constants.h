#ifndef CONSTANTS_H
#define CONSTANTS_H

// maximal bytes to capture
#define MAX_BYTES_2_CAPTURE 2048

// the value for tcp in the protocol field from ip
#define TCP_ID 0x06

// the value for udp in the protocol field from ip
#define UDP_ID 0x11

// ethernet headers are always exactly 14 bytes
#define ETHERNET_SIZE 14

// maximal payload size
#define MAX_PAYLOAD_SIZE 1460

// maximal elapsed time in microseconds
#define MAX_USEC_TIME 1000000


#endif // CONSTANTS_H
