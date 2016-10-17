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
    RID(int _pageId=0, int _rowId=0)
    {
        pageId = _pageId;
        rowId = _rowId;
    }
};
#endif
