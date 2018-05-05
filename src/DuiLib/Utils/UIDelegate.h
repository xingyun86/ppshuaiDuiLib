#ifndef __UIDELEGATE_H__
#define __UIDELEGATE_H__

#pragma once

namespace DuiLib {

class DUILIB_API CDelegateBase
{
public:
    CDelegateBase(void* pObj, void* pFun);
    CDelegateBase(const CDelegateBase& rhs);
    virtual ~CDelegateBase();
	BOOL Equals(const CDelegateBase& rhs) const;
	LRESULT operator() (void* param);
    virtual CDelegateBase* Copy() const = 0; // add const for gcc

protected:
    void* GetFun();
    void* GetObj();
	virtual LRESULT Invoke(void* param) = 0;

private:
    void* m_pObj;
    void* m_pFun;
};

class CDelegateStatic: public CDelegateBase
{
	typedef LRESULT(*Fun)(void*);
public:
    CDelegateStatic(Fun pFun) : CDelegateBase(NULL, (void *)pFun) { }
    CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { }
    virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
	virtual LRESULT Invoke(void* param)
    {
        Fun pFun = (Fun)GetFun();
        return (*pFun)(param);
    }
};

template <class O, class T>
class CDelegate : public CDelegateBase
{
	typedef LRESULT(T::* Fun)(void*);
public:
    CDelegate(O* pObj, Fun pFun) : CDelegateBase(pObj, *(void**)&pFun) { }
    CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { }
    virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
	virtual LRESULT Invoke(void* param)
    {
		O* pObj = (O*) GetObj();
		union
		{
			void* ptr;
			Fun fun;
		} ufun = { GetFun() };
		return (pObj->*ufun.fun)(param);
    }

private:
	Fun m_pFun;
};

template <class O, class T>
CDelegate<O, T> MakeDelegate(O* pObj, LRESULT(T::* pFun)(void*))
{
    return CDelegate<O, T>(pObj, pFun);
}

inline CDelegateStatic MakeDelegate(LRESULT(*pFun)(void*))
{
    return CDelegateStatic(pFun);
}

class DUILIB_API CEventSource
{
    typedef LRESULT (*FunType)(void*);
public:
    ~CEventSource();
	operator LRESULT();
    void operator+= (const CDelegateBase& d); // add const for gcc
    void operator+= (FunType pFn);
    void operator-= (const CDelegateBase& d);
    void operator-= (FunType pFn);
    LRESULT operator() (void* param);

protected:
    CDuiPtrArray m_aDelegates;
};

} // namespace DuiLib

#endif // __UIDELEGATE_H__
