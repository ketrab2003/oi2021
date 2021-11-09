@echo off

if "%1"=="_chk_" shift

rem --- Konfiguracja ocen.bat ---
rem W przypadku opracowania wlasnego zestawu testow nalezy zmienic
rem zawartosc zmiennej TESTS a testy zabpiowac do kataloguw IN\, OUT\
rem nazwy testow powinny analogiczne do przykladowych

if "%1"=="dom" goto dom
if "%1"=="DOM" goto dom
if "%1"=="dru" goto dru
if "%1"=="DRU" goto dru
if "%1"=="imp" goto imp
if "%1"=="IMP" goto imp
if "%1"=="mon" goto mon
if "%1"=="MON" goto mon
if "%1"=="ukl" goto ukl
if "%1"=="UKL" goto ukl


set T=%1
goto end

:dom
set I=dom
set T=0 0a 1 2 3 4
set C=bin\cmp.exe
goto end
:dru
set I=dru
set T=0 1 2 3 4 5
set C=bin\cmp.exe
goto end
:imp
set I=imp
set T=0 1 2
set C=bin\cmp.exe
goto end
:mon
set I=mon
set T=0 1 2 3
set C=bin\cmp.exe
goto end
:ukl
set I=ukl
set T=0 1 2 3 4
set C=bin\cmp.exe
goto end


rem --- Koniec konfiguracji

:end

if "%C%"=="" goto def_chk
goto new_chk
:def_chk
set C=bin\cmp.exe
:new_chk

:real_end
