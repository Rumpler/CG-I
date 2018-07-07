#include "IdSingleton.h"




int IdSingleton::getNextId(){
    id++;
    return id;
}

IdSingleton* IdSingleton::instance()
{
    static IdSingleton INSTANCE;
    return &INSTANCE;
}
