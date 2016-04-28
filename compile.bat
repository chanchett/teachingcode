@echo off

pushd compiled_programs

cl ..\%1 /FIhelpful.h /DLESSON_%~n1 /I"..\window\includes" "..\window\lib\SDL2.lib" "..\window\lib\SDL2_ttf.lib" /EHsc

popd
