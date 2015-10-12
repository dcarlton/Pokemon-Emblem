#ifndef GUI_H
#define GUI_H

#include <string>

#include "SDL.h"

#include "Image.h"
#include "ImageEnum.h"
#include "../Utility/Point.h"


class Size;


namespace GUI
{
	void cleanup();
	void createWindow(Size size,
					  std::string title);
	void deleteWindow();
	void drawImage(Image image, Point position);
	Image getImage(ImageEnum imageEnum);
    void loadAssets();
	void loadEngine();
	void showMessage(std::string message);
	void updateWindow();
};

#endif