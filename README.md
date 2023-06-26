# SFML-Practice
Commands to build statically and dynamically are provided.

# Running

To compile
```
g++ -c main.cpp -I"C:\SFML-2.6.0\include"
```

Create runnable exe
```
g++ main.o -o main -LC:\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
```

If make is installed on your device then run the following command

```
make
```
To get rid of the main.o file run
```
make clean
```

# Dependencies
The latest version of SMFL is required to run the program.

https://www.sfml-dev.org/download.php

Make sure to place the folder into the C or replace the location in the run/compile commands.
