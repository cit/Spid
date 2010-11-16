// ---------------------------------------------------------------------------
// Qosilan.h
//
// Author: Florian Adamsky <florian.adamsky@iem.fh-friedberg.de>
// ---------------------------------------------------------------------------
#ifndef QOSILAN_H
#define QOSILAN_H

#include "IObserver.h"
#include "Flow/Controller.h"

class Qosilan : public IObserver {
public:
    virtual void handleEvent(fiveTupel flow, char* protocol);
};

#endif // QOSILAN_H
