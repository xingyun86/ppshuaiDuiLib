#ifndef __UIHORIZONTALLAYOUT_H__
#define __UIHORIZONTALLAYOUT_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CHorizontalLayoutUI : public CContainerUI
	{
	public:
		CHorizontalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepWidth(int iWidth);
		LONG GetSepWidth() const;
		void SetSepImmMode(BOOL bImmediately);
		BOOL IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		LRESULT DoEvent(TEventUI& event);

		LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
		LRESULT DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(BOOL bUseNew = FALSE) const;

	protected:
		LONG m_iSepWidth;
		UINT m_uButtonState;
		POINT m_ptLastMouse;
		RECT m_rcNewPos;
		BOOL m_bImmMode;
	};
}
#endif // __UIHORIZONTALLAYOUT_H__
