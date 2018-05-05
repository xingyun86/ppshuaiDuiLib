#ifndef __UILIST_H__
#define __UILIST_H__

#pragma once
#include "Layout/UIVerticalLayout.h"
#include "Layout/UIHorizontalLayout.h"

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

typedef LONG (CALLBACK *PULVCompareFunc)(UINT_PTR, UINT_PTR, UINT_PTR);

class CListHeaderUI;

#define UILIST_MAX_COLUMNS 64

typedef struct tagTListInfoUI
{
    LONG nColumns;
    RECT rcColumn[UILIST_MAX_COLUMNS];
    UINT uFixedHeight; 
    LONG nFont;
    UINT uTextStyle;
    RECT rcTextPadding;
    DWORD dwTextColor;
    DWORD dwBkColor;
    TDrawInfo diBk;
    BOOL bAlternateBk;
    DWORD dwSelectedTextColor;
    DWORD dwSelectedBkColor;
    TDrawInfo diSelected;
    DWORD dwHotTextColor;
    DWORD dwHotBkColor;
    TDrawInfo diHot;
    DWORD dwDisabledTextColor;
    DWORD dwDisabledBkColor;
    TDrawInfo diDisabled;
    LONG iHLineSize;
    DWORD dwHLineColor;
    LONG iVLineSize;
    DWORD dwVLineColor;
    BOOL bShowHtml;
    BOOL bMultiExpandable;
} TListInfoUI;


/////////////////////////////////////////////////////////////////////////////////////
//

class IListCallbackUI
{
public:
    virtual LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) = 0;
};

class IListOwnerUI
{
public:
    virtual TListInfoUI* GetListInfo() = 0;
    virtual LONG GetCurSel() const = 0;
	virtual LRESULT SelectItem(LONG iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE) = 0;
	virtual LRESULT DoEvent(TEventUI& event) = 0;
	virtual LRESULT ExpandItem(LONG iIndex, BOOL bExpand = TRUE) = 0;
    virtual LONG GetExpandedItem() const = 0;
};

class IListUI : public IListOwnerUI
{
public:
    virtual CListHeaderUI* GetHeader() const = 0;
    virtual CContainerUI* GetList() const = 0;
    virtual IListCallbackUI* GetTextCallback() const = 0;
    virtual void SetTextCallback(IListCallbackUI* pCallback) = 0;
};

class IListItemUI
{
public:
    virtual LONG GetIndex() const = 0;
    virtual void SetIndex(int iIndex) = 0;
    virtual LONG GetDrawIndex() const = 0;
    virtual void SetDrawIndex(int iIndex) = 0;
    virtual IListOwnerUI* GetOwner() = 0;
    virtual void SetOwner(CControlUI* pOwner) = 0;
    virtual BOOL IsSelected() const = 0;
    virtual BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent=TRUE) = 0;
    virtual BOOL IsExpanded() const = 0;
    virtual BOOL Expand(BOOL bExpand = TRUE) = 0;
	virtual LRESULT DrawItemText(HDC hDC, const RECT& rcItem) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CListBodyUI;
class CListHeaderUI;

class DUILIB_API CListUI : public CVerticalLayoutUI, public IListUI
{
public:
    CListUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    BOOL GetScrollSelect();
    void SetScrollSelect(BOOL bScrollSelect);
    LONG GetCurSel() const;
	LRESULT SelectItem(LONG iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE);

