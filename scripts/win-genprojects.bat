@echo off
pushd ..\
call vendors\bin\premake\premake5.exe vs2019
popd
pause