@echo off
pushd %~dp0\..\
call vendor\bin\premake\premake5.exe --file=premake5.lua vs2019
popd
PAUSE
