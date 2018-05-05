#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CSliderUI : public CProgressUI
	{
	public:
		CSliderUI();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetEnabled(BOOL bEnable = true);

		LONG GetChangeStep();
		void SetChangeStep(LONG step);
		void SetThumbSize(SIZE szXY);
		RECT GetThumbRect() const;
		BOOL IsImmMode() const;
		void SetImmMode(BOOL bImmMode);
		LPCTSTR GetThumbImage() const;
		void SetThumbImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbHotImage() const;
		void SetThumbHotImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbPushedImage() const;
		void SetThumbPushedImage(LPCTSTR pStrImage);

		LRESULT DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		LRESULT PaintStatusImage(HDC hDC);

	protected:
		SIZE m_szThumb;
		UINT m_uButtonState;
		LONG m_nStep;
		BOOL m_bImmMode;

		TDrawInfo m_diThumb;
		TDrawInfo m_diThumbHot;
		TDrawInfo m_diThumbPushed;
	};
}

#endif // __UISLIDER_H__