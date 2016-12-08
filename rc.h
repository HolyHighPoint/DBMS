#ifndef RC_H
#define RC_H
enum RC
{
    Success = 0,
    Error
};

const char *configFile = "config.db";

struct RID
{
    int pageId, rowId;
    RID(int _pageId = 0, int _rowId = 0)
    {
        pageId = _pageId;
        rowId = _rowId;
    }
    bool operator < (const RID &a) const
    {
        if (pageId == a.pageId)return rowId < a.rowId;
        else return pageId < a.pageId;
    }

    bool operator == (const RID &a) const
    {
        return (pageId == a.pageId) && (rowId == a.rowId);
    }

    bool operator != (const RID &a) const
    {
        return !(*this == a);
    }

};
#endif
