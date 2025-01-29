@echo off
title "WND_CMD"
subst w: C:\Users\mike\dev
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set PATH="w:\Engine\";"w:\batch\";%path%
w:
