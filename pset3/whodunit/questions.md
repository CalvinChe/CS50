# Questions

## What's `stdint.h`?

<stdint.h> allows the declaration of integer types with specified widths, where the width of the integer is the number of bits used to store its value in a pure binary system.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It allows us to set an unsigned integer type with width N. Since if the author knows they will never have a negative number using unsigned ints is ideal since we have more bits to work with.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

There is 1 byte in a BYTE, 4 bytes in a DWORD, 4 bytes in a LONG, and 2 bytes in a 'WORD'.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes in any BMP file is the bfType variable inside the tagBITMAPFILEHEADER. 0x42 0x4D in hexadecimal.

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the bitmap file whereas, biSize stores the information to locate the color table in a BITMAPINFO structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative it indicates a top-down DIB and its origin is the upper left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies the number of bits-per-pixel. biBitCount determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in `copy.c`?

If fopen is unsuccessful in opening a FILE object a NULL pointer is returned.

## Why is the third argument to `fread` always `1` in our code?

Because we only have to read one the header once.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

```C
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
```

Since the sizeof RDBtriple is 3 bytes then you would get a padding of 3.

## What does `fseek` do?

**fSeek** repositions the indicator associated with stream. So you can do things as go back to the beginning of the file, go to the end of the file or move where you're looking slightly forward or backwards.

## What is `SEEK_CUR`?

**SEEK_CUR** is the current position of the file pointer.