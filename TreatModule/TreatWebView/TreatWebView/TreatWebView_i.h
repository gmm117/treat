

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 29 13:25:44 2016
 */
/* Compiler settings for TreatWebView.idl:
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

#ifndef __TreatWebView_i_h__
#define __TreatWebView_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITreatHtmlModule_FWD_DEFINED__
#define __ITreatHtmlModule_FWD_DEFINED__
typedef interface ITreatHtmlModule ITreatHtmlModule;
#endif 	/* __ITreatHtmlModule_FWD_DEFINED__ */


#ifndef __TreatHtmlModule_FWD_DEFINED__
#define __TreatHtmlModule_FWD_DEFINED__

#ifdef __cplusplus
typedef class TreatHtmlModule TreatHtmlModule;
#else
typedef struct TreatHtmlModule TreatHtmlModule;
#endif /* __cplusplus */

#endif 	/* __TreatHtmlModule_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITreatHtmlModule_INTERFACE_DEFINED__
#define __ITreatHtmlModule_INTERFACE_DEFINED__

/* interface ITreatHtmlModule */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITreatHtmlModule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D830A25B-A6E7-4D35-B5D8-EA7794931506")
    ITreatHtmlModule : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowWebView( 
            BSTR pbstrData,
            VARIANT_BOOL *vbResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChildDestroy( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITreatHtmlModuleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITreatHtmlModule * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITreatHtmlModule * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITreatHtmlModule * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITreatHtmlModule * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITreatHtmlModule * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITreatHtmlModule * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITreatHtmlModule * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowWebView )( 
            ITreatHtmlModule * This,
            BSTR pbstrData,
            VARIANT_BOOL *vbResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ChildDestroy )( 
            ITreatHtmlModule * This);
        
        END_INTERFACE
    } ITreatHtmlModuleVtbl;

    interface ITreatHtmlModule
    {
        CONST_VTBL struct ITreatHtmlModuleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITreatHtmlModule_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITreatHtmlModule_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITreatHtmlModule_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITreatHtmlModule_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITreatHtmlModule_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITreatHtmlModule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITreatHtmlModule_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITreatHtmlModule_ShowWebView(This,pbstrData,vbResult)	\
    ( (This)->lpVtbl -> ShowWebView(This,pbstrData,vbResult) ) 

#define ITreatHtmlModule_ChildDestroy(This)	\
    ( (This)->lpVtbl -> ChildDestroy(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITreatHtmlModule_INTERFACE_DEFINED__ */



#ifndef __TreatWebViewLib_LIBRARY_DEFINED__
#define __TreatWebViewLib_LIBRARY_DEFINED__

/* library TreatWebViewLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TreatWebViewLib;

EXTERN_C const CLSID CLSID_TreatHtmlModule;

#ifdef __cplusplus

class DECLSPEC_UUID("384178EC-C8F7-4B04-9F1D-E78E6118216F")
TreatHtmlModule;
#endif
#endif /* __TreatWebViewLib_LIBRARY_DEFINED__ */

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


