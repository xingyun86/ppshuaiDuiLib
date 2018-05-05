#ifndef __UIVERTICALLAYOUT_H__
#define __UIVERTICALLAYOUT_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CVerticalLayoutUI : public CContainerUI
	{
	public:
		CVerticalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(BOOL bImmediately);
		BOOL IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		LRESULT DoEvent(TEventUI& event);

		LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = true);
		LRESULT DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(BOOL bUseNew = false) const;

	protected:
		int m_iSepHeight;
		UINT m_uButtonState;
		POINT m_ptLastMouse;
		RECT m_rcNewPos;
		BOOL m_bImmMode;
	};
}
#endif // __UIVERTICALLAYOUT_H__
