echo Compiling...; 
g++ 'Shrek Dating Sim.cpp' -Llib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o 'Shrek Dating Sim'; 
if ($?) {echo Running...; .\\'Shrek Dating Sim'} 
