#include <sstream>

#include "Options.h"
#include "SimpleIni.h"


namespace
{
    const char* configFilename = "../config.ini";
    CSimpleIniA configInfo;
    std::stringstream stream;
}

// Return the current music volume, ranging from 0 for muted to
// 100 for max volume.
int Filesystem::GetMusicVolume()
{
    stream << configInfo.GetValue("Audio", "MusicVolume", NULL);
    unsigned int volume;
    stream >> volume;

    if (volume > 100)
        return 100;

    return volume;
}

// Load the config file config.ini from the root directory.
void Filesystem::LoadIniFile()
{
    configInfo.SetUnicode();
    configInfo.LoadFile(configFilename);
}

// Set the current music volume.
void Filesystem::SetMusicVolume(unsigned int volume)
{
    if (volume > 100)
        volume = 100;

    stream << volume;
    configInfo.SetValue("Audio", "MusicVolume", stream.str().c_str());
    configInfo.SaveFile(configFilename);
}