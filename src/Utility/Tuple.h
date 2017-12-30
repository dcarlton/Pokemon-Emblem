#ifndef TUPLE_H
#define TUPLE_H


namespace Utility
{

template <class T1, class T2>
class Tuple
{
public:
    T1 first;
    T2 second;

    // It needed a default constructor, so sayeth the Great Compiler
    Tuple()
    {
    }

    Tuple(T1 first, T2 second)
    {
        this->first = first;
        this->second = second;
    }
};

}

#endif
