

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for G_SUB_Inspection.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0620 
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
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __G_SUB_Inspection_h_h__
#define __G_SUB_Inspection_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IG_SUB_Inspection_FWD_DEFINED__
#define __IG_SUB_Inspection_FWD_DEFINED__
typedef interface IG_SUB_Inspection IG_SUB_Inspection;

#endif 	/* __IG_SUB_Inspection_FWD_DEFINED__ */


#ifndef __G_SUB_Inspection_FWD_DEFINED__
#define __G_SUB_Inspection_FWD_DEFINED__

#ifdef __cplusplus
typedef class G_SUB_Inspection G_SUB_Inspection;
#else
typedef struct G_SUB_Inspection G_SUB_Inspection;
#endif /* __cplusplus */

#endif 	/* __G_SUB_Inspection_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __G_SUB_Inspection_LIBRARY_DEFINED__
#define __G_SUB_Inspection_LIBRARY_DEFINED__

/* library G_SUB_Inspection */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_G_SUB_Inspection;

#ifndef __IG_SUB_Inspection_DISPINTERFACE_DEFINED__
#define __IG_SUB_Inspection_DISPINTERFACE_DEFINED__

/* dispinterface IG_SUB_Inspection */
/* [uuid] */ 


EXTERN_C const IID DIID_IG_SUB_Inspection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2A95506E-C52C-4CFE-BCAB-ACEAE356EFEF")
    IG_SUB_Inspection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IG_SUB_InspectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG_SUB_Inspection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG_SUB_Inspection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG_SUB_Inspection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG_SUB_Inspection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG_SUB_Inspection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG_SUB_Inspection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG_SUB_Inspection * This,
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
        
        END_INTERFACE
    } IG_SUB_InspectionVtbl;

    interface IG_SUB_Inspection
    {
        CONST_VTBL struct IG_SUB_InspectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG_SUB_Inspection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG_SUB_Inspection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG_SUB_Inspection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG_SUB_Inspection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG_SUB_Inspection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG_SUB_Inspection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG_SUB_Inspection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IG_SUB_Inspection_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_G_SUB_Inspection;

#ifdef __cplusplus

class DECLSPEC_UUID("C56B5EF0-4CB1-4D70-AF8D-25BA3DFFC0AC")
G_SUB_Inspection;
#endif
#endif /* __G_SUB_Inspection_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


