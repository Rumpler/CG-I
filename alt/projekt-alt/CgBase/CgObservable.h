/*
 * CgObservable.h
 *
 *  Created on: 16.02.2012
 *      Author: ginkel
 */

#ifndef CGOBSERVABLE_H_
#define CGOBSERVABLE_H_

#include <list>

class CgObserver;
class CgBaseEvent;


class CgObservable {
public:

    virtual ~CgObservable();

    virtual void attachObserver(CgObserver*);
    virtual void detachObserver(CgObserver*);
    virtual bool notifyObserver(CgBaseEvent* e);

protected:
    CgObservable();

    typedef std::list<CgObserver*> CgObserverList;
    typedef CgObserverList::iterator CgObserverListIterator;
    CgObserverList m_observers;

};

#endif /* CGOBSERVABLE_H_ */



