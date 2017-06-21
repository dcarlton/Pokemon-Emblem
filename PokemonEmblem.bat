@echo off

pushd build
cl /EHsc /ZI /MP /W4 /WX /wd4996 /wd4267 ..\Main.cpp ..\src\Gameplay\*.cpp ..\src\Audio\*.cpp ..\src\GUI\*.cpp ..\src\Utility\*.cpp ..\src\Filesystem\*.cpp ..\src\State\*.cpp ..\src\State\Controller\*.cpp ..\include\tinyxml2.cpp /I ..\include /link /libpath ..\lib\SDL2.lib /libpath ..\lib\SDL2_ttf.lib /libpath ..\lib\SDL2_mixer.lib
ren Main.exe PokemonEmblem.exe
copy PokemonEmblem.exe ..\PokemonEmblem.exe
del PokemonEmblem.exe
popd
PokemonEmblem.exe
del PokemonEmblem.exe