#!/bin/sh
g++ -g -O0 savetheints.c -o savetheints -I/home/carson/opt/include -L/home/carson/opt/lib -lGL -lglut -lGLU
#g++ savetheints.cc -g -o savetheints -lglut -lGL -msse3  -L/udd/cbrownle/svn/gl2manta/gl2manta/lib -L/udd/cbrownle/svn/Manta/build/lib -lManta_Core -lManta_Engine -lManta_Factory -lManta_Interface -lManta_Model -lManta_Image -lManta_UserInterface -lManta_Core_XUtils -lAbout -lgl2manta
