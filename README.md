# CSC-410
## OpenGL graphics


### DIRECTORY STRUCTURE 

- Create an overarching dir 
  - bin 
    - this is where your executables will be created using the makefile. Go here to run the executables.
  - include 
    - place header files (`.h`) in this dir 
  - lib 
    - place `rklib.cpp`, `utils.cpp`, and `libGraphicsUtils.a` in this dir 
    - also place makefile and then `make` 
      - sources for makefile should be `Utils.cpp` and `rklib.cpp`
  - src 
    - place project files in this dir (files like `ThreePoints.cpp`, etc.)
    - place makefile in this dir as well and alter it as needed. 
    - alternatively, you can make each project a subdir in the src director and have each subdir have its own makefile for that specific project
    
    
### MAKEFILE
- I am **not** the creator of the makefile (I recieved it from a professor while in school and makefiles are a wizardry I'll eventually learn)
- use the template makefile and alter it for each project 
  - you will need to change the `FILENAME =  _________` to whatever your heart desires. This will be the name of the executable 
  
  
### USE
  - Once you run make on the desired file, an executable will be created in the bin folder
  - `./filename` to run 
  - To remake, use make clean to delete the current obj directory (where the `.d` and `.o` files are storeed) and then run make again
  - Some programs will need `.dat` files to read points
  
