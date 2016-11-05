#include "SDL_mixer.h"

#include "DJ.h"
#include "../Utility/Log.h"
#include "../Filesystem/Options.h"


namespace
{
    const int MUSIC_CHANNEL = 1;
    const int SOUND_EFFECT_CHANNEL = 2;

    Mix_Chunk *currentMusic = NULL;
    Mix_Chunk *currentSoundEffect = NULL;
}

// Safely shut down the SDL_Mixer.
void Audio::cleanup()
{
    Mix_FreeChunk(currentSoundEffect);
    Mix_FreeChunk(currentMusic);
    Mix_CloseAudio();
}

// Initialize the SDL_Mixer to play audio.
void Audio::initAudio()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        Utility::log("Audio could not be initialized.");

    updateMusicVolume();
    updateSoundEffectVolume();
}

// Play the chosen musical track on infinite loop.
void Audio::playMusic(Music musicToPlay)
{
    Mix_FreeChunk(currentMusic);

    switch (musicToPlay)
    {
        case Music::Music:
            // TODO: Cleanup
            // TODO: Should check if the music already exists and is paused.
            // http://lazyfoo.net/SDL_tutorials/lesson11/
            currentMusic = Mix_LoadWAV("../resources/Audio/Music/StageMusic.wav");
            if (currentMusic == NULL)
                Utility::log("Stage music could not be loaded.");
            Mix_PlayChannel(MUSIC_CHANNEL, currentMusic, -1);
            break;
    }
}

// Play the chosen sound effect one time.
void Audio::playSoundEffect(SoundEffect soundEffectToPlay)
{
    Mix_FreeChunk(currentSoundEffect);
    updateSoundEffectVolume();

    switch (soundEffectToPlay)
    {
        case SoundEffect::TestSoundEffect:
            currentSoundEffect = Mix_LoadWAV("../resources/Audio/SoundEffects/TestSoundEffect.wav");
            if (currentSoundEffect == NULL)
                Utility::log("Sound effect could not be loaded.");
            
            Mix_PlayChannel(SOUND_EFFECT_CHANNEL, currentSoundEffect, 0);
    }
}

// Call when the music volume configuration is changed to update the current
// music.
void Audio::updateMusicVolume()
{
    Mix_Volume(MUSIC_CHANNEL, Filesystem::GetMusicVolume());
}

void Audio::updateSoundEffectVolume()
{
    Mix_Volume(SOUND_EFFECT_CHANNEL, Filesystem::GetSoundEffectVolume());
}