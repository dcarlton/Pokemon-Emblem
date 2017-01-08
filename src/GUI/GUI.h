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
#include "../Gameplay/Tile.h"


namespace GUI
{
	void cleanup();
	void createWindow(Utility::Point size,
					  std::string title);
	void deleteWindow();
	void drawImage(Image image, Utility::Point position);
	void drawImage(Image image, SDL_Rect* imageRect, Utility::Point targetPosition);
	void drawImage(Image image, SDL_Rect* imageRect, Utility::Point targetPosition, Utility::Point pixelOffset);
	void drawMenu(std::vector<std::string> items, Utility::Point position);
	void drawPokemon(std::shared_ptr<Gameplay::Pokemon> pokemon, Utility::Point position);
	void drawPokemonOnMap(Utility::Point targetPosition, int pokemonOffset, int animationOffset);
	void drawPokemonStats(std::shared_ptr<Gameplay::Pokemon> pokemon);
	void drawText(std::string text, Utility::Point drawPosition, Utility::Point pixelOffset, SDL_Color textColor);
	void drawTile(Gameplay::Tile tile, Utility::Point position);
	void drawWorld(std::vector<std::vector<Gameplay::Tile>> map, Utility::Point cursorPos);
	Image getImage(ImageEnum imageEnum);
    void loadAssets();
	void loadEngine();
	Utility::Point mousePositionToCursorPosition(int x, int y);
	Utility::Point setCursorFromMouse(int x, int y, Utility::Point mapSize);
	void showMessage(std::string message);
	void updateWindow();
};

#endif