@echo off
pushd compiled_programs

cl ..\%1 /FIhelpful.h

popd
