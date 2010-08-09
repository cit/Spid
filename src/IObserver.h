// ---------------------------------------------------------------------------
// IObserver.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "structs.h"

class Spid;
class IObserver {
public:
    virtual void handleEvent(fiveTupel flow, char* protocol) = 0;
};

#endif // IOBSERVER_H
