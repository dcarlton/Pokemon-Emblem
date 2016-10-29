#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>

#include "SDL.h"

#include "Image.h"
#include "ImageEnum.h"
#include "../Utility/Point.h"


class Utility::Size;


namespace GUI
{
	void cleanup();
	void createWindow(Utility::Size size,
					  std::string title);
	void deleteWindow();
	void drawImage(Image image, Utility::Point position);
	void drawImage(GUI::Image image, SDL_Rect* imageRect, Utility::Point targetPosition);
	void drawMenu(std::vector<std::string> items, Utility::Point position);
	void drawPokemon(Utility::Point targetPosition, int pokemonOffset, int animationOffset);
	Image getImage(ImageEnum imageEnum);
    void loadAssets();
	void loadEngine();
	void showMessage(std::string message);
	void updateWindow();
};

#endif