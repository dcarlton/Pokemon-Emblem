#ifndef OPTIONS_H
#define OPTIONS_H


namespace Filesystem
{

int GetMusicVolume();
int GetSoundEffectVolume();
void LoadIniFile();
void SetMusicVolume(unsigned int volume);
void SetSoundEffectVolume(unsigned int volume);

}


#endif