# [resize.c](https://github.com/CalvinChe/CS50/blob/master/pset3/resize/resize.c)
A program called resize that resizes (i.e., enlarges or shrinks) 24-bit uncompressed BMPs by a factor of a float f.

## Specification
1. The program should accept exactly 3 command-line arguments

2. The first argument ,f , must be a floating-point value in the range [0.0, 100.0]

3. The second argument must be the name of a BMP to be resized.

4. The third argument must be the name of the resized version to be written.

5. If your program is not executed with such, it should remind the user of the correct usage, as with print, and main should return 1;

6. If your program uses malloc, it must not leak any memory.

## Usage 
```shell
$ ./resize
Usage: ./resize f infile outfile
$ echo $?
1
```
```shell
$ ./resize .5 large.bmp smaller.bmp 
$ echo $?
0
```
```shell
$ ./resize 2 small.bmp larger.bmp
$ echo$?
0
```