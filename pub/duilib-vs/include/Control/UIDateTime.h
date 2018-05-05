#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#pragma once

namespace DuiLib
{
	class CDateTimeWnd;

	/// 时间选择控件
	class DUILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;
		HWND GetNativeWindow() const;

		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);

		void SetReadOnly(BOOL bReadOnly);
		BOOL IsReadOnly() const;

		LRESULT UpdateText();

		LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
		LRESULT Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);

		LRESULT DoEvent(TEventUI& event);

	protected:
		SYSTEMTIME m_sysTime;
		LONG       m_nDTUpdateFlag;
		BOOL       m_bReadOnly;

		CDateTimeWnd* m_pWindow;
	};
}
#endif // __UIDATETIME_H__