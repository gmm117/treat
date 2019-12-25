

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 29 13:26:08 2016
 */
/* Compiler settings for TreatConsult.idl:
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

#ifndef __TreatConsult_i_h__
#define __TreatConsult_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITreatConsultInterface_FWD_DEFINED__
#define __ITreatConsultInterface_FWD_DEFINED__
typedef interface ITreatConsultInterface ITreatConsultInterface;
#endif 	/* __ITreatConsultInterface_FWD_DEFINED__ */


#ifndef __TreatConsultInterface_FWD_DEFINED__
#define __TreatConsultInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class TreatConsultInterface TreatConsultInterface;
#else
typedef struct TreatConsultInterface TreatConsultInterface;
#endif /* __cplusplus */

#endif 	/* __TreatConsultInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITreatConsultInterface_INTERFACE_DEFINED__
#define __ITreatConsultInterface_INTERFACE_DEFINED__

/* interface ITreatConsultInterface */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITreatConsultInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("086BEB2E-59EA-4ABB-9EC9-41DE2B59FEDC")
    ITreatConsultInterface : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateModule( 
            /* [in] */ IUnknown *pUnkn,
            /* [in] */ long lParentHwnd,
            /* [in] */ long lLeft,
            /* [in] */ long lTop,
            /* [in] */ long lRight,
            /* [in] */ long lBottom) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ VARIANT_BOOL bShow) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChildDestroy( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RefleshEnvData( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITreatConsultInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITreatConsultInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITreatConsultInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITreatConsultInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITreatConsultInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITreatConsultInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITreatConsultInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITreatConsultInterface * This,
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
            ITreatConsultInterface * This,
            /* [in] */ IUnknown *pUnkn,
            /* [in] */ long lParentHwnd,
            /* [in] */ long lLeft,
            /* [in] */ long lTop,
            /* [in] */ long lRight,
            /* [in] */ long lBottom);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            ITreatConsultInterface * This,
            /* [in] */ VARIANT_BOOL bShow);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ChildDestroy )( 
            ITreatConsultInterface * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RefleshEnvData )( 
            ITreatConsultInterface * This);
        
        END_INTERFACE
    } ITreatConsultInterfaceVtbl;

    interface ITreatConsultInterface
    {
        CONST_VTBL struct ITreatConsultInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITreatConsultInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITreatConsultInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITreatConsultInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITreatConsultInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITreatConsultInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITreatConsultInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITreatConsultInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITreatConsultInterface_CreateModule(This,pUnkn,lParentHwnd,lLeft,lTop,lRight,lBottom)	\
    ( (This)->lpVtbl -> CreateModule(This,pUnkn,lParentHwnd,lLeft,lTop,lRight,lBottom) ) 

#define ITreatConsultInterface_Show(This,bShow)	\
    ( (This)->lpVtbl -> Show(This,bShow) ) 

#define ITreatConsultInterface_ChildDestroy(This)	\
    ( (This)->lpVtbl -> ChildDestroy(This) ) 

#define ITreatConsultInterface_RefleshEnvData(This)	\
    ( (This)->lpVtbl -> RefleshEnvData(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITreatConsultInterface_INTERFACE_DEFINED__ */



#ifndef __TreatConsultLib_LIBRARY_DEFINED__
#define __TreatConsultLib_LIBRARY_DEFINED__

/* library TreatConsultLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TreatConsultLib;

EXTERN_C const CLSID CLSID_TreatConsultInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("CBC93756-AC71-4578-876A-B71D4DCDC3D7")
TreatConsultInterface;
#endif
#endif /* __TreatConsultLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


