@echo off

pushd build
cl /EHsc /ZI /W4 /WX /wd4996 ..\Tests.cpp ..\src\Utility\*.cpp ..\test\UnitTests\Utility\*.cpp ..\src\State\*.cpp ..\test\UnitTests\State\*.cpp ..\src\Data\*.cpp /I ..\include /link /libpath ..\lib\SDL2.lib
Tests.exe
del Tests.exe
popd