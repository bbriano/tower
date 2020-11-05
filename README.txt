I don't have access to a windows computer so I cannot submit a Visual Studio project
This is a short guide on how to compile and run the tower game

prerequisite:
- a c++ compiler.
    clang compiler: https://releases.llvm.org/download.html
    NOTE: for windows users make sure select 'Add LLVM to the system PATH' option during installation

== WINDOWS ==
Open Command Prompt and enter the following commands:
go to project folder
    cd %HOMEPATH%\Downloads\the_tower
build game
    clang++ *.cpp -o tower.exe
run game
    tower.exe

== MACOS / LINUX ==
Open a terminal and enter the following commands:
go to project folder
    cd ~/Downloads/the_tower
build game using clang
    clang++ *.cpp -o tower
run game
    ./tower
