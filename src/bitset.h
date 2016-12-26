#ifndef BYTE_H
#define BYTE_H

typedef unsigned char uch;
struct Byte
{
    int length;
    unsigned char *a;
    Byte(_length = 0, _a = NULL)
    {
        length = _length;
        a = _a;
    }
};

#endif
