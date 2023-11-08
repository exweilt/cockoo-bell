# Cuckoo clock
I was astonished by a cuckoo clock visiting one of my friends and decided to write a small program for myself. 
Hope you enjoy this as much as I do :) 
This program **plays** pleasant bell sound every hour and is currently available only for **Windows**.

## Installing
Launch INSTALL.bat after downloading the release, or compiling the code.
> Default installation folder is `C:/Program Files`. It can be changed from the bat file.

## Uninstalling
Launch UNINSTALL.bat from the app folder.

## Compiling
Use CMake to configure the project and generate makefiles/project files to build.
It will also install the only dependency for you - **SFML**.

## Configuring
Edit `VOLUME` and `PITCH` global variables(`Cockoo.cpp`) to change correspondent parameters.

## Licence
The Cockoo is under GNU Public License.