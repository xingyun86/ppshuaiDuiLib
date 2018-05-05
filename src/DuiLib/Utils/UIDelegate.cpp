#include "StdAfx.h"

namespace DuiLib {

CDelegateBase::CDelegateBase(void* pObj, void* pFun) 
{
    m_pObj = pObj;
    m_pFun = pFun; 
}

CDelegateBase::CDelegateBase(const CDelegateBase& rhs) 
{
    m_pObj = rhs.m_pObj;
    m_pFun = rhs.m_pFun; 
}

CDelegateBase::~CDelegateBase()
{

}

BOOL CDelegateBase::Equals(const CDelegateBase& rhs) const 
{
    return (m_pObj == rhs.m_pObj) && (m_pFun == rhs.m_pFun); 
}

LRESULT CDelegateBase::operator() (void* param) 
{
    return Invoke(param); 
}

void* CDelegateBase::GetFun() 
{
    return m_pFun; 
}

void* CDelegateBase::GetObj() 
{
    return m_pObj; 
}

CEventSource::~CEventSource()
{
    for( int i = 0; i < m_aDelegates.GetSize(); i++ ) {
        CDelegateBase* pObj = static_cast<CDelegateBase*>(m_aDelegates[i]);
        if ( pObj) delete pObj;
    }
}

CEventSource::operator LRESULT()
{
    return m_aDelegates.GetSize() > 0 ? (0L) : (-1L);
}

void CEventSource::operator+= (const CDelegateBase& d)
{ 
    for( int i = 0; i < m_aDelegates.GetSize(); i++ ) {
        CDelegateBase* pObj = static_cast<CDelegateBase*>(m_aDelegates[i]);
        if ( pObj && pObj->Equals(d) ) return;
    }

    m_aDelegates.Add(d.Copy());
}

void CEventSource::operator+= (FunType pFun)
{ 
    (*this) += MakeDelegate(pFun);
}

void CEventSource::operator-= (const CDelegateBase& d) 
{
    for( int i = 0; i < m_aDelegates.GetSize(); i++ ) {
        CDelegateBase* pObj = static_cast<CDelegateBase*>(m_aDelegates[i]);
        if ( pObj && pObj->Equals(d) ) {
            delete pObj;
            m_aDelegates.Remove(i);
            break;
        }
    }
}
void CEventSource::operator-= (FunType pFun)
{ 
    (*this) -= MakeDelegate(pFun);
}

LRESULT CEventSource::operator() (void* param)
{
    for( int i = 0; i < m_aDelegates.GetSize(); i++ ) {
        CDelegateBase* pObj = static_cast<CDelegateBase*>(m_aDelegates[i]);
        if ( pObj && ((*pObj)(param) < (0L))) return (-1L);
    }
    return (0L);
}

} // namespace DuiLib
