

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 29 13:25:27 2016
 */
/* Compiler settings for TreatBasicSuga.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TreatBasicSuga_i_h__
#define __TreatBasicSuga_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITreatBasicViewModule_FWD_DEFINED__
#define __ITreatBasicViewModule_FWD_DEFINED__
typedef interface ITreatBasicViewModule ITreatBasicViewModule;
#endif 	/* __ITreatBasicViewModule_FWD_DEFINED__ */


#ifndef __TreatBasicViewModule_FWD_DEFINED__
#define __TreatBasicViewModule_FWD_DEFINED__

#ifdef __cplusplus
typedef class TreatBasicViewModule TreatBasicViewModule;
#else
typedef struct TreatBasicViewModule TreatBasicViewModule;
#endif /* __cplusplus */

#endif 	/* __TreatBasicViewModule_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITreatBasicViewModule_INTERFACE_DEFINED__
#define __ITreatBasicViewModule_INTERFACE_DEFINED__

/* interface ITreatBasicViewModule */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITreatBasicViewModule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C11FA8BB-A07F-47FE-A3C7-B540856F62B1")
    ITreatBasicViewModule : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowBasicView( 
            /* [retval][out] */ VARIANT_BOOL *vbResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChildDestroy( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTreatEnvData( 
            /* [out] */ LONG *plHospDiv,
            /* [out] */ BSTR *pbstrStandDate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITreatBasicViewModuleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITreatBasicViewModule * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITreatBasicViewModule * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITreatBasicViewModule * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITreatBasicViewModule * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITreatBasicViewModule * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITreatBasicViewModule * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITreatBasicViewModule * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowBasicView )( 
            ITreatBasicViewModule * This,
            /* [retval][out] */ VARIANT_BOOL *vbResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ChildDestroy )( 
            ITreatBasicViewModule * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTreatEnvData )( 
            ITreatBasicViewModule * This,
            /* [out] */ LONG *plHospDiv,
            /* [out] */ BSTR *pbstrStandDate);
        
        END_INTERFACE
    } ITreatBasicViewModuleVtbl;

    interface ITreatBasicViewModule
    {
        CONST_VTBL struct ITreatBasicViewModuleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITreatBasicViewModule_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITreatBasicViewModule_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITreatBasicViewModule_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITreatBasicViewModule_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITreatBasicViewModule_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITreatBasicViewModule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITreatBasicViewModule_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITreatBasicViewModule_ShowBasicView(This,vbResult)	\
    ( (This)->lpVtbl -> ShowBasicView(This,vbResult) ) 

#define ITreatBasicViewModule_ChildDestroy(This)	\
    ( (This)->lpVtbl -> ChildDestroy(This) ) 

#define ITreatBasicViewModule_GetTreatEnvData(This,plHospDiv,pbstrStandDate)	\
    ( (This)->lpVtbl -> GetTreatEnvData(This,plHospDiv,pbstrStandDate) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITreatBasicViewModule_INTERFACE_DEFINED__ */



#ifndef __TreatBasicSugaLib_LIBRARY_DEFINED__
#define __TreatBasicSugaLib_LIBRARY_DEFINED__

/* library TreatBasicSugaLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TreatBasicSugaLib;

EXTERN_C const CLSID CLSID_TreatBasicViewModule;

#ifdef __cplusplus

class DECLSPEC_UUID("1C53A8C5-C155-4A6E-BFA8-2188D4EA7AEC")
TreatBasicViewModule;
#endif
#endif /* __TreatBasicSugaLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


