#ifndef __UIACTIVEX_H__
#define __UIACTIVEX_H__

#pragma once

struct IOleObject;


namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CActiveXCtrl;

template< class T >
class CSafeRelease
{
public:
    CSafeRelease(T* p) : m_p(p) { };
    ~CSafeRelease() { if ( m_p != NULL ) m_p->Release(); };
    T* Detach() { T* t = m_p; m_p = NULL; return t; };
    T* m_p;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CActiveXUI : public CControlUI, public IMessageFilterUI
{
    friend class CActiveXCtrl;
public:
    CActiveXUI();
    virtual ~CActiveXUI();

	LPCTSTR GetClass() CONST;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() CONST;
	HWND GetNativeWindow() CONST;

	BOOL IsDelayCreate() CONST;
    void SetDelayCreate(BOOL bDelayCreate = TRUE);

	LRESULT CreateControl(CONST CLSID clsid);
	LRESULT CreateControl(LPCTSTR pstrCLSID);
	HRESULT GetControl(CONST IID iid, LPVOID* ppRet);
	CLSID GetClisd() CONST;
	CDuiString GetModuleName() CONST;
    void SetModuleName(LPCTSTR pstrText);

    void SetVisible(BOOL bVisible = TRUE);
	void SetInternVisible(BOOL bVisible = TRUE);
	LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
	LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& bHandled);

protected:
	virtual LRESULT ReleaseControl();
	virtual LRESULT DoCreateControl();

protected:
    CLSID m_clsid;
    CDuiString m_sModuleName;
    BOOL m_bCreated;
    BOOL m_bDelayCreate;
    IOleObject* m_pUnk;
    CActiveXCtrl* m_pControl;
    HWND m_hwndHost;
};

} // namespace DuiLib

#endif // __UIACTIVEX_H__
