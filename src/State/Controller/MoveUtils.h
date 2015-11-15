#include <exception>

#include "../../Utility/Point.h"


namespace State
{
namespace Controller
{

class OutOfBoundsException: public std::exception{};

int moveDown(int oldPos, int maxPos);
int moveLeft(int oldPos, int minPos);
int moveRight(int oldPos, int maxPos);
int moveUp(int oldPos, int minPos);

}
}