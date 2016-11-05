#ifndef DJ_H
#define DJ_H

#include "TrackList.h"


namespace Audio
{
    void cleanup();
    void initAudio();
    void playMusic(Music musicToPlay); 
    void playSoundEffect(SoundEffect soundEffectToPlay);
    void updateMusicVolume();
    void updateSoundEffectVolume();
}


#endif