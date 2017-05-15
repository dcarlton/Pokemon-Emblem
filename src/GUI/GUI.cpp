#include <algorithm>
#include <memory>

#include "SDL_ttf.h"

#include "../Utility/Color.h"
#include "GUI.h"
#include "ImageFactory.h"
#include "../Utility/Log.h"
#include "../Utility/Point.h"


namespace
{
    const SDL_Color BLACK = {0, 0, 0, 0};
    const int NUM_TILES_TO_DISPLAY = 10;
    const int TILE_HEIGHT = 32;
    const int TILE_WIDTH = 32;
    const SDL_Color WHITE = {255, 255, 255, 0};

    // Pretty sure the static keyword here doesn't actually do anything.
    static TTF_Font *font = nullptr;
    static SDL_Window *window = nullptr;
    static SDL_Surface *windowSurface = nullptr;

    Utility::Point camera = Utility::Point(1, 1);

    // Move the camera so that the given point is visible.
    void focusCamera(Utility::Point pointToContain)
    {
        // Fix the X axis.
        if (pointToContain.x < camera.x)
        {
            camera.x = pointToContain.x;
        }
        else if (pointToContain.x >= (camera.x + NUM_TILES_TO_DISPLAY))
        {
            camera.x = (pointToContain.x - NUM_TILES_TO_DISPLAY) + 1;
        }

        // Fix the Y axis.
        if (pointToContain.y < camera.y)
        {
            camera.y = pointToContain.y;
        }
        else if (pointToContain.y >= (camera.y + NUM_TILES_TO_DISPLAY))
        {
            camera.y = (pointToContain.y - NUM_TILES_TO_DISPLAY) + 1;
        }
    }
}


void GUI::cleanup()
{
    deleteWindow();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void GUI::createWindow(Utility::Point size, std::string title)
{
    deleteWindow();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, 0);
    if (!window)
        Utility::log("Failed to create a window with size " +
                     size.to_string() +
                     " and title " +
                     title);
    windowSurface = SDL_GetWindowSurface(window);
}

void GUI::deleteWindow()
{
    if (!window || !windowSurface)
        Utility::log("Attempting to delete a window when a window has not been created");
    SDL_DestroyWindow(window);
    SDL_FreeSurface(windowSurface);
}

void GUI::drawImage(const GUI::Image* image, Utility::Point position)
{
    drawImage(image, NULL, position, Utility::Point(0, 0));
}

// Draw an image to the screen at the target position. ImageRect defines what
// piece of the image should be drawn to the screen. If it is NULL, draw the entire
// image.
//
// The target position is the position in the map; we need to adjust it based
// on the camera.
void GUI::drawImage(const GUI::Image* image, SDL_Rect* imageRect, Utility::Point targetPosition)
{
    GUI::drawImage(image, imageRect, targetPosition, Utility::Point(0, 0));
}

// Draw an image to the screen at the target position. ImageRect defines what
// piece of the image should be drawn to the screen. If it is NULL, draw the entire
// image.
//
// The target position is the position in the map; we need to adjust it based
// on the camera and the given pixel offset.
void GUI::drawImage(const GUI::Image* image, SDL_Rect* imageRect, Utility::Point targetPosition, Utility::Point pixelOffset)
{
    if (!image->surface || !windowSurface)
        return;

    targetPosition -= camera;

    SDL_Rect targetRect;
    targetRect.x = (targetPosition.x * TILE_WIDTH) + pixelOffset.x;
    targetRect.y = (targetPosition.y * TILE_HEIGHT) + pixelOffset.y;
    targetRect.h = image->size.y;
    targetRect.w = image->size.x;

    SDL_BlitSurface(image->surface, imageRect, windowSurface, &targetRect);
}

void GUI::drawMenu(std::vector<std::string> items, Utility::Point position)
{
    const GUI::Image* menuImage = GUI::getImage(GUI::ImageEnum::MenuItem);

    for (unsigned int i = 0; i < items.size(); i++)
    {
        GUI::drawImage(menuImage, NULL, position, Utility::Point(0, i * menuImage->size.y));
        GUI::drawText(items[i], position, Utility::Point(8, 2 + (i * menuImage->size.y)), WHITE);
    }
}

