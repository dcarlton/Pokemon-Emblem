#include "MoveUtils.h"


int State::Controller::moveDown(int oldPos, int maxPos)
{
    if (oldPos < maxPos)
        return oldPos + 1;
    else if (oldPos == maxPos)
        return oldPos;
    else
        throw OutOfBoundsException();
}

int State::Controller::moveLeft(int oldPos, int minPos)
{
    if (oldPos > minPos)
        return oldPos - 1;
    else if (oldPos == minPos)
        return oldPos;
    else
        throw OutOfBoundsException();
}

int State::Controller::moveRight(int oldPos, int maxPos)
{
    if (oldPos < maxPos)
        return oldPos + 1;
    else if (oldPos == maxPos)
        return oldPos;
    else
        throw OutOfBoundsException();
}

int State::Controller::moveUp(int oldPos, int minPos)
{
    if (oldPos > minPos)
        return oldPos - 1;
    else if (oldPos == minPos)
        return oldPos;
    else
        throw OutOfBoundsException();
}