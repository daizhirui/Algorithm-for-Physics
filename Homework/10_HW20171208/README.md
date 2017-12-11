# Molecule System Interface

## Install
```
mkdir -p build lib
cmake ./
make
```
The binary is installed in build and the library is in lib.

## Option
```
Interface of Molecule System
  Usage:
    LONG OPTION  SHORT   DEFAULT     DESCRIPTION
    --help       -h                  Print this usage
    --input      -i      1COA.pdb    The file to read in
    --output     -o      result.txt  The file to store the result
```

## Function
- Output the atom group list, including group name, group number, group mass and group position
- Output the interaction list, including 3 types: HAR, LJ and REP


