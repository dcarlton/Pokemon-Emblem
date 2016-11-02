#include "SDL_mixer.h"

#include "DJ.h"
#include "../Utility/Log.h"
#include "../Filesystem/Options.h"


namespace
{
    Mix_Music *currentMusic = NULL;
}

// Safely shut down the SDL_Mixer.
void Audio::cleanup()
{
    Mix_FreeMusic(currentMusic);
    Mix_CloseAudio();
}

// Initialize the SDL_Mixer to play audio.
void Audio::initAudio()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        Utility::log("Audio could not be initialized.");

    updateMusicVolume();
}

// Play the chosen musical track on infinite loop.
void Audio::playMusic(Music musicToPlay)
{
    switch (musicToPlay)
    {
        case Music::Music:
            // TODO: Cleanup
            // TODO: Should check if the music already exists and is paused.
            // http://lazyfoo.net/SDL_tutorials/lesson11/
            currentMusic = Mix_LoadMUS("../resources/Audio/Music/StageMusic.wav");
            if (currentMusic == NULL)
                Utility::log("Stage music could not be loaded.");
            Mix_PlayMusic(currentMusic, -1);
            break;
    }
}

// Play the chosen sound effect one time.
void Audio::playSoundEffect(SoundEffect soundEffectToPlay)
{
    soundEffectToPlay;
}

// Call when the music volume configuration is changed to update the current
// music.
void Audio::updateMusicVolume()
{
    Mix_VolumeMusic(Filesystem::GetMusicVolume());
}