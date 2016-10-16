#!/bin/sh
astyle --mode=c --style=ansi --indent=spaces=4 --convert-tabs --align-pointer=name --pad-oper --pad-header --suffix=none --lineend=linux --indent-switches *.cpp
