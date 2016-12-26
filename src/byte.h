#ifndef BYTE_H
#define BYTE_H

#include <cstdlib>
typedef unsigned char uch;
typedef unsigned short ush;
struct Byte
{
    int length;
    uch *a;
    Byte(int _length = 0, uch *_a = NULL)
    {
        length = _length;
        a = _a;
    }
};

#endif
