#ifndef __UIRICHEDIT_H__
#define __UIRICHEDIT_H__

#pragma once

namespace DuiLib {

class CTxtWinHost;

class DUILIB_API CRichEditUI : public CContainerUI, public IMessageFilterUI
{
public:
    CRichEditUI();
    ~CRichEditUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

    BOOL IsWantTab();
    void SetWantTab(BOOL bWantTab = TRUE);
    BOOL IsWantReturn();
    void SetWantReturn(BOOL bWantReturn = TRUE);
    BOOL IsWantCtrlReturn();
    void SetWantCtrlReturn(BOOL bWantCtrlReturn = TRUE);
    BOOL IsTransparent();
    void SetTransparent(BOOL bTransparent = TRUE);
    BOOL IsRich();
    void SetRich(BOOL bRich = TRUE);
    BOOL IsReadOnly();
    void SetReadOnly(BOOL bReadOnly = TRUE);
    BOOL IsWordWrap();
    void SetWordWrap(BOOL bWordWrap = TRUE);
    LONG GetFont();
    void SetFont(LONG index);
    void SetFont(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic);
    LONG GetWinStyle();
    void SetWinStyle(LONG lStyle);
    DWORD GetTextColor();
    void SetTextColor(DWORD dwTextColor);
    LONG GetLimitText();
    void SetLimitText(LONG iChars);
    LONG GetTextLength(DWORD dwFlags = GTL_DEFAULT) const;
    CDuiString GetText() const;
    void SetText(LPCTSTR pstrText);
    BOOL IsModify() const;
    void SetModify(BOOL bModified = TRUE) const;
    void GetSel(CHARRANGE &cr) const;
    void GetSel(LONG& nStartChar, LONG& nEndChar) const;
    LONG SetSel(CHARRANGE &cr);
    LONG SetSel(LONG nStartChar, LONG nEndChar);
    void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo);
    void ReplaceSelW(LPCWSTR lpszNewText, BOOL bCanUndo = FALSE);
    CDuiString GetSelText() const;
    LONG SetSelAll();
    LONG SetSelNone();
    WORD GetSelectionType() const;
    BOOL GetZoom(LONG& nNum, LONG& nDen) const;
    BOOL SetZoom(LONG nNum, LONG nDen);
    BOOL SetZoomOff();
    BOOL GetAutoURLDetect() const;
    BOOL SetAutoURLDetect(BOOL bAutoDetect = TRUE);
    DWORD GetEventMask() const;
    DWORD SetEventMask(DWORD dwEventMask);
    CDuiString GetTextRange(LONG nStartChar, LONG nEndChar) const;
    void HideSelection(BOOL bHide = TRUE, BOOL bChangeStyle = FALSE);
    void ScrollCaret();
    LONG InsertText(LONG nInsertAfterChar, LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
    LONG AppendText(LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
    DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;
    BOOL SetDefaultCharFormat(CHARFORMAT2 &cf);
    DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;
    BOOL SetSelectionCharFormat(CHARFORMAT2 &cf);
    BOOL SetWordCharFormat(CHARFORMAT2 &cf);
    DWORD GetParaFormat(PARAFORMAT2 &pf) const;
    BOOL SetParaFormat(PARAFORMAT2 &pf);
    BOOL Redo();
    BOOL Undo();
    void Clear();
    void Copy();
    void Cut();
    void Paste();
    LONG GetLineCount() const;
    CDuiString GetLine(LONG nIndex, LONG nMaxLength) const;
    LONG LineIndex(LONG nLine = -1) const;
    LONG LineLength(LONG nLine = -1) const;
    BOOL LineScroll(LONG nLines, LONG nChars = 0);
	CDuiPoint GetCharPos(LONG lChar) const;
    LONG LineFromChar(LONG nIndex) const;
    CDuiPoint PosFromChar(UINT nChar) const;
    LONG CharFromPos(CDuiPoint pt) const;
    void EmptyUndoBuffer();
    UINT SetUndoLimit(UINT nLimit);
    LONG StreamIn(LONG nFormat, EDITSTREAM &es);
    LONG StreamOut(LONG nFormat, EDITSTREAM &es);

	RECT GetTextPadding() const;
	void SetTextPadding(RECT rc);

    LRESULT DoInit();
	BOOL SetDropAcceptFile(BOOL bAccept);
	// 注意：TxSendMessage和SendMessage是有区别的，TxSendMessage没有multibyte和unicode自动转换的功能，
	// 而richedit2.0内部是以unicode实现的，在multibyte程序中，必须自己处理unicode到multibyte的转换
    virtual HRESULT TxSendMessage(UINT msg, WPARAM wparam, LPARAM lparam, LRESULT *plresult) const; 
    IDropTarget* GetTxDropTarget();
	virtual LRESULT OnTxViewChanged();
	virtual LRESULT OnTxNotify(DWORD iNotify, void *pv);

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

    SIZE EstimateSize(SIZE szAvailable);
	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
	LRESULT DoEvent(TEventUI& event);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& bHandled);

protected:
	enum { 
		DEFAULT_TIMERID = 20,
	};

    CTxtWinHost* m_pTwh;
    BOOL m_bVScrollBarFixing;
	BOOL m_bWantTab;
	BOOL m_bWantReturn;
	BOOL m_bWantCtrlReturn;
	BOOL m_bTransparent;
	BOOL m_bRich;
	BOOL m_bReadOnly;
	BOOL m_bWordWrap;
    DWORD m_dwTextColor;
    LONG m_iFont;
    LONG m_iLimitText;
    LONG m_lTwhStyle;
	BOOL m_bDrawCaret;
	BOOL m_bInited;
	RECT m_rcTextPadding;
};

} // namespace DuiLib

#endif // __UIRICHEDIT_H__
