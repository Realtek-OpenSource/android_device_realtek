/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCBASEDS_H_RPCGEN
#define _RPCBASEDS_H_RPCGEN

#include <RPCstruct.h>

#include "RPCBaseDS_data.h"

#ifdef __cplusplus
extern "C" {
#endif


/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_HRESULT (XDR *, HRESULT*);
extern  bool_t xdr_RPCRES_LONG (XDR *, RPCRES_LONG*);
extern  bool_t xdr_USB_DEVICE_CONFIG_INFO (XDR *, USB_DEVICE_CONFIG_INFO*);
extern  bool_t xdr_RPC_CONNECTION (XDR *, RPC_CONNECTION*);
extern  bool_t xdr_RPC_SEND_LONG (XDR *, RPC_SEND_LONG*);

#else /* K&R C */
extern bool_t xdr_HRESULT ();
extern bool_t xdr_RPCRES_LONG ();
extern bool_t xdr_USB_DEVICE_CONFIG_INFO ();
extern bool_t xdr_RPC_CONNECTION ();
extern bool_t xdr_RPC_SEND_LONG ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCBASEDS_H_RPCGEN */
