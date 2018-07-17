#ifndef IDSINGLETON_H
#define IDSINGLETON_H

class IdSingleton
{
public:
    static IdSingleton* instance();
    int getNextId();

private:
    IdSingleton(){}
    int id = 0;
};

#endif // IDSINGLETON_H
