#ifndef __UICOMBO_H__
#define __UICOMBO_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CComboWnd;

class DUILIB_API CComboUI : public CContainerUI, public IListOwnerUI
{
    friend class CComboWnd;
public:
    CComboUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	LRESULT DoInit();
    UINT GetControlFlags() const;

    CDuiString GetText() const;
    void SetEnabled(BOOL bEnable = TRUE);

    CDuiString GetDropBoxAttributeList();
    void SetDropBoxAttributeList(LPCTSTR pstrList);
    SIZE GetDropBoxSize() const;
    void SetDropBoxSize(SIZE szDropBox);

    LONG GetCurSel() const;
	BOOL GetSelectCloseFlag();
	void SetSelectCloseFlag(BOOL flag);
	LRESULT SelectItem(LONG iIndex, BOOL bTakeFocus = FALSE, BOOL bTriggerEvent = TRUE);
	LRESULT ExpandItem(LONG iIndex, BOOL bExpand = TRUE);
	LONG GetExpandedItem() const;

	LRESULT SetItemIndex(CControlUI* pControl, int iNewIndex);
	LRESULT SetMultiItemIndex(CControlUI* pStartControl, int iCount, int iNewStartIndex);
	LRESULT Add(CControlUI* pControl);
	LRESULT AddAt(CControlUI* pControl, int iIndex);
	LRESULT Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAt(LONG iIndex, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAll();

    BOOL Activate();

	BOOL GetShowTextStatus() const;
	void SetShowTextStatus(BOOL flag);
    RECT GetTextPadding() const;
    void SetTextPadding(RECT rc);
    LPCTSTR GetNormalImage() const;
    void SetNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetHotImage() const;
    void SetHotImage(LPCTSTR pStrImage);
    LPCTSTR GetPushedImage() const;
    void SetPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetFocusedImage() const;
    void SetFocusedImage(LPCTSTR pStrImage);
    LPCTSTR GetDisabledImage() const;
    void SetDisabledImage(LPCTSTR pStrImage);

    TListInfoUI* GetListInfo();
    UINT GetItemFixedHeight();
    void SetItemFixedHeight(UINT nHeight);
    long GetItemFont(int index);
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
    long GetItemVLineSize() const;
    void SetItemVLineSize(int iSize);
	DWORD GetItemVLineColor() const;
    void SetItemVLineColor(DWORD dwLineColor);
    BOOL IsItemShowHtml();
    void SetItemShowHtml(BOOL bShowHtml = TRUE);

    SIZE EstimateSize(SIZE szAvailable);
	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
	LRESULT DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
	LRESULT PaintText(HDC hDC);
	LRESULT PaintStatusImage(HDC hDC);

protected:
    CComboWnd* m_pWindow;

    LONG m_iCurSel;
	BOOL m_bShowText;
	BOOL m_bSelectCloseFlag;
    RECT m_rcTextPadding;
    CDuiString m_sDropBoxAttributes;
    SIZE m_szDropBox;
    UINT m_uButtonState;

	TDrawInfo m_diNormal;
    TDrawInfo m_diHot;
    TDrawInfo m_diPushed;
    TDrawInfo m_diFocused;
    TDrawInfo m_diDisabled;

    TListInfoUI m_ListInfo;
};

} // namespace DuiLib

#endif // __UICOMBO_H__
