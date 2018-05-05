#ifndef __UIPROGRESS_H__
#define __UIPROGRESS_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CProgressUI : public CLabelUI
	{
	public:
		CProgressUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		BOOL IsHorizontal();
		void SetHorizontal(BOOL bHorizontal = TRUE);
		LONG GetMinValue() const;
		void SetMinValue(LONG nMin);
		LONG GetMaxValue() const;
		void SetMaxValue(LONG nMax);
		LONG GetValue() const;
		void SetValue(LONG nValue);
		LPCTSTR GetForeImage() const;
		void SetForeImage(LPCTSTR pStrImage);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		LRESULT PaintStatusImage(HDC hDC);

	protected:
		BOOL m_bHorizontal;
		LONG m_nMax;
		LONG m_nMin;
		LONG m_nValue;

		TDrawInfo m_diFore;
	};

} // namespace DuiLib

#endif // __UIPROGRESS_H__
