#include "CgObservable.h"
#include "CgObserver.h"

CgObservable::CgObservable() {
	// TODO Auto-generated constructor stub

}

CgObservable::~CgObservable() {
	// TODO Auto-generated destructor stub
}


void CgObservable::attachObserver (CgObserver* obs)
{
	m_observers.push_back(obs);
}

void CgObservable::detachObserver (CgObserver* obs)
{
	m_observers.remove(obs);
}

bool CgObservable::notifyObserver(CgBaseEvent* e)
{
    for (CgObserverListIterator i (m_observers.begin()); i != m_observers.end(); ++i)
		(*i)->handleEvent(e->clone());
	delete e;
	return true;
}
