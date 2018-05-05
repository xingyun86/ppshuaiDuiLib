#ifndef __UITABLAYOUT_H__
#define __UITABLAYOUT_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CTabLayoutUI : public CContainerUI
	{
	public:
		CTabLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		LRESULT Add(CControlUI* pControl);
		LRESULT AddAt(CControlUI* pControl, int iIndex);
		LRESULT Remove(CControlUI* pControl, BOOL bDoNotDestroy = FALSE);
		LRESULT RemoveAll();
		int GetCurSel() const;
		BOOL SelectItem(int iIndex, BOOL bTriggerEvent=TRUE);
		BOOL SelectItem(CControlUI* pControl,  BOOL bTriggerEvent=TRUE);

		LRESULT SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		int m_iCurSel;
	};
}
#endif // __UITABLAYOUT_H__
