#ifndef	_COMMONDLGPROCHOOKER_H_
#define	_COMMONDLGPROCHOOKER_H_
#include "dllmain.h"

////////////////////
//	H3DlgProcHook
template<class T>
class CProcHooker
{
	public:
		typedef CProcHooker<T>	thisClassType;

	//////////////////////////////////////////////////////////////////////////
	//	GetThisClass
	//////////////////////////////////////////////////////////////////////////
	static T*& GetThisClass()
	{
		static T* t;
		return t;
	}
	
	//////////////////////////////////////////////////////////////////////////
	//	GetHookHandle
	//////////////////////////////////////////////////////////////////////////
	static HHOOK& GetHookHandle()
	{
		static HHOOK hook;
		return hook;
	}


	//////////////////////////////////////////////////////////////////////////
	//	HookProc
	//////////////////////////////////////////////////////////////////////////
	static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if((nCode < 0) ||				//	코드가 0 미만일 경우 리턴
		   (nCode != MSGF_DIALOGBOX))	//	다이얼로그 메시지가 아닌 경우 리턴
		{
			return CallNextHookEx(GetHookHandle(), nCode, wParam, lParam);
		}

		//	Message
		MSG* pMsg = reinterpret_cast<MSG*>(lParam);
		T*& pT = GetThisClass();
		BOOL bResult = pT->OnHook(pMsg);
		if(!bResult)
			return CallNextHookEx(GetHookHandle(), nCode, wParam, lParam);

		return TRUE;	//	Stop processing.... if return value is TRUE.
	}


	//////////////////////////////////////////////////////////////////////////
	//	OnHook
	//////////////////////////////////////////////////////////////////////////
	BOOL OnHook(const MSG* msg)
	{
		return FALSE;
	}



	//////////////////////////////////////////////////////////////////////////
	//	Hook
	//////////////////////////////////////////////////////////////////////////
	BOOL Hook()
	{
		T* pT = static_cast<T*>(this);
		T*& ref = GetThisClass();
		ref = pT;

		HHOOK& hook = GetHookHandle();

		hook = ::SetWindowsHookEx(WH_MSGFILTER, HookProc, NULL , ::GetCurrentThreadId());
		if(hook == 0L)
		{
			//	ERROR OCCURED
			::MessageBox(0, _T("E00020001: Failure in installing hooking procedure"), _T("ERROR"), MB_OK | MB_ICONSTOP);
			return FALSE;
		}

		return TRUE;
	}


	//////////////////////////////////////////////////////////////////////////
	//	Unhook
	//////////////////////////////////////////////////////////////////////////
	BOOL UnHook()
	{
		HHOOK& hook = GetHookHandle();
		if(hook)
		{
			if(FALSE == ::UnhookWindowsHookEx(hook))
			{
				::MessageBox(0, _T("E00020002: Unhooking failed"), _T("ERROR"), MB_OK | MB_ICONSTOP);
				return FALSE;
			}

		}

		return TRUE;
	}
};


#endif	//	_COMMONDLGPROCHOOKER_H_