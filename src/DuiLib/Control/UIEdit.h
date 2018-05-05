#ifndef __UIEDIT_H__
#define __UIEDIT_H__

#pragma once

namespace DuiLib
{
	class CEditWnd;

	class DUILIB_API CEditUI : public CLabelUI
	{
		friend class CEditWnd;
	public:
		CEditUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		void SetEnabled(BOOL bEnable = TRUE);
		void SetText(LPCTSTR pstrText);
		void SetMaxChar(UINT uMax);
		UINT GetMaxChar();
		void SetReadOnly(BOOL bReadOnly);
		BOOL IsReadOnly() const;
		void SetPasswordMode(BOOL bPasswordMode);
		BOOL IsPasswordMode() const;
		void SetPasswordChar(TCHAR cPasswordChar);
		TCHAR GetPasswordChar() const;
		BOOL IsAutoSelAll();
		void SetAutoSelAll(BOOL bAutoSelAll);
		void SetNumberOnly(BOOL bNumberOnly);
		BOOL IsNumberOnly() const;
		LONG GetWindowStyles() const;
		HWND GetNativeEditHWND() const;

		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR pStrImage);
		LPCTSTR GetFocusedImage();
		void SetFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR pStrImage);
		void SetNativeEditBkColor(DWORD dwBkColor);
		DWORD GetNativeEditBkColor() const;

		LRESULT SetSel(long nStartChar, long nEndChar);
		LRESULT SetSelAll();
		LRESULT SetReplaceSel(LPCTSTR lpszReplace);

		LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
		LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
		void SetVisible(BOOL bVisible = TRUE);
		void SetInternVisible(BOOL bVisible = TRUE);
		SIZE EstimateSize(SIZE szAvailable);
		LRESULT DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		LRESULT PaintStatusImage(HDC hDC);
		LRESULT PaintText(HDC hDC);

	protected:
		CEditWnd* m_pWindow;

		UINT m_uMaxChar;
		BOOL m_bReadOnly;
		BOOL m_bPasswordMode;
		BOOL m_bAutoSelAll;
		TCHAR m_cPasswordChar;
		UINT m_uButtonState;
		DWORD m_dwEditbkColor;
		LONG m_nWindowStyles;

		TDrawInfo m_diNormal;
		TDrawInfo m_diHot;
		TDrawInfo m_diFocused;
		TDrawInfo m_diDisabled;
	};
}
#endif // __UIEDIT_H__