#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class IContainerUI
{
public:
    virtual CControlUI* GetItemAt(LONG iIndex) const = 0;
    virtual LONG GetItemIndex(CControlUI* pControl) const  = 0;
	virtual LRESULT SetItemIndex(CControlUI* pControl, LONG iNewIndex) = 0;
	virtual LRESULT SetMultiItemIndex(CControlUI* pStartControl, LONG iCount, LONG iNewStartIndex) = 0;
    virtual LONG GetCount() const = 0;
	virtual LRESULT Add(CControlUI* pControl) = 0;
	virtual LRESULT AddAt(CControlUI* pControl, LONG iIndex) = 0;
	virtual LRESULT Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE) = 0;
	virtual LRESULT RemoveAt(LONG iIndex, BOOL bDoNotDestroy = FALSE) = 0;
	virtual LRESULT RemoveAll() = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
class CScrollBarUI;

class DUILIB_API CContainerUI : public CControlUI, public IContainerUI
{
public:
    CContainerUI();
    virtual ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	CControlUI* GetItemAt(LONG iIndex) const;
	LONG GetItemIndex(CControlUI* pControl) const;
	LRESULT SetItemIndex(CControlUI* pControl, LONG iNewIndex);
	LRESULT SetMultiItemIndex(CControlUI* pStartControl, LONG iCount, LONG iNewStartIndex);
	LONG GetCount() const;
	LRESULT Add(CControlUI* pControl);
	LRESULT AddAt(CControlUI* pControl, LONG iIndex);
	LRESULT Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAt(LONG iIndex, BOOL bDoNotDestroy = FALSE);
	LRESULT RemoveAll();

	LRESULT DoEvent(TEventUI& event);
	void SetVisible(BOOL bVisible = TRUE);
	void SetInternVisible(BOOL bVisible = TRUE);
	void SetMouseEnabled(BOOL bEnable = TRUE);

    virtual RECT GetInset() const;
    virtual void SetInset(RECT rcInset); // 设置内边距，相当于设置客户区
    virtual LONG GetChildPadding() const;
    virtual void SetChildPadding(LONG iPadding);
	virtual UINT GetChildAlign() const;
	virtual void SetChildAlign(UINT iAlign);
	virtual UINT GetChildVAlign() const;
	virtual void SetChildVAlign(UINT iVAlign);
    virtual BOOL IsAutoDestroy() const;
    virtual void SetAutoDestroy(BOOL bAuto);
    virtual BOOL IsDelayedDestroy() const;
    virtual void SetDelayedDestroy(BOOL bDelayed);
    virtual BOOL IsMouseChildEnabled() const;
    virtual void SetMouseChildEnabled(BOOL bEnable = TRUE);

	virtual LONG FindSelectable(LONG iIndex, BOOL bForward = TRUE) const;

	RECT GetClientPos() const;
	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);
    CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	BOOL SetSubControlText(LPCTSTR pstrSubControlName, LPCTSTR pstrText);
	BOOL SetSubControlFixedHeight(LPCTSTR pstrSubControlName, LONG cy);
	BOOL SetSubControlFixedWdith(LPCTSTR pstrSubControlName, LONG cx);
	BOOL SetSubControlUserData(LPCTSTR pstrSubControlName, LPCTSTR pstrText);

	CDuiString GetSubControlText(LPCTSTR pstrSubControlName);
	LONG GetSubControlFixedHeight(LPCTSTR pstrSubControlName);
	LONG GetSubControlFixedWdith(LPCTSTR pstrSubControlName);
	const CDuiString GetSubControlUserData(LPCTSTR pstrSubControlName);
	CControlUI* FindSubControl(LPCTSTR pstrSubControlName);

    virtual SIZE GetScrollPos() const;
    virtual SIZE GetScrollRange() const;
    virtual void SetScrollPos(SIZE szPos);
    virtual void LineUp();
    virtual void LineDown();
    virtual void PageUp();
    virtual void PageDown();
    virtual void HomeUp();
    virtual void EndDown();
    virtual void LineLeft();
    virtual void LineRight();
    virtual void PageLeft();
    virtual void PageRight();
    virtual void HomeLeft();
    virtual void EndRight();
    virtual void EnableScrollBar(BOOL bEnableVertical = TRUE, BOOL bEnableHorizontal = TRUE);
    virtual CScrollBarUI* GetVerticalScrollBar() const;
    virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
    virtual void SetFloatPos(LONG iIndex);
	virtual void ProcessScrollBar(RECT rc, LONG cxRequired, LONG cyRequired);

protected:
    CDuiPtrArray m_items;
    RECT m_rcInset;
	LONG m_iChildPadding;
	UINT m_iChildAlign;
	UINT m_iChildVAlign;
    BOOL m_bAutoDestroy;
    BOOL m_bDelayedDestroy;
    BOOL m_bMouseChildEnabled;
    BOOL m_bScrollProcess; // 防止SetPos循环调用

    CScrollBarUI* m_pVerticalScrollBar;
    CScrollBarUI* m_pHorizontalScrollBar;
};

} // namespace DuiLib

#endif // __UICONTAINER_H__
