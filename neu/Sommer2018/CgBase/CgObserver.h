/*
 * FhhObserver.h
 *
 *  Created on: 16.02.2012
 *      Author: ginkel
 */

#ifndef CGOBSERVER_H_
#define CGOBSERVER_H_


#include "CgBaseEvent.h"

class CgObserver {
public:
    virtual void handleEvent(CgBaseEvent* e) = 0;

};

#endif /* CGOBSERVER_H_ */
