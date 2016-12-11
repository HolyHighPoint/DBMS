#ifndef RM_RECORD_H
#define RM_RECORD_H
#include "rc.h"
#include <vector>
#include "type.h"
#include <cstdio>
#include <bitset>
#include <typeinfo>
class RM_Record
{
private:
    std::vector<Type *> sta, var, total;
public:
    void push_back(Type *value)
    {
        if (value->sizeType == value->sta)sta.push_back(value);
        else var.push_back(value);

        total.push_back(value);
    }
    void clear()
    {
        for (auto const & i : total)
        {
            delete i;
        }
    }
    Type * get(int n)
    {
        return total[n];
    }

    Byte toByte() const
    {
        Byte byte;
        static std::vector<uch> data;
        data.clear();
        uch TagA = (1 << 4) | (var.size() ? (1 << 5) : 0);
        data.push_back(TagA);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);

        for (int i = 0; i < sta.size(); i++)
        {
            Byte byte = sta[i]->toByte();

            for (int i = 0; i < byte.length; i++)
                data.push_back(byte.a[i]);
        }

        unsigned short t = data.size();
        data[2] = *(uch *)&t;
        data[3] = *(((uch *)&t) + 1);
        t = total.size();
        data.push_back(*(uch *)&t);
        data.push_back(*(((uch *)&t) + 1));
        std::vector<std::bitset<8> >null((t + 7) / 8);

        for (int i = 0; i < total.size(); i++)
        {
            null[i / 8].set(i % 8, total[i]->null);
        }

        for (int i = 0; i < null.size(); i++)
            data.push_back(uch(null[i].to_ulong()));

        t = var.size();

        if (!t)
        {
            byte.length = data.size();
            byte.a = data.data();
            return byte;
        }

        data.push_back(*(uch *)&t);
        data.push_back(*(((uch *)&t) + 1));
        int start = data.size();

        for (int i = 0; i < var.size(); i++)
        {
            data.push_back(0);
            data.push_back(0);
        }

        for (int i = 0; i < var.size(); i++)
        {
            Byte byte = var[i]->toByte();

            for (int j = 0; j < byte.length; j++)
                data.push_back(byte.a[j]);

            int t = data.size() - 1;
            data[start + i * 2] = *(uch *)&t;
            data[start + i * 2 + 1] = *(((uch *)&t) + 1);
        }

        byte.length = data.size();
        byte.a = data.data();
        return byte;
    }

    RC fromByte(Byte _byte)
    {
        Byte byte = _byte;
        uch TagA = (1 << 4) | (var.size() ? (1 << 5) : 0);

        if (byte.a[0] != TagA) return Error;

        unsigned short t = *(ush *)&byte.a[2];
        int start = 4;

        for (int i = 0; i < sta.size(); i++)
        {
            Byte b(sta[i]->getSize(), byte.a + start);
            sta[i]->fromByte(b);
            start += sta[i]->getSize();
        }

        if (t != start) return Error;

        t = *(ush *)&byte.a[start];

        if (t != total.size()) return Error;

        start += 2;
        std::vector<std::bitset<8> >null((t + 7) / 8);

        for (int i = 0; i < null.size(); i++, start++)null[i] = std::bitset<8>(byte.a[start]);

        for (int i = 0; i < total.size(); i++)
        {
            total[i]->null = null[i / 8][i % 8];
        }

        t = *(ush *)&byte.a[start];

        if (t != var.size()) return Error;

        start += 2;

        for (int i = 0, pre = start + var.size() * 2; i < var.size(); i++)
        {
            t = *(ush *)&byte.a[start + i * 2];
            var[i]->fromByte(Byte(t - pre + 1, byte.a + pre));
            pre = t + 1;
        }

        if (t != byte.length) return Error;

        return Success;
    }
    void print()
    {
        for (auto const & i : total)
        {
            //printf("%s: ", typeid(*i).name());
            i->print();
            //printf("\n");
        }

        //printf("\n");
    }
};
#endif