// Draw the Pokemon at the provided position.
void GUI::drawPokemon(std::shared_ptr<Gameplay::Pokemon> pokemon, Utility::Point position)
{
    drawPokemonOnMap(position, pokemon->num - 1, pokemon->animationState);
}

// Draw a Pokemon using the loaded Pokemon sprite sheet. The first offset
// sets how far down the sprite sheet to move before fetching the image;
// Bulbasaur is at the top of the sprite sheet and doesn't require an offset,
// while Ivysaur right below needs an offset of 1, Venusaur is at offset 2, and.
// so on.
//
// The animation offset is used to select a specific pose for that Pokemon. The
// first pose is a neutral stance facing downward, and all other sprites for that
// Pokemon can be found with different offsets.
void GUI::drawPokemonOnMap(Utility::Point targetPosition, int pokemonOffset, int animationOffset)
{
    std::shared_ptr<SDL_Rect> imageRect = std::make_shared<SDL_Rect>();
    imageRect->x = TILE_WIDTH * animationOffset;
    imageRect->y = TILE_HEIGHT * pokemonOffset;
    imageRect->w = TILE_WIDTH;
    imageRect->h = TILE_HEIGHT;

    drawImage(GUI::getImage(GUI::ImageEnum::PokemonSpriteSheet), imageRect.get(), targetPosition);
}

// Draw the most recently selected Pokemon's HP on the screen.
// TODO: Add the Pokemon's alliance and picture in a nice format.
void GUI::drawPokemonStats(std::shared_ptr<Gameplay::Pokemon> pokemon)
{
    if (pokemon == nullptr)
        return;

    std::string text = "Level: " + std::to_string(pokemon->stats.getLevel());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 0), BLACK);

    text = "HP: " + std::to_string(pokemon->stats.getCurrentHP()) + "/" + std::to_string(pokemon->stats.getMaxHP());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 16), BLACK);
    
    text = "Attack: " + std::to_string(pokemon->stats.getAttack());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 32), BLACK);

    text = "Skill: " + std::to_string(pokemon->stats.getSkill());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 48), BLACK);

    text = "Speed: " + std::to_string(pokemon->stats.getSpeed());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 64), BLACK);

    text = "Luck: " + std::to_string(pokemon->stats.getLuck());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 80), BLACK);

    text = "Defense: " + std::to_string(pokemon->stats.getDefense());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 96), BLACK);

    text = "Movement: " + std::to_string(pokemon->stats.getMovementRange());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 112), BLACK);

    text = "Accuracy: " + std::to_string(pokemon->stats.getAccuracy());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 128), BLACK);

    text = "Evasion: " + std::to_string(pokemon->stats.getEvasion());
    drawText(text, Utility::Point(7, 0), Utility::Point(0, 144), BLACK);
}

// Draw text to the screen at the given map position, with an offset down to the
// pixel, and the given color.
void GUI::drawText(std::string text, Utility::Point drawPosition, Utility::Point pixelOffset, SDL_Color color)
{
    drawPosition -= camera;
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Rect targetRect;
    targetRect.x = (drawPosition.x * TILE_WIDTH) + pixelOffset.x;
    targetRect.y = (drawPosition.y * TILE_HEIGHT) + pixelOffset.y;
    targetRect.h = TILE_HEIGHT;
    targetRect.w = TILE_WIDTH * 2;

    SDL_BlitSurface(textSurface, NULL, windowSurface, &targetRect);
    SDL_FreeSurface(textSurface);
}

// Draw the Pokemon and terrain of a tile.
void GUI::drawTile(Gameplay::Tile tile, Utility::Point position)
{
    GUI::drawImage(GUI::getImage(GUI::ImageEnum::TestTile), position);
    if (tile.pokemon)
        GUI::drawPokemon(tile.pokemon, position);
}

// Draw the world and cursor.
void GUI::drawWorld(std::vector<std::vector<Gameplay::Tile>> map, Utility::Point cursorPos)
{
    focusCamera(cursorPos);

    for (unsigned int x = camera.x; x < std::min((unsigned int)map.size(), camera.x + NUM_TILES_TO_DISPLAY); x++)
    {
        for (unsigned int y = camera.y; y < std::min((unsigned int)map[x].size(), camera.y + NUM_TILES_TO_DISPLAY); y++)
        {
            drawTile(map[x][y], Utility::Point(x, y));
        }
    }

    drawImage(GUI::getImage(GUI::ImageEnum::GameplayCursor), cursorPos);
}

const GUI::Image* GUI::getImage(ImageEnum imageEnum)
{
    return makeImage(imageEnum);
}

// Get the index for the menu item the mouse is hovering over.
//
// Of course we can't see the pixels the menu items are at,
// so we will assume there are numMenuItems being displayed from
// the point menuPosition, and that the mouse is at (mouseX, mouseY).
// From there, figure out if the mouse would be over the first menu
// item, the second, etc. and return that as a zero-based index.
// Return -1 if it isn't over a menu item.
int GUI::getMenuItemFromMouse(int mouseX, int mouseY, Utility::Point menuPosition, int numMenuItems)
{
    const Image* menuImage = GUI::getImage(GUI::ImageEnum::MenuItem);
    int menuLeftmostPixel = (menuPosition.x - camera.x) * TILE_WIDTH;
    int menuTopmostPixel = (menuPosition.y - camera.y) * TILE_HEIGHT;

    if (menuPosition.x < camera.x ||
        mouseX < menuLeftmostPixel ||
        mouseX > (int)(menuLeftmostPixel + menuImage->size.x))
    {
        return -1;
    }

    if (menuPosition.y < camera.y || mouseY < menuTopmostPixel)
        return -1;

    int menuItemIndex = ((mouseY - menuTopmostPixel) / menuImage->size.y);
    if (menuItemIndex < numMenuItems)
        return menuItemIndex;
    else
        return -1;
}

void GUI::loadAssets()
{
}

void GUI::loadEngine()
{
    int error = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    if (error != 0)
        Utility::log("Unabe to initialize SDL: " + std::string(SDL_GetError()));

    if (TTF_Init() < 0)
        Utility::log("Unable to initialize SDL_TTF: ");

    font = TTF_OpenFont("resources/Fonts/cour.ttf", 12);
}

// Convert the X and Y coordinates of a mouse to the coordinates
// on a map.
Utility::Point GUI::mousePositionToCursorPosition(int x, int y)
{
    return Utility::Point(camera.x + (x / TILE_WIDTH), camera.y + (y / TILE_HEIGHT));
}

// Move the camera if the mouse is at the edge of the screen, and
// return where the cursor is now.
Utility::Point GUI::setCursorFromMouse(int x, int y, Utility::Point mapSize)
{
    Utility::Point cursorPos = mousePositionToCursorPosition(x, y);

    if (x == 0 && camera.x > 0 && NUM_TILES_TO_DISPLAY < mapSize.x)
        camera.x--;
    else if (x == ((NUM_TILES_TO_DISPLAY * TILE_WIDTH) - 1) && (camera.x + NUM_TILES_TO_DISPLAY) < (mapSize.x))
        camera.x++;
    
    if (y == 0 && camera.y > 0 && NUM_TILES_TO_DISPLAY < mapSize.y)
        camera.y--;
    else if (y == ((NUM_TILES_TO_DISPLAY * TILE_HEIGHT) - 1) && (camera.y + NUM_TILES_TO_DISPLAY) < (mapSize.y))
        camera.y++;

    return cursorPos;
}

void GUI::showMessage(std::string message)
{
    SDL_ShowSimpleMessageBox(0,
                             "",
                             message.c_str(),
                             window);

}

void GUI::updateWindow()
{
    SDL_UpdateWindowSurface(window);
}