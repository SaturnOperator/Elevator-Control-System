FLAGS = -g -std=c++11

all: qt

# Install icons font, if this doesn't work you can remove from recipe and should still compile
font:
        mkdir -p ~/.fonts/
        cp -p assets/fonts/fa-solid-900.ttf ~/.fonts/
        fc-cache -f

qt: font
        mkdir -p build
        qmake -o build/Makefile elevatorSimulator.pro
        cd build && $(MAKE)

run: qt
#       ./build/elevatorSimulator.app/Contents/MacOS/elevatorSimulator
        ./build/elevatorSimulator

clean:
        rm -rf build/*
        rm -rf build