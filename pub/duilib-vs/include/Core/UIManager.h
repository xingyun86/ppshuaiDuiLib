#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CControlUI;


/////////////////////////////////////////////////////////////////////////////////////
//

typedef enum EVENTTYPE_UI
{
    UIEVENT__FIRST = 1,
    UIEVENT__KEYBEGIN,
    UIEVENT_KEYDOWN,
    UIEVENT_KEYUP,
    UIEVENT_CHAR,
    UIEVENT_SYSKEY,
    UIEVENT__KEYEND,
    UIEVENT__MOUSEBEGIN,
    UIEVENT_MOUSEMOVE,
    UIEVENT_MOUSELEAVE,
    UIEVENT_MOUSEENTER,
    UIEVENT_MOUSEHOVER,
    UIEVENT_BUTTONDOWN,
    UIEVENT_BUTTONUP,
    UIEVENT_RBUTTONDOWN,
    UIEVENT_DBLCLICK,
    UIEVENT_CONTEXTMENU,
    UIEVENT_SCROLLWHEEL,
    UIEVENT__MOUSEEND,
    UIEVENT_KILLFOCUS,
    UIEVENT_SETFOCUS,
    UIEVENT_WINDOWSIZE,
    UIEVENT_SETCURSOR,
    UIEVENT_TIMER,
    UIEVENT_NOTIFY,
    UIEVENT_COMMAND,
    UIEVENT__LAST,
};

/////////////////////////////////////////////////////////////////////////////////////
//

// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_UPDATETEST    0x00000008
#define UIFIND_TOP_FIRST     0x00000010
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040



/////////////////////////////////////////////////////////////////////////////////////
//

typedef struct DUILIB_API tagTFontInfo
{
    HFONT hFont;
    CDuiString sFontName;
    int iSize;
	BOOL bBold;
	BOOL bUnderline;
	BOOL bItalic;
    TEXTMETRIC tm;
} TFontInfo;

typedef struct DUILIB_API tagTImageInfo
{
    HBITMAP hBitmap;
    LPBYTE pBits;
	LPBYTE pSrcBits;
    LONG nX;
    LONG nY;
	BOOL bAlpha;
	BOOL bUseHSL;
    CDuiString sResType;
    DWORD dwMask;
} TImageInfo;

typedef struct DUILIB_API tagTDrawInfo
{
	tagTDrawInfo();
	tagTDrawInfo(LPCTSTR lpsz);
	void Clear();
	CDuiString sDrawString;
    CDuiString sImageName;
	BOOL bLoaded;
	const TImageInfo* pImageInfo;
	RECT rcDestOffset;
	RECT rcBmpPart;
	RECT rcScale9;
	BYTE uFade;
	BOOL bHole;
	BOOL bTiledX;
	BOOL bTiledY;
} TDrawInfo;

typedef struct DUILIB_API tagTPercentInfo
{
	double left;
	double top;
	double right;
	double bottom;
} TPercentInfo;

typedef struct DUILIB_API tagTResInfo
{
	DWORD m_dwDefaultDisabledColor;
	DWORD m_dwDefaultFontColor;
	DWORD m_dwDefaultLinkFontColor;
	DWORD m_dwDefaultLinkHoverFontColor;
	DWORD m_dwDefaultSelectedBkColor;
	TFontInfo m_DefaultFontInfo;
	CDuiStringPtrMap m_CustomFonts;
	CDuiStringPtrMap m_ImageHash;
	CDuiStringPtrMap m_AttrHash;
	CDuiStringPtrMap m_MultiLanguageHash;
} TResInfo;

// Structure for notifications from the system
// to the control implementation.
typedef struct DUILIB_API tagTEventUI
{
    LONG Type;
    CControlUI* pSender;
    DWORD dwTimestamp;
    POINT ptMouse;
    TCHAR chKey;
    WORD wKeyState;
    WPARAM wParam;
    LPARAM lParam;
} TEventUI;

// Listener interface
class DUILIB_API INotifyUI
{
public:
	virtual LRESULT Notify(TNotifyUI& msg) = 0;
};

// MessageFilter interface
class DUILIB_API IMessageFilterUI
{
public:
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& bHandled) = 0;
};

class DUILIB_API ITranslateAccelerator
{
public:
	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);


class DUILIB_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

public:
    LRESULT Init(HWND hWnd, LPCTSTR pstrName = NULL);
	BOOL IsUpdateNeeded() const;
	LRESULT NeedUpdate();
	LRESULT Invalidate();
	LRESULT Invalidate(RECT& rcItem);

	LPCTSTR GetName() const;
    HDC GetPaintDC() const;
	HBITMAP GetPaintOffscreenBitmap();
    HWND GetPaintWindow() const;
    HWND GetTooltipWindow() const;
	int GetTooltipWindowWidth() const;
	void SetTooltipWindowWidth(int iWidth);
	int GetHoverTime() const;
	void SetHoverTime(int iTime);

    POINT GetMousePos() const;
    SIZE GetClientSize() const;
    SIZE GetInitSize();
    void SetInitSize(int cx, int cy);
    RECT& GetSizeBox();
    void SetSizeBox(RECT& rcSizeBox);
    RECT& GetCaptionRect();
    void SetCaptionRect(RECT& rcCaption);
    SIZE GetRoundCorner() const;
    void SetRoundCorner(int cx, int cy);
    SIZE GetMinInfo() const;
    void SetMinInfo(int cx, int cy);
    SIZE GetMaxInfo() const;
    void SetMaxInfo(int cx, int cy);
	BOOL IsShowUpdateRect() const;
	void SetShowUpdateRect(BOOL show);
	BOOL IsNoActivate();
	void SetNoActivate(BOOL bNoActivate);

	BYTE GetOpacity() const;
	void SetOpacity(BYTE nOpacity);

	BOOL IsLayered();
	void SetLayered(BOOL bLayered);
	RECT& GetLayeredInset();
	void SetLayeredInset(RECT& rcLayeredInset);
	BYTE GetLayeredOpacity();
	void SetLayeredOpacity(BYTE nOpacity);
	LPCTSTR GetLayeredImage();
	void SetLayeredImage(LPCTSTR pstrImage);

    static HINSTANCE GetInstance();
    static CDuiString GetInstancePath();
    static CDuiString GetCurrentPath();
    static HINSTANCE GetResourceDll();
    static const CDuiString& GetResourcePath();
    static const CDuiString& GetResourceZip();
	static BOOL IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
    static void SetInstance(HINSTANCE hInst);
    static void SetCurrentPath(LPCTSTR pStrPath);
    static void SetResourceDll(HINSTANCE hInst);
    static void SetResourcePath(LPCTSTR pStrPath);
	static void SetResourceZip(LPVOID pVoid, unsigned int len);
	static void SetResourceZip(LPCTSTR pstrZip, BOOL bCachedResourceZip = FALSE);
	static BOOL GetHSL(short* H, short* S, short* L);
	static void SetHSL(BOOL bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
	static CPaintManagerUI* GetPaintManager(LPCTSTR pstrName);
	static CDuiPtrArray* GetPaintManagers();
	static BOOL LoadPlugin(LPCTSTR pstrModuleName);
    static CDuiPtrArray* GetPlugins();

	BOOL IsForceUseSharedRes() const;
	void SetForceUseSharedRes(BOOL bForce);

    DWORD GetDefaultDisabledColor() const;
	void SetDefaultDisabledColor(DWORD dwColor, BOOL bShared = FALSE);
    DWORD GetDefaultFontColor() const;
	void SetDefaultFontColor(DWORD dwColor, BOOL bShared = FALSE);
    DWORD GetDefaultLinkFontColor() const;
	void SetDefaultLinkFontColor(DWORD dwColor, BOOL bShared = FALSE);
    DWORD GetDefaultLinkHoverFontColor() const;
	void SetDefaultLinkHoverFontColor(DWORD dwColor, BOOL bShared = FALSE);
    DWORD GetDefaultSelectedBkColor() const;
	void SetDefaultSelectedBkColor(DWORD dwColor, BOOL bShared = FALSE);

    TFontInfo* GetDefaultFontInfo();
	void SetDefaultFont(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
	DWORD GetCustomFontCount(BOOL bShared = FALSE) const;
	HFONT AddFont(int id, LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
    HFONT GetFont(int id);
	HFONT GetFont(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic);
	int GetFontIndex(HFONT hFont, BOOL bShared = FALSE);
	int GetFontIndex(LPCTSTR pStrFontName, int nSize, BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bShared = FALSE);
	void RemoveFont(HFONT hFont, BOOL bShared = FALSE);
	void RemoveFont(int id, BOOL bShared = FALSE);
	void RemoveAllFonts(BOOL bShared = FALSE);
    TFontInfo* GetFontInfo(int id);
    TFontInfo* GetFontInfo(HFONT hFont);

    const TImageInfo* GetImage(LPCTSTR bitmap);
	const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, BOOL bUseHSL = FALSE);
	const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, BOOL bUseHSL = FALSE, BOOL bShared = FALSE);
	const TImageInfo* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, BOOL bAlpha, BOOL bShared = FALSE);
	void RemoveImage(LPCTSTR bitmap, BOOL bShared = FALSE);
	void RemoveAllImages(BOOL bShared = FALSE);
	static void ReloadSharedImages();
	void ReloadImages();

	void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList, BOOL bShared = FALSE);
    LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
	BOOL RemoveDefaultAttributeList(LPCTSTR pStrControlName, BOOL bShared = FALSE);
	void RemoveAllDefaultAttributeList(BOOL bShared = false);

    void AddWindowCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
    LPCTSTR GetWindowCustomAttribute(LPCTSTR pstrName) const;
	BOOL RemoveWindowCustomAttribute(LPCTSTR pstrName);
    void RemoveAllWindowCustomAttribute();

    CDuiString GetWindowAttribute(LPCTSTR pstrName);
    void SetWindowAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	CDuiString GetWindowAttributeList(BOOL bIgnoreDefault = TRUE);
    void SetWindowAttributeList(LPCTSTR pstrList);
	BOOL RemoveWindowAttribute(LPCTSTR pstrName);

    CDuiString GetWindowXML();

	static void AddMultiLanguageString(int id, LPCTSTR pStrMultiLanguage);
	static LPCTSTR GetMultiLanguageString(int id);
	static BOOL RemoveMultiLanguageString(int id);
	static void RemoveAllMultiLanguageString();
	static void ProcessMultiLanguageTokens(CDuiString& pStrMultiLanguage);

	BOOL AttachDialog(CControlUI* pControl);
	BOOL InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
	BOOL RenameControl(CControlUI* pControl, LPCTSTR pstrName);
	LRESULT ReapObjects(CControlUI* pControl);

	BOOL AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    CDuiPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);
    void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    void RemoveAllOptionGroups();

    CControlUI* GetFocus() const;
	void SetFocus(CControlUI* pControl, BOOL bFocusWnd = TRUE);
    void SetFocusNeeded(CControlUI* pControl);

	BOOL SetNextTabControl(BOOL bForward = TRUE);

    LRESULT SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
	LRESULT KillTimer(CControlUI* pControl, UINT nTimerID);
    void KillTimer(CControlUI* pControl);
    void RemoveAllTimers();

    void SetCapture();
    void ReleaseCapture();
	BOOL IsCaptured();

	BOOL IsPainting();
	void SetPainting(BOOL bIsPainting);

	LRESULT AddNotifier(INotifyUI* pControl);
	LRESULT RemoveNotifier(INotifyUI* pControl);
	void SendNotify(TNotifyUI& Msg, BOOL bAsync = FALSE, BOOL bEnableRepeat = TRUE);
	void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bAsync = FALSE, BOOL bEnableRepeat = TRUE);

	LRESULT AddPreMessageFilter(IMessageFilterUI* pFilter);
	LRESULT RemovePreMessageFilter(IMessageFilterUI* pFilter);

	LRESULT AddMessageFilter(IMessageFilterUI* pFilter);
	LRESULT RemoveMessageFilter(IMessageFilterUI* pFilter);

    int GetPostPaintCount() const;
	LRESULT AddPostPaint(CControlUI* pControl);
	LRESULT RemovePostPaint(CControlUI* pControl);
	LRESULT SetPostPaintIndex(CControlUI* pControl, int iIndex);

	int GetNativeWindowCount() const;
	RECT GetNativeWindowRect(HWND hChildWnd);
	LRESULT AddNativeWindow(CControlUI* pControl, HWND hChildWnd);
	LRESULT RemoveNativeWindow(HWND hChildWnd);

    void AddDelayedCleanup(CControlUI* pControl);
	LRESULT AddMouseLeaveNeeded(CControlUI* pControl);
	LRESULT RemoveMouseLeaveNeeded(CControlUI* pControl);

	LRESULT AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	LRESULT RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	LRESULT TranslateAccelerator(LPMSG pMsg);

    CControlUI* GetRoot() const;
    CControlUI* FindControl(POINT pt) const;
    CControlUI* FindControl(LPCTSTR pstrName) const;
    CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
    CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
    CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
    CDuiPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);

	static LRESULT MessageLoop();
	static LRESULT TranslateMessage(const LPMSG pMsg);
	static LRESULT Term();

	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	LRESULT PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	void UsedVirtualWnd(BOOL bUsed);

private:
	CDuiPtrArray* GetFoundControls();
    static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlsFromUpdate(CControlUI* pThis, LPVOID pData);

	static void AdjustSharedImagesHSL();
	void AdjustImagesHSL();
	void PostAsyncNotify();

private:
	CDuiString m_sName;
    HWND m_hWndPaint;
    HDC m_hDcPaint;
    HDC m_hDcOffscreen;
    HDC m_hDcBackground;
    HBITMAP m_hbmpOffscreen;
	COLORREF* m_pOffscreenBits;
    HBITMAP m_hbmpBackground;
	COLORREF* m_pBackgroundBits;
	int m_iTooltipWidth;
    int m_iLastTooltipWidth;
	HWND m_hwndTooltip;
	TOOLINFO m_ToolTip;
	int m_iHoverTime;
	BOOL m_bNoActivate;
	BOOL m_bShowUpdateRect;
    //
    CControlUI* m_pRoot;
    CControlUI* m_pFocus;
    CControlUI* m_pEventHover;
    CControlUI* m_pEventClick;
    CControlUI* m_pEventKey;
    CControlUI* m_pLastToolTip;
    //
    POINT m_ptLastMousePos;
    SIZE m_szMinWindow;
    SIZE m_szMaxWindow;
    SIZE m_szInitWindowSize;
    RECT m_rcSizeBox;
    SIZE m_szRoundCorner;
    RECT m_rcCaption;
    UINT m_uTimerID;
	BOOL m_bFirstLayout;
	BOOL m_bUpdateNeeded;
	BOOL m_bFocusNeeded;
	BOOL m_bOffscreenPaint;

	BYTE m_nOpacity;
	BOOL m_bLayered;
	RECT m_rcLayeredInset;
	BOOL m_bLayeredChanged;
	RECT m_rcLayeredUpdate;
	TDrawInfo m_diLayered;

	BOOL m_bMouseTracking;
	BOOL m_bMouseCapture;
	BOOL m_bIsPainting;
	BOOL m_bUsedVirtualWnd;
	BOOL m_bAsyncNotifyPosted;

    //
    CDuiPtrArray m_aNotifiers;
    CDuiPtrArray m_aTimers;
    CDuiPtrArray m_aPreMessageFilters;
    CDuiPtrArray m_aMessageFilters;
    CDuiPtrArray m_aPostPaintControls;
	CDuiPtrArray m_aNativeWindow;
	CDuiPtrArray m_aNativeWindowControl;
    CDuiPtrArray m_aDelayedCleanup;
    CDuiPtrArray m_aAsyncNotify;
    CDuiPtrArray m_aFoundControls;
    CDuiPtrArray m_aNeedMouseLeaveNeeded;
    CDuiStringPtrMap m_mNameHash;
	CDuiStringPtrMap m_mWindowAttrHash;
    CDuiStringPtrMap m_mOptionGroup;

    //
	BOOL m_bForceUseSharedRes;
	TResInfo m_ResInfo;

    //
	static HINSTANCE m_hResourceInstance;
	static CDuiString m_pStrResourcePath;
	static CDuiString m_pStrResourceZip;
	static HANDLE m_hResourceZip;

	static BOOL m_bCachedResourceZip;
	static TResInfo m_SharedResInfo;
    static HINSTANCE m_hInstance;
	static BOOL m_bUseHSL;
    static short m_H;
    static short m_S;
    static short m_L;
    static CDuiPtrArray m_aPreMessages;
    static CDuiPtrArray m_aPlugins;

public:
	CDuiPtrArray m_aTranslateAccelerator;
};

} // namespace DuiLib

#endif // __UIMANAGER_H__
