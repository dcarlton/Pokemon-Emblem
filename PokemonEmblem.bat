@echo off

pushd build
cl /EHsc /ZI /MP /W4 /WX /wd4996 /wd4267 ..\Main.cpp ..\src\Gameplay\*.cpp ..\src\GUI\*.cpp ..\src\Utility\*.cpp ..\src\State\*.cpp ..\src\State\Controller\*.cpp /I ..\include /link /libpath ..\lib\SDL2.lib /libpath ..\lib\SDL2_ttf.lib
Main.exe
del Main.exe
popd