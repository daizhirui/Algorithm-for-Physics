# Structure Compare
### based on orthogonal transformation

## Install
```
mkdir -p build lib
cmake ./
make
```
The binary is installed in build and the library is in lib.

## Option
```
Molecule Structure Mean Difference Program
  Usage:
    LONG OPTION    SHORT   DEFAULT        DESCRIPTION
    --help            -h                  Print this usage
    --auto_pair       -a   0              Auto pair the atoms of two molecules
    --molecule_data   -m   molecule.json  The file store positions of molecules' atoms
    --output          -o   result.txt     The file to store the result
```

## Features
- This program uses JSON as the format of input file
    - JSON is a kind of file easy to modified and read with a friendly style
- This program can automatically pair atoms between two molecules when auto_pair is set 1.
- The result is not only stored in the specific file but also showed on the screen