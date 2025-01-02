    ultrared game engine
============================

    ultrared is a simple 3D-ish "game" "engine" (both terms used very loosely) written using C++ and SDL2.

    *** 1. Compilation ***

        In order to compile the engine you need the following:
            1. a C++ compiler (preferably G++)
            2. GNU Make
            3. SDL2 library
            4. SDL2 TTF
            5. *nix system (preferably Linux)

        If you have all of the above run the following command to compile ultrared:
            make -i clean && make

        These commands will generate an executable called "0".

    *** 2. Running ***

        To run ultrared you must first compile it (as described in 1. Compilation). If you successfully
        compiled ultrared you can run it with the following command:
            ./0 <path to the map file>

        A demo map file is located in /data/maps/.
