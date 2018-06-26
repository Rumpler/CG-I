#include "IdSingleton.h"

#include <iostream>



int IdSingleton::getNextId(){
    id++;
    std::cout << "ID: " << id << std::endl;
    return id;
}

IdSingleton &IdSingleton::instance()
{
    static IdSingleton INSTANCE;
    return INSTANCE;
}
