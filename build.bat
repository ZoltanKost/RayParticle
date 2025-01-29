@echo off
cd w:/Engine/
mkdir builds
pushd builds
cl -Zi w:\Engine\src\engine.c ..\src\lib\raylibdll.lib /I ..\src\include
popd

