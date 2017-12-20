#ifndef TUPLE_H
#define TUPLE_H


template class T1;
template class T2;

namespace Utility
{

class Tuple
{
    T1 first;
    T2 second;

    Tuple(T1 first, T2 second)
    {
        this->first = first;
        this->second = second;
    }
}

}

#endif