    CControlUI* GetItemAt(int iIndex) const;
    LONG GetItemIndex(CControlUI* pControl) const;
    BOOL SetItemIndex(CControlUI* pControl, int iIndex);
    BOOL SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
    LONG GetCount() const;
	LRESULT Add(CControlUI* pControl);
	LRESULT AddAt(CControlUI* pControl, LONG iIndex);
	LRESULT Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAt(LONG iIndex, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAll();

    void EnsureVisible(int iIndex);
    void Scroll(int dx, int dy);

    LONG GetChildPadding() const;
	void SetChildPadding(LONG iPadding);

    CListHeaderUI* GetHeader() const;  
    CContainerUI* GetList() const;
    TListInfoUI* GetListInfo();

    UINT GetItemFixedHeight();
    void SetItemFixedHeight(UINT nHeight);
    int GetItemFont(int index);
    void SetItemFont(int index);
    UINT GetItemTextStyle();
    void SetItemTextStyle(UINT uStyle);
    RECT GetItemTextPadding() const;
    void SetItemTextPadding(RECT rc);
    DWORD GetItemTextColor() const;
    void SetItemTextColor(DWORD dwTextColor);
    DWORD GetItemBkColor() const;
    void SetItemBkColor(DWORD dwBkColor);
    LPCTSTR GetItemBkImage() const;
    void SetItemBkImage(LPCTSTR pStrImage);
    BOOL IsAlternateBk() const;
    void SetAlternateBk(BOOL bAlternateBk);
    DWORD GetSelectedItemTextColor() const;
    void SetSelectedItemTextColor(DWORD dwTextColor);
    DWORD GetSelectedItemBkColor() const;
    void SetSelectedItemBkColor(DWORD dwBkColor);
    LPCTSTR GetSelectedItemImage() const;
    void SetSelectedItemImage(LPCTSTR pStrImage);
    DWORD GetHotItemTextColor() const;
    void SetHotItemTextColor(DWORD dwTextColor);
    DWORD GetHotItemBkColor() const;
    void SetHotItemBkColor(DWORD dwBkColor);
    LPCTSTR GetHotItemImage() const;
    void SetHotItemImage(LPCTSTR pStrImage);
    DWORD GetDisabledItemTextColor() const;
    void SetDisabledItemTextColor(DWORD dwTextColor);
    DWORD GetDisabledItemBkColor() const;
    void SetDisabledItemBkColor(DWORD dwBkColor);
    LPCTSTR GetDisabledItemImage() const;
    void SetDisabledItemImage(LPCTSTR pStrImage);
    int GetItemHLineSize() const;
    void SetItemHLineSize(int iSize);
    DWORD GetItemHLineColor() const;
    void SetItemHLineColor(DWORD dwLineColor);
    int GetItemVLineSize() const;
    void SetItemVLineSize(int iSize);
    DWORD GetItemVLineColor() const;
    void SetItemVLineColor(DWORD dwLineColor);
    BOOL IsItemShowHtml();
    void SetItemShowHtml(BOOL bShowHtml = TRUE);

    void SetMultiExpanding(BOOL bMultiExpandable); 
    LONG GetExpandedItem() const;
	LRESULT ExpandItem(LONG iIndex, BOOL bExpand = TRUE);

	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = true);
	LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = true);
	LRESULT DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    IListCallbackUI* GetTextCallback() const;
    void SetTextCallback(IListCallbackUI* pCallback);

    SIZE GetScrollPos() const;
    SIZE GetScrollRange() const;
    void SetScrollPos(SIZE szPos);
    void LineUp();
    void LineDown();
    void PageUp();
    void PageDown();
    void HomeUp();
    void EndDown();
    void LineLeft();
    void LineRight();
    void PageLeft();
    void PageRight();
    void HomeLeft();
    void EndRight();
    void EnableScrollBar(BOOL bEnableVertical = TRUE, BOOL bEnableHorizontal = FALSE);
    virtual CScrollBarUI* GetVerticalScrollBar() const;
    virtual CScrollBarUI* GetHorizontalScrollBar() const;
    BOOL SortItems(PULVCompareFunc pfnCompare, UINT_PTR dwData);

