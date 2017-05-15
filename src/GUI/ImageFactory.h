#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H

#include "Image.h"
#include "ImageEnum.h"


namespace GUI
{
    const Image* makeImage(ImageEnum imageEnum);
}

#endif