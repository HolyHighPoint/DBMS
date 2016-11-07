#ifndef RC_H
#define RC_H
enum RC
{
    Success = 0,
    Error
};
struct RID
{
    int pageId, rowId;
    RID(int _pageId = 0, int _rowId = 0)
    {
        pageId = _pageId;
        rowId = _rowId;
    }
    bool operator < (const RID &a)
    {
        if(pageId == a.pageId)return rowId < a.rowId;else return rowId < a.rowId;
    }
};
#endif
