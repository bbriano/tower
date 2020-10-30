
Short guide on how to build and run the troubled tower game
I don't have access to a windows computer so I cannot submit a Visual Studio project

prerequisite:

- a c++ compiler.
    clang compiler: https://releases.llvm.org/download.html
    NOTE: for windows users make sure select 'Add LLVM to the system PATH' option during installation

WINDOWS:

Open Command Prompt and enter the following commands:

change directory

    cd %HOMEPATH%\Downloads\briano31482228

build game

    clang++ *.cpp -o tower.exe

run game

    tower.exe

MAC / LINUX:

Open a terminal and enter the following commands:

change directory to source files directory

    cd ~/Downloads/briano31482228

build game using clang

    clang++ *.cpp -o tower

run game

    ./tower
