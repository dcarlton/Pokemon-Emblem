#ifndef GUI_H
#define GUI_H

#include <string>

#include "SDL.h"


namespace GUI
{
	void cleanup();
	void createWindow(int width,
		              int height,
					  std::string title);
	void deleteWindow();
	void drawImage(SDL_Surface* image, int x, int y, int width, int height);
	SDL_Surface* getImage(const std::string imageFilename);
    void loadAssets();
	void loadEngine();
	void updateWindow();
};

#endif