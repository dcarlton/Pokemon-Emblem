#ifndef GUI_H
#define GUI_H

#include <memory>
#include <string>
#include <vector>

#include "SDL.h"

#include "Image.h"
#include "ImageEnum.h"
#include "../Utility/Point.h"
#include "../Gameplay/Pokemon.h"


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
	void drawPokemon(std::shared_ptr<Gameplay::Pokemon> pokemon, Utility::Point position);
	void drawPokemonOnMap(Utility::Point targetPosition, int pokemonOffset, int animationOffset);
	void drawPokemonStats(std::shared_ptr<Gameplay::Pokemon> pokemon);
	void drawText(std::string text, Utility::Point drawPosition, Utility::Point pixelOffset, SDL_Color textColor);
	Image getImage(ImageEnum imageEnum);
    void loadAssets();
	void loadEngine();
	void showMessage(std::string message);
	void updateWindow();
};

#endif