#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

class DUILIB_API CControlUI
{
public:
    CControlUI();
    virtual void Delete();

protected:
    virtual ~CControlUI();

public:
    virtual CDuiString GetName() const;
    virtual void SetName(LPCTSTR pstrName);
    virtual LPCTSTR GetClass() const;
    virtual LPVOID GetInterface(LPCTSTR pstrName);
    virtual UINT GetControlFlags() const;
	virtual HWND GetNativeWindow() const;

    virtual BOOL Activate();
    virtual CPaintManagerUI* GetManager() const;
    virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);
    virtual CControlUI* GetParent() const;
    virtual CControlUI* GetCover() const;
    virtual void SetCover(CControlUI *pControl);

    // 文本相关
    virtual CDuiString GetText() const;
    virtual void SetText(LPCTSTR pstrText);

    // 图形相关
    DWORD GetBkColor() const;
    void SetBkColor(DWORD dwBackColor);
    DWORD GetBkColor2() const;
    void SetBkColor2(DWORD dwBackColor);
    DWORD GetBkColor3() const;
    void SetBkColor3(DWORD dwBackColor);
    LPCTSTR GetBkImage();
    void SetBkImage(LPCTSTR pStrImage);
	DWORD GetFocusBorderColor() const;
	void SetFocusBorderColor(DWORD dwBorderColor);
    BOOL IsColorHSL() const;
    void SetColorHSL(BOOL bColorHSL);
    SIZE GetBorderRound() const;
    void SetBorderRound(SIZE cxyRound);
	LRESULT DrawImage(HDC hDC, TDrawInfo& drawInfo);

	//边框相关
	DWORD GetBorderColor() const;
	void SetBorderColor(DWORD dwBorderColor);
	RECT GetBorderSize() const;
	void SetBorderSize(RECT rc);
	void SetBorderSize(int iSize);
	int GetBorderStyle() const;
	void SetBorderStyle(int nStyle);

    // 位置相关
    virtual const RECT& GetPos() const;
	virtual RECT GetRelativePos() const; // 相对(父控件)位置
	virtual RECT GetClientPos() const; // 客户区域（除去scrollbar和inset）
	// 只有控件为float的时候，外部调用SetPos和Move才是有效的，位置参数是相对父控件的位置
	virtual LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
	virtual LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
    virtual LONG GetWidth() const;
    virtual LONG GetHeight() const;
    virtual LONG GetX() const;
    virtual LONG GetY() const;
    virtual RECT GetPadding() const;
    virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
    virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedXY(SIZE szXY);      // 仅float为true时有效
	virtual TPercentInfo GetFloatPercent() const;
	virtual void SetFloatPercent(TPercentInfo piFloatPercent);
    virtual LONG GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedWidth(int cx);      // 预设的参考值
    virtual LONG GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedHeight(int cy);     // 预设的参考值
    virtual LONG GetMinWidth() const;
    virtual void SetMinWidth(int cx);
    virtual LONG GetMaxWidth() const;
    virtual void SetMaxWidth(int cx);
    virtual LONG GetMinHeight() const;
    virtual void SetMinHeight(int cy);
    virtual LONG GetMaxHeight() const;
    virtual void SetMaxHeight(int cy);

    // 鼠标提示
    virtual CDuiString GetToolTip() const;
    virtual void SetToolTip(LPCTSTR pstrText);
	virtual void SetToolTipWidth(LONG nWidth);
	virtual LONG GetToolTipWidth(void);	// 多行ToolTip单行最长宽度

    // 快捷键
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut(TCHAR ch);

    // 菜单
    virtual BOOL IsContextMenuUsed() const;
    virtual void SetContextMenuUsed(BOOL bMenuUsed);

    // 用户属性
    virtual const CDuiString& GetUserData(); // 辅助函数，供用户使用
    virtual void SetUserData(LPCTSTR pstrText); // 辅助函数，供用户使用
    virtual UINT_PTR GetTag() const; // 辅助函数，供用户使用
    virtual void SetTag(UINT_PTR pTag); // 辅助函数，供用户使用

    // 一些重要的属性
    virtual BOOL IsVisible() const;
    virtual void SetVisible(BOOL bVisible = TRUE);
    virtual void SetInternVisible(BOOL bVisible = TRUE); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    virtual BOOL IsEnabled() const;
    virtual void SetEnabled(BOOL bEnable = TRUE);
    virtual BOOL IsMouseEnabled() const;
    virtual void SetMouseEnabled(BOOL bEnable = TRUE);
    virtual BOOL IsKeyboardEnabled() const;
    virtual void SetKeyboardEnabled(BOOL bEnable = TRUE);
    virtual BOOL IsFocused() const;
    virtual void SetFocus();
    virtual BOOL IsFloat() const;
    virtual void SetFloat(BOOL bFloat = TRUE);

	// 自定义(未处理的)属性
	LRESULT AddCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
	LPCTSTR GetCustomAttribute(LPCTSTR pstrName) const;
	LRESULT RemoveCustomAttribute(LPCTSTR pstrName);
	LRESULT RemoveAllCustomAttribute();

    virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	LRESULT Invalidate();
    BOOL IsUpdateNeeded() const;
	LRESULT NeedUpdate();
	LRESULT NeedParentUpdate();
    DWORD GetAdjustColor(DWORD dwColor);

	virtual LRESULT Init();
	virtual LRESULT DoInit();

	virtual LRESULT Event(TEventUI& event);
	virtual LRESULT DoEvent(TEventUI& event);

    virtual CDuiString GetAttribute(LPCTSTR pstrName);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual CDuiString GetAttributeList(BOOL bIgnoreDefault = TRUE);
    virtual void SetAttributeList(LPCTSTR pstrList);

    virtual SIZE EstimateSize(SIZE szAvailable);

	virtual LRESULT Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl = NULL); // 返回要不要继续绘制
	virtual LRESULT DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
	virtual LRESULT PaintBkColor(HDC hDC);
	virtual LRESULT PaintBkImage(HDC hDC);
	virtual LRESULT PaintStatusImage(HDC hDC);
	virtual LRESULT PaintText(HDC hDC);
	virtual LRESULT PaintBorder(HDC hDC);

	virtual LRESULT DoPostPaint(HDC hDC, const RECT& rcPaint);

	//虚拟窗口参数
	void SetVirtualWnd(LPCTSTR pstrValue);
	CDuiString GetVirtualWnd() const;

public:
    CEventSource OnInit;
    CEventSource OnDestroy;
    CEventSource OnSize;
    CEventSource OnEvent;
    CEventSource OnNotify;
	CEventSource OnPaint;
	CEventSource OnPostPaint;

protected:
    CPaintManagerUI* m_pManager;
    CControlUI* m_pParent;
    CControlUI* m_pCover;
	CDuiString m_sVirtualWnd;
    CDuiString m_sName;
    BOOL m_bUpdateNeeded;
	BOOL m_bMenuUsed;
	BOOL m_bAsyncNotify;
    RECT m_rcItem;
    RECT m_rcPadding;
    SIZE m_cXY;
    SIZE m_cxyFixed;
    SIZE m_cxyMin;
    SIZE m_cxyMax;
	BOOL m_bVisible;
	BOOL m_bInternVisible;
	BOOL m_bEnabled;
	BOOL m_bMouseEnabled;
	BOOL m_bKeyboardEnabled;
	BOOL m_bFocused;
	BOOL m_bFloat;
	TPercentInfo m_piFloatPercent;
	BOOL m_bSetPos; // 防止SetPos循环调用

    CDuiString m_sText;
    CDuiString m_sToolTip;
    TCHAR m_chShortcut;
    CDuiString m_sUserData;
    UINT_PTR m_pTag;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    TDrawInfo m_diBk;
	TDrawInfo m_diFore;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
	BOOL m_bColorHSL;
	LONG m_nBorderStyle;
	LONG m_nTooltipWidth;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;
	RECT m_rcBorderSize;
	CDuiStringPtrMap m_mCustomAttrHash;
};

} // namespace DuiLib

#endif // __UICONTROL_H__
