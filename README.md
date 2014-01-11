opendash
========

![basic opendash image](https://f.cloud.github.com/assets/699550/1893137/55c8432e-7a70-11e3-84f5-6d01b6784588.png)

SDL game launcher / front end for linux

Prerequisites
=============

sdl, sdl_ttf, sdl_image

Configuration
=============

This game launcher is seriously minimal.  It has only a few features:

- launch a binary or shell script
- list the contents of a directory, launch a binary and pass the filename in as an argument.  So you can iterate through a list of ROMs in the UI, and launch your emulator.  If you need more parameters to pass to your emulator, do it in a shell script that accepts the ROM file and does the rest of the processing somewhere else.
- Exit the application.

It is also minimally themable.  More demo themes will come soon.  There is also functionality for switching themes via the menuing system.

Potential Future
================

There's room here for more pi-specific features like showing the temperature in the corner.  Also one could get rid of all the Xbox-related cruft.

The goal here is easy configuration - this app will never have a massive directory of configuration XML files in order to get working, even if that means we don't add support for animations, game logos, game types, etc, etc.

History
=======

8 years ago this was an open-source, legal dashboard for the xbox.  It was the first freely distributable xbox dashboard because it was built using the OpenXDK, instead of the oft-pirated official Microsoft XDK which powered almost all of the amazing Xbox homebrew scene.

After looking at current options for