protected:
    BOOL m_bScrollSelect;
    LONG m_iCurSel;
    LONG m_iExpandedItem;
    IListCallbackUI* m_pCallback;
    CListBodyUI* m_pList;
    CListHeaderUI* m_pHeader;
    TListInfoUI m_ListInfo;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListHeaderUI : public CHorizontalLayoutUI
{
public:
    CListHeaderUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    SIZE EstimateSize(SIZE szAvailable);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListHeaderItemUI : public CControlUI
{
public:
    CListHeaderItemUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

    void SetEnabled(BOOL bEnable = true);

	BOOL IsDragable() const;
    void SetDragable(BOOL bDragable);
	DWORD GetSepWidth() const;
    void SetSepWidth(int iWidth);
	DWORD GetTextStyle() const;
    void SetTextStyle(UINT uStyle);
	DWORD GetTextColor() const;
    void SetTextColor(DWORD dwTextColor);
    DWORD GetSepColor() const;
    void SetSepColor(DWORD dwSepColor);
	void SetTextPadding(RECT rc);
	RECT GetTextPadding() const;
    void SetFont(LONG index);
    BOOL IsShowHtml();
    void SetShowHtml(BOOL bShowHtml = true);
    LPCTSTR GetNormalImage() const;
    void SetNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetHotImage() const;
    void SetHotImage(LPCTSTR pStrImage);
    LPCTSTR GetPushedImage() const;
    void SetPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetFocusedImage() const;
    void SetFocusedImage(LPCTSTR pStrImage);
    LPCTSTR GetSepImage() const;
    void SetSepImage(LPCTSTR pStrImage);

	LRESULT DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    RECT GetThumbRect() const;

	LRESULT PaintText(HDC hDC);
	LRESULT PaintStatusImage(HDC hDC);

protected:
    POINT ptLastMouse;
    BOOL m_bDragable;
    UINT m_uButtonState;
    LONG m_iSepWidth;
    DWORD m_dwTextColor;
    DWORD m_dwSepColor;
    LONG m_iFont;
    UINT m_uTextStyle;
    BOOL m_bShowHtml;
	RECT m_rcTextPadding;
    TDrawInfo m_diNormal;
    TDrawInfo m_diHot;
    TDrawInfo m_diPushed;
    TDrawInfo m_diFocused;
    TDrawInfo m_diSep;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListElementUI : public CControlUI, public IListItemUI
{
public:
    CListElementUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetEnabled(BOOL bEnable = TRUE);

    LONG GetIndex() const;
    void SetIndex(int iIndex);
    LONG GetDrawIndex() const;
    void SetDrawIndex(int iIndex);

    IListOwnerUI* GetOwner();
    void SetOwner(CControlUI* pOwner);
    void SetVisible(BOOL bVisible = TRUE);

    BOOL IsSelected() const;
    BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent=TRUE);
    BOOL IsExpanded() const;
    BOOL Expand(BOOL bExpand = TRUE);

	LRESULT Invalidate(); // 直接CControl::Invalidate会导致滚动条刷新，重写减少刷新区域
    BOOL Activate();

	LRESULT DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	LRESULT DrawItemBk(HDC hDC, const RECT& rcItem);

protected:
    LONG m_iIndex;
    LONG m_iDrawIndex;
    BOOL m_bSelected;
    UINT m_uButtonState;
    IListOwnerUI* m_pOwner;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListLabelElementUI : public CListElementUI
{
public:
    CListLabelElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetOwner(CControlUI* pOwner);

    void SetFixedWidth(int cx);
    void SetFixedHeight(int cy);
    void SetText(LPCTSTR pstrText);

	LRESULT DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

	LRESULT DrawItemText(HDC hDC, const RECT& rcItem);

protected:
    SIZE    m_cxyFixedLast;
    BOOL    m_bNeedEstimateSize;

    SIZE    m_szAvailableLast;
    UINT    m_uFixedHeightLast; 
    LONG     m_nFontLast;
    UINT    m_uTextStyleLast;
    RECT    m_rcTextPaddingLast;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListTextElementUI : public CListLabelElementUI
{
public:
    CListTextElementUI();
    ~CListTextElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

	LPCTSTR GetText(int iIndex) const;
	void SetText(int iIndex, LPCTSTR pstrText);

	HICON GetIcon(int iIndex) const;
	void SetIcon(int iIndex, HICON hIcon);

    void SetOwner(CControlUI* pOwner);
    CDuiString* GetLinkContent(int iIndex);

	LRESULT DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);

	LRESULT DrawItemText(HDC hDC, const RECT& rcItem);

protected:
    enum { MAX_LINK = 8 };
    int m_nLinks;
    RECT m_rcLinks[MAX_LINK];
    CDuiString m_sLinks[MAX_LINK];
    int m_nHoverLink;
    IListUI* m_pOwner;
    CDuiPtrArray m_aTexts;
	CDuiPtrArray m_aIcons;
    CDuiString m_sTextLast;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListContainerElementUI : public CContainerUI, public IListItemUI
{
public:
    CListContainerElementUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    LONG GetIndex() const;
    void SetIndex(int iIndex);
    LONG GetDrawIndex() const;
    void SetDrawIndex(int iIndex);

    IListOwnerUI* GetOwner();
    void SetOwner(CControlUI* pOwner);
    void SetVisible(BOOL bVisible = TRUE);
    void SetEnabled(BOOL bEnable = TRUE);

    BOOL IsSelected() const;
    BOOL Select(BOOL bSelect = TRUE, BOOL bTriggerEvent=TRUE);
    BOOL IsExpandable() const;
    void SetExpandable(BOOL bExpandable);
    BOOL IsExpanded() const;
    BOOL Expand(BOOL bExpand = TRUE);

    void Invalidate(); // 直接CControl::Invalidate会导致滚动条刷新，重写减少刷新区域
    BOOL Activate();

	LRESULT DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

	LRESULT DrawItemText(HDC hDC, const RECT& rcItem);
	LRESULT DrawItemBk(HDC hDC, const RECT& rcItem);

    SIZE EstimateSize(SIZE szAvailable);

protected:
    int m_iIndex;
    int m_iDrawIndex;
    BOOL m_bSelected;
    BOOL m_bExpandable;
    BOOL m_bExpand;
    UINT m_uButtonState;
    IListOwnerUI* m_pOwner;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CListHBoxElementUI : public CListContainerElementUI
{
public:
    CListHBoxElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
};

} // namespace DuiLib

#endif // __UILIST_H__
