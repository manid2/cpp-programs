# Programs for fun

### Simple **Cpp programs** to:  
1 Learn Cpp techniques.  
2 Solve simple problems.  
3 Automate or simplify redundant tasks.  

This project uses CMake to support cross-platform build.

Install [CMake](https://cmake.org/) to generate the build files for your system.

## How to use?

```sh
# I prefer to use out-of-source build for easy maintainence.
# It separates the source files from the build files and binaries.

mkdir ProgramsForFun_top
cd ProgramsForFun_top
git clone https://github.com/manid2/ProgramsForFun.git

mkdir build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../ProgramsForFun/
```

## TODO
1. Implement **LearnGTestAndGMock**.
2. Add a module to **automatically insert data into an empty space in an image**.
3. Add a module to **Generate/Scan Barcode images**.
4. Add a module to convert **pdf2jpeg** file [If possible].
5. Add a module to **Decode/Encode jpeg2raw** file using libjpeg. 
6. Add a module to show how to use Unicode characters(esp CJK) in C++  
   and character code conversion using libiconv.
7. Add a module to Create/Parse **XML** files.
8. Add a module to Create/Parse **YML** files.

License
--------

    GNU GPL v3
    
    Copyright (c) 2018 Mani Kumar
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
