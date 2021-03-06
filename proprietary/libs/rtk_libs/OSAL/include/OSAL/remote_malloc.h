/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REMOTE_MALLOC_H_RPCGEN
#define _REMOTE_MALLOC_H_RPCGEN

#include <RPCstruct.h>

#include "remote_malloc_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <RPCstruct.h>

#define R_PROGRAM 98
#define R_VERSION 0

//struct REG_STRUCT * R_PROGRAM_0_register(struct REG_STRUCT *rnode);

#if defined(__STDC__) || defined(__cplusplus)
#define rmalloc 1
extern  int * rmalloc_0(int *, CLNT_STRUCT *);
extern  int * rmalloc_0_svc(int *, RPC_STRUCT *, int *);
#define rfree 2
extern  int * rfree_0(int *, CLNT_STRUCT *);
extern  int * rfree_0_svc(int *, RPC_STRUCT *, int *);

#else /* K&R C */
#define rmalloc 1
extern  int * rmalloc_0();
extern  int * rmalloc_0_svc();
#define rfree 2
extern  int * rfree_0();
extern  int * rfree_0_svc();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REMOTE_MALLOC_H_RPCGEN */
