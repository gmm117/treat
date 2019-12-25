

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 29 13:23:32 2016
 */
/* Compiler settings for TreatWrapper.idl:
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

#ifndef __TreatWrapper_i_h__
#define __TreatWrapper_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITreatWrapperInterface_FWD_DEFINED__
#define __ITreatWrapperInterface_FWD_DEFINED__
typedef interface ITreatWrapperInterface ITreatWrapperInterface;
#endif 	/* __ITreatWrapperInterface_FWD_DEFINED__ */


#ifndef __TreatWrapperInterface_FWD_DEFINED__
#define __TreatWrapperInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class TreatWrapperInterface TreatWrapperInterface;
#else
typedef struct TreatWrapperInterface TreatWrapperInterface;
#endif /* __cplusplus */

#endif 	/* __TreatWrapperInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITreatWrapperInterface_INTERFACE_DEFINED__
#define __ITreatWrapperInterface_INTERFACE_DEFINED__

/* interface ITreatWrapperInterface */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITreatWrapperInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3365DD4-A69A-408B-8F2A-6D56FA5FC196")
    ITreatWrapperInterface : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateModule( 
            /* [in] */ IUnknown *pUnkn) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChildDestroy( void) = 0;
        
        virtual /* [local][id] */ HRESULT STDMETHODCALLTYPE LoadBasicSuga( 
            /* [in] */ long lHospDiv,
            /* [in] */ BSTR bstrStandDate,
            /* [out] */ BSTR *pvarCode,
            /* [out] */ BSTR *pvarName,
            /* [out] */ BSTR *pvarCost,
            /* [in] */ short nCount,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetStandDate( 
            /* [in] */ long lHospDiv,
            /* [out] */ BSTR *pbstrStandDate) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTotalBasicContSize( 
            /* [out] */ long *plDataSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurControlSize( 
            /* [in] */ long lContIdx,
            /* [out] */ long *plCurSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurData( 
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurContRect( 
            /* [in] */ long lContIdx,
            /* [out] */ long *plLeft,
            /* [out] */ long *plTop,
            /* [out] */ long *plRight,
            /* [out] */ long *plBottom) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurContStatic( 
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurCode( 
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITreatWrapperInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITreatWrapperInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITreatWrapperInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITreatWrapperInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITreatWrapperInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITreatWrapperInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITreatWrapperInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITreatWrapperInterface * This,
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateModule )( 
            ITreatWrapperInterface * This,
            /* [in] */ IUnknown *pUnkn);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ChildDestroy )( 
            ITreatWrapperInterface * This);
        
        /* [local][id] */ HRESULT ( STDMETHODCALLTYPE *LoadBasicSuga )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lHospDiv,
            /* [in] */ BSTR bstrStandDate,
            /* [out] */ BSTR *pvarCode,
            /* [out] */ BSTR *pvarName,
            /* [out] */ BSTR *pvarCost,
            /* [in] */ short nCount,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetStandDate )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lHospDiv,
            /* [out] */ BSTR *pbstrStandDate);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTotalBasicContSize )( 
            ITreatWrapperInterface * This,
            /* [out] */ long *plDataSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurControlSize )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lContIdx,
            /* [out] */ long *plCurSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurData )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurContRect )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lContIdx,
            /* [out] */ long *plLeft,
            /* [out] */ long *plTop,
            /* [out] */ long *plRight,
            /* [out] */ long *plBottom);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurContStatic )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurCode )( 
            ITreatWrapperInterface * This,
            /* [in] */ long lContIdx,
            /* [out] */ BSTR *pbstrData);
        
        END_INTERFACE
    } ITreatWrapperInterfaceVtbl;

    interface ITreatWrapperInterface
    {
        CONST_VTBL struct ITreatWrapperInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITreatWrapperInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITreatWrapperInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITreatWrapperInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITreatWrapperInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITreatWrapperInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITreatWrapperInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITreatWrapperInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITreatWrapperInterface_CreateModule(This,pUnkn)	\
    ( (This)->lpVtbl -> CreateModule(This,pUnkn) ) 

#define ITreatWrapperInterface_ChildDestroy(This)	\
    ( (This)->lpVtbl -> ChildDestroy(This) ) 

#define ITreatWrapperInterface_LoadBasicSuga(This,lHospDiv,bstrStandDate,pvarCode,pvarName,pvarCost,nCount,pResult)	\
    ( (This)->lpVtbl -> LoadBasicSuga(This,lHospDiv,bstrStandDate,pvarCode,pvarName,pvarCost,nCount,pResult) ) 

#define ITreatWrapperInterface_GetStandDate(This,lHospDiv,pbstrStandDate)	\
    ( (This)->lpVtbl -> GetStandDate(This,lHospDiv,pbstrStandDate) ) 

#define ITreatWrapperInterface_GetTotalBasicContSize(This,plDataSize)	\
    ( (This)->lpVtbl -> GetTotalBasicContSize(This,plDataSize) ) 

#define ITreatWrapperInterface_GetCurControlSize(This,lContIdx,plCurSize)	\
    ( (This)->lpVtbl -> GetCurControlSize(This,lContIdx,plCurSize) ) 

#define ITreatWrapperInterface_GetCurData(This,lContIdx,pbstrData)	\
    ( (This)->lpVtbl -> GetCurData(This,lContIdx,pbstrData) ) 

#define ITreatWrapperInterface_GetCurContRect(This,lContIdx,plLeft,plTop,plRight,plBottom)	\
    ( (This)->lpVtbl -> GetCurContRect(This,lContIdx,plLeft,plTop,plRight,plBottom) ) 

#define ITreatWrapperInterface_GetCurContStatic(This,lContIdx,pbstrData)	\
    ( (This)->lpVtbl -> GetCurContStatic(This,lContIdx,pbstrData) ) 

#define ITreatWrapperInterface_GetCurCode(This,lContIdx,pbstrData)	\
    ( (This)->lpVtbl -> GetCurCode(This,lContIdx,pbstrData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITreatWrapperInterface_INTERFACE_DEFINED__ */



#ifndef __TreatWrapperLib_LIBRARY_DEFINED__
#define __TreatWrapperLib_LIBRARY_DEFINED__

/* library TreatWrapperLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TreatWrapperLib;

EXTERN_C const CLSID CLSID_TreatWrapperInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("E7308AB9-E0B4-4DC8-9698-4EE6869B66AF")
TreatWrapperInterface;
#endif
#endif /* __TreatWrapperLib_LIBRARY_DEFINED__ */

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


