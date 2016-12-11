#ifndef TYPE_H
#define TYPE_H
#include "byte.h"
#include <cstring>
#include <cstdio>

class Type
{
public:
    enum SizeType
    {
        sta = 0,
        var
    } sizeType;
    bool null;
    virtual Byte toByte() = 0;
    virtual void fromByte(Byte byte) = 0;
    virtual int getSize() = 0;
    virtual void print() = 0;
    Type(SizeType _sizeType, bool _null)
        : sizeType(_sizeType), null(_null)
    {
    }
};

//class Type_tinyint : public Type
//{
//private:
//    int value;
//public:
//    Type_tinyint(bool _null = true, int t = 0)
//        : Type(Type::sta, _null), value(t)
//    {
//    }
//    int getSize()
//    {
//        return sizeof(char) / sizeof(uch);
//    }

//    Byte toByte()
//    {
//        if (null) value = 0;

//        return Byte(sizeof(char) / sizeof(uch), (uch *)&value);
//    }
//    void fromByte(Byte byte)
//    {
//        value = *(int *)byte.a;
//    }
//    void print()
//    {
//        if (null)printf("%d ", 0);
//        else printf("%d ", value);
//    }

//    int getValue()
//    {
//        return value;
//    }
//    void setValue(int t)
//    {
//        value = t;
//    }

//    bool operator < (const Type_tinyint &t) const
//    {
//        if (null && t.null)return false;

//        if (null != t.null)return null < t.null;

//        return value < t.value;
//    }

//    bool operator == (const Type_tinyint &t) const
//    {
//        if (null && t.null) return true;

//        return value == t.value;
//    }
//};

class Type_int : public Type
{
private:
    int value, len;
public:
    Type_int(bool _null = true, int t = 0, int _len = -1)
        : Type(Type::sta, _null), value(t), len(_len)
    {
    }
    int getSize()
    {
        return sizeof(int) / sizeof(uch);
    }

    Byte toByte()
    {
        if (null) value = 0;

        return Byte(sizeof(int) / sizeof(uch), (uch *)&value);
    }
    void fromByte(Byte byte)
    {
        value = *(int *)byte.a;
    }
    void print()
    {
        char buf[16];
        if(len == -1)sprintf(buf, "| %%d | ");else sprintf(buf, "| %%0%dd | ", len);
        if (null)printf(buf, 0);
        else printf(buf, value);
    }

    int getValue()
    {
        return value;
    }
    void setValue(int t)
    {
        value = t;
    }

    bool operator < (const Type_int &t) const
    {
        if (null && t.null)return false;

        if (null != t.null)return null < t.null;

        return value < t.value;
    }

    bool operator == (const Type_int &t) const
    {
        if (null && t.null) return true;

        return value == t.value;
    }
};

template<int size = 64>
class Type_varchar : public Type
{
private:
    char str[size + 1];
    int length;
public:
    Type_varchar(bool _null = true, const char *_str = "", int _length = 0)
        : Type(Type::var, _null)
    {
        memset(str, 0, sizeof(char)*size);
        length = _length;
        memcpy(str, _str, length * sizeof(char));
        str[length] = '\000';
    }
    ~Type_varchar()
    {
    }

    int getSize()
    {
        return null ? 0 : length;
    }

    Byte toByte()
    {
        return Byte(null ? 0 : length, (uch *)str);
    }
    void fromByte(Byte byte)
    {
        memset(str, 0, sizeof(char)*size);
        const char *_str = (char *)byte.a;
        length = byte.length;
        memcpy(str, _str, length * sizeof(char));
        str[length] = '\000';
    }
    void print()
    {
        if (!null)printf("| %s | ", str);
        else printf("|  | ");
    }
    const char *getStr()
    {
        return str;
    }
    void setStr(const char *_str, int _length)
    {
        memset(str, 0, sizeof(char)*size);
        length = _length;
        memcpy(str, _str, length * sizeof(char));
        str[length] = '\000';
    }
    bool operator < (const Type_varchar &t) const
    {
        if (null && t.null)return false;

        if (null != t.null)return null < t.null;

        return strcmp(str, t.str) < 0;
    }

    bool operator == (const Type_varchar &t) const
    {
        if (null && t.null) return true;

        return strcmp(str, t.str) == 0;
    }
};

#endif
