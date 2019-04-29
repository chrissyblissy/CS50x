# Questions

## What's `stdint.h`?

A header file that defines how many bits a certain integer will be made of.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

You can set the exact size of a structure.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

66 77

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the whole bitmap file, biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If \'biHeight\' is negative then the origin of the bitmap is in the upper-left corner and the bitmap works from the top down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file does not exist then fopen will return NULL

## Why is the third argument to `fread` always `1` in our code?

Because there is only 1 Header file at the start of each bitmap file.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

-1

## What does `fseek` do?

fseek offsets the position of the stream to skip over any padding in the file.

## What is `SEEK_CUR`?

\'SEEK_CUR\' is the current position of the file pointer in the file.

## Whodunit?

It was Professor Plum with the candlestick in the library.
