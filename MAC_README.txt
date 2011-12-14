@@  Installation and Building of ArduPilotOne on a Mac
@@
@@
@@  Modified from README.txt by James Goppert jgoppert@gmail.com
@@  By: Nathanael Xie Wenyao wenyaoxie@gmail.com Dec 13 2011



Install Procedure:
1. Install MacPorts
2. Install Cmake via MacPorts
3. Install Arduino IDE (only versions 0022 and 0023 currently supported)
4. Build using Cmake





Installing MacPorts
-----------------------------------------------
 - Ensure you have the following 2 pre-requisites for MacPorts:

	1.  Apple's Xcode Developer Tools (version 4.1 or later for Lion, 3.2 or later for Snow Leopard, or 3.1 or later for Leopard), found at the Apple Developer Connection site, on your Mac OS X installation CDs/DVD, or in the Mac App Store. Using the latest available version that will run on your OS is highly recommended. Ensure that the optional components for command line development are installed ("UNIX Development", plus "System Tools" in newer versions, or "Command Line Support" in older ones).

	2. The X11 windowing environment (A.K.A. “X11 User”) for ports that depend on the functionality it provides to run.
The “X11 User” package is an optional installation on your system CDs/DVD for Tiger, enabled through the “Customize” button of the installer, whereas it is included by default on Leopard and newer.
You can use the xorg-server port instead of Apple's X11.app if you wish.

 - Go to: http://www.macports.org/install.php
 - Download the .pkg for your OS and install it


Installing Cmake via MacPorts
-----------------------------------------------
 - Open Terminal.app (Applications > Utilities > Terminal)
 - sudo port install cmake
 - sudo port build cmake

Installing Arduino IDE
-----------------------------------------------
 - Go to: http://arduino.cc/en/Main/Software
 - Download the desired Arduino version (0022 or 0023)
 - Drag the Arduino.app into the Applications folder on your computer

Building using cmake
-----------------------------------------------
Within your ardupilotone directory, execute the following in Terminal.app:
 - mkdir build
 - cd build
 - cmake .. -DBOARD=mega -DPORT=/dev/ttyUSB0 -DARDUINO_SDK_PATH=/Applications/Arduino.app/Contents/Resources/Java/
    Note: Boards that can be selected are mega/mega2560

Then choose from the following options from within the build directory:
 - make (will build every sketch)
 - make ArduPlane (will build just ArduPlane etc.)
 - make ArduPloat-upload (will upload the sketch)

    If you have a sync error during upload reset the board/power cycle the board
    before the upload starts.





OPTIONAL: This is provided for those who want to build from the Eclipse IDE 
Building using eclipse
-----------------------------------------------

    Getting the Source:

        assuming source located here: /home/name/apm-src
        You can either download it or grab it from git:
        git clone https://code.google.com/p/ardupilot-mega/ /home/name/apm-src

    Generating the Eclipse Project for Your System:
    
        mkdir /home/name/apm-build 
        cd /home/name/apm-build
        cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../apm-src -D BOARD=mega -D PORT=/dev/ttyUSB0

        Note: Unix can be substituted for MinGW/ MSYS/ NMake (for windows)
            (see http://www.vtk.org/Wiki/Eclipse_CDT4_Generator)

        input options:

            CMAKE_BUILD_TYPE choose from DEBUG, RELEASE etc.
            PORT is the port for uploading to the board, COM0 etc on windows. /dev/ttyUSB0 etc. on linux
            BOARD is your board type, mega for the 1280 or mega2560 for the 2560 boards.
            ARDUINO_SDK_PATH if it is not in default path can specify as /path/to/arduino
        
    Importing the Eclipse Build Project:

        Import project using Menu File->Import
        Select General->Existing projects into workspace:
        Browse where your build tree is and select the root build tree directory. 
        Keep "Copy projects into workspace" unchecked.
        You get a fully functional eclipse project

    Importing the Eclipse Source Project:
    
        You can also import the source repository (/home/name/apm-src) if you want to modify the source/ commit using git.

    Settings up Eclipse to Recognize PDE files:

         Window > Preferences > General > Content Types. This tree associates a
            filename or filename pattern with its content type so that tools can treat it
            properly. Source and header files for most languages are under the Text tree. 
            Add "*.pde" as a C++ Source.

	Autocompletion:
	
		Right click on source project -> Properties -> Project References -> apm-build Project
    
    Advanced:
    
        * Regenerating the eclipse source project file:
            cmake -G"Eclipse CDT4 - Unix Makefiles" -DECLIPSE_CDT4_GENERATE_SOURCE_PROJECT=TRUE /home/name/apm-src




vim:ts=4:sw=4:expandtab
