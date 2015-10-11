#ifndef SIZE_H
#define SIZE_H

// TODO: Namespace Utility

class Size
{
public:
    int height = 0;
    int width = 0;

    Size() {};
    Size(int widthArg, int heightArg) {height = heightArg; width = widthArg;}
};

#endif