

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Dec 28 15:08:36 2016
 */
/* Compiler settings for .\RedirAx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __RedirAx_h__
#define __RedirAx_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IToAcroPdf_FWD_DEFINED__
#define __IToAcroPdf_FWD_DEFINED__
typedef interface IToAcroPdf IToAcroPdf;
#endif 	/* __IToAcroPdf_FWD_DEFINED__ */


#ifndef __IToAcroPDF2_FWD_DEFINED__
#define __IToAcroPDF2_FWD_DEFINED__
typedef interface IToAcroPDF2 IToAcroPDF2;
#endif 	/* __IToAcroPDF2_FWD_DEFINED__ */


#ifndef __ToAcroPdf_FWD_DEFINED__
#define __ToAcroPdf_FWD_DEFINED__

#ifdef __cplusplus
typedef class ToAcroPdf ToAcroPdf;
#else
typedef struct ToAcroPdf ToAcroPdf;
#endif /* __cplusplus */

#endif 	/* __ToAcroPdf_FWD_DEFINED__ */


#ifndef __ToAcroPDF2_FWD_DEFINED__
#define __ToAcroPDF2_FWD_DEFINED__

#ifdef __cplusplus
typedef class ToAcroPDF2 ToAcroPDF2;
#else
typedef struct ToAcroPDF2 ToAcroPDF2;
#endif /* __cplusplus */

#endif 	/* __ToAcroPDF2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IToAcroPdf_INTERFACE_DEFINED__
#define __IToAcroPdf_INTERFACE_DEFINED__

/* interface IToAcroPdf */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IToAcroPdf;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("23580868-AEBA-4B3A-B8F7-B2BCB49E2509")
    IToAcroPdf : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IToAcroPdfVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IToAcroPdf * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IToAcroPdf * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IToAcroPdf * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IToAcroPdf * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IToAcroPdf * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IToAcroPdf * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IToAcroPdf * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IToAcroPdfVtbl;

    interface IToAcroPdf
    {
        CONST_VTBL struct IToAcroPdfVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IToAcroPdf_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IToAcroPdf_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IToAcroPdf_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IToAcroPdf_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IToAcroPdf_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IToAcroPdf_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IToAcroPdf_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IToAcroPdf_INTERFACE_DEFINED__ */


#ifndef __IToAcroPDF2_INTERFACE_DEFINED__
#define __IToAcroPDF2_INTERFACE_DEFINED__

/* interface IToAcroPDF2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IToAcroPDF2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA4093A8-C728-4184-A1E1-3C2B13156952")
    IToAcroPDF2 : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IToAcroPDF2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IToAcroPDF2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IToAcroPDF2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IToAcroPDF2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IToAcroPDF2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IToAcroPDF2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IToAcroPDF2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IToAcroPDF2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IToAcroPDF2Vtbl;

    interface IToAcroPDF2
    {
        CONST_VTBL struct IToAcroPDF2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IToAcroPDF2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IToAcroPDF2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IToAcroPDF2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IToAcroPDF2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IToAcroPDF2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IToAcroPDF2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IToAcroPDF2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IToAcroPDF2_INTERFACE_DEFINED__ */



#ifndef __RedirAxLib_LIBRARY_DEFINED__
#define __RedirAxLib_LIBRARY_DEFINED__

/* library RedirAxLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RedirAxLib;

EXTERN_C const CLSID CLSID_ToAcroPdf;

#ifdef __cplusplus

class DECLSPEC_UUID("C810262B-0F7B-4529-80E5-E37217C20807")
ToAcroPdf;
#endif

EXTERN_C const CLSID CLSID_ToAcroPDF2;

#ifdef __cplusplus

class DECLSPEC_UUID("010CC513-8EDE-44E6-A74E-C24D25FC2A90")
ToAcroPDF2;
#endif
#endif /* __RedirAxLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


