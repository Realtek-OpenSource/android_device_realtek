/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _VIDEORPC_SYSTEM_H_RPCGEN
#define _VIDEORPC_SYSTEM_H_RPCGEN

#include <RPCstruct.h>

#include "VideoRPC_System_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <RPCBaseDS.h>
#include <VideoRPCBaseDS.h>
#include <AudioRPCBaseDS.h>
#include <AudioRPC_System.h>

#define VIDEO_SYSTEM 201
#define VERSION 0

struct REG_STRUCT * VIDEO_SYSTEM_0_register(struct REG_STRUCT *rnode);

#if defined(__STDC__) || defined(__cplusplus)
#define VIDEO_RPC_VOUT_ToAgent_SetV2alpha 3090
extern  HRESULT * VIDEO_RPC_VOUT_ToAgent_SetV2alpha_0(u_char *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_VOUT_ToAgent_SetV2alpha_0_svc(u_char *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetSpeed 1010
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetSpeed_0(VIDEO_RPC_DEC_SET_SPEED *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetSpeed_0_svc(VIDEO_RPC_DEC_SET_SPEED *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel 1015
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel_0(VIDEO_RPC_DEC_SET_ERR_CONCEALMENT_LEVEL *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel_0_svc(VIDEO_RPC_DEC_SET_ERR_CONCEALMENT_LEVEL *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_Init 1020
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Init_0(VIDEO_RPC_DEC_INIT *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Init_0_svc(VIDEO_RPC_DEC_INIT *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetDeblock 1030
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDeblock_0(VIDEO_RPC_DEC_SET_DEBLOCK *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDeblock_0_svc(VIDEO_RPC_DEC_SET_DEBLOCK *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo 1035
extern  VIDEO_RPC_DEC_SEQ_INFO * VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo_0(long *, CLNT_STRUCT *);
extern  VIDEO_RPC_DEC_SEQ_INFO * VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo_0_svc(long *, RPC_STRUCT *, VIDEO_RPC_DEC_SEQ_INFO *);
#define VIDEO_RPC_DEC_ToAgent_BitstreamValidation 1040
extern  VIDEO_RPC_DEC_BV_RESULT * VIDEO_RPC_DEC_ToAgent_BitstreamValidation_0(VIDEO_RPC_DEC_BITSTREAM_BUFFER *, CLNT_STRUCT *);
extern  VIDEO_RPC_DEC_BV_RESULT * VIDEO_RPC_DEC_ToAgent_BitstreamValidation_0_svc(VIDEO_RPC_DEC_BITSTREAM_BUFFER *, RPC_STRUCT *, VIDEO_RPC_DEC_BV_RESULT *);
#define VIDEO_RPC_DEC_ToAgent_Capability 1045
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Capability_0(VIDEO_RPC_DEC_CAPABILITY *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Capability_0_svc(VIDEO_RPC_DEC_CAPABILITY *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass 1050
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass_0(VIDEO_RPC_DEC_CC_BYPASS_MODE *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass_0_svc(VIDEO_RPC_DEC_CC_BYPASS_MODE *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetDNR 1060
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDNR_0(VIDEO_RPC_DEC_SET_DNR *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDNR_0_svc(VIDEO_RPC_DEC_SET_DNR *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit 1065
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit_0(VIDEO_RPC_DEC_SET_REF_SYNC_LIMIT *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit_0_svc(VIDEO_RPC_DEC_SET_REF_SYNC_LIMIT *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat 1070
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat_0(VIDEO_RPC_THUMBNAIL_SET_VSCALER_OUTFORMAT *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat_0_svc(VIDEO_RPC_THUMBNAIL_SET_VSCALER_OUTFORMAT *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold 1080
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold_0(VIDEO_RPC_THUMBNAIL_SET_THRESHOLD *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold_0_svc(VIDEO_RPC_THUMBNAIL_SET_THRESHOLD *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_FLASH_ToAgent_SetOutput 1085
extern  HRESULT * VIDEO_RPC_FLASH_ToAgent_SetOutput_0(VIDEO_RPC_FLASH_SET_OUTPUT *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_FLASH_ToAgent_SetOutput_0_svc(VIDEO_RPC_FLASH_SET_OUTPUT *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber 1090
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber_0(VIDEO_RPC_THUMBNAIL_SET_STARTPIC *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber_0_svc(VIDEO_RPC_THUMBNAIL_SET_STARTPIC *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToAgent_PrivateInfo 1095
extern  VIDEO_RPC_DEC_PRIVATEINFO_OUTPUT_PARAMETERS * VIDEO_RPC_DEC_ToAgent_PrivateInfo_0(VIDEO_RPC_DEC_PRIVATEINFO_INPUT_PARAMETERS *, CLNT_STRUCT *);
extern  VIDEO_RPC_DEC_PRIVATEINFO_OUTPUT_PARAMETERS * VIDEO_RPC_DEC_ToAgent_PrivateInfo_0_svc(VIDEO_RPC_DEC_PRIVATEINFO_INPUT_PARAMETERS *, RPC_STRUCT *, VIDEO_RPC_DEC_PRIVATEINFO_OUTPUT_PARAMETERS *);
#define VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure 5040
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure_0(VIDEO_RPC_SUBPIC_DEC_CONFIGURE *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure_0_svc(VIDEO_RPC_SUBPIC_DEC_CONFIGURE *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_SUBPIC_DEC_ToAgent_Page 5050
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Page_0(VIDEO_RPC_SUBPIC_DEC_PAGE *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Page_0_svc(VIDEO_RPC_SUBPIC_DEC_PAGE *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_JPEG_ToAgent_DEC 6010
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_0(VIDEO_RPC_JPEG_DEC *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_0_svc(VIDEO_RPC_JPEG_DEC *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_JPEG_ToAgent_DEC_BATCH 6011
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_BATCH_0(VIDEO_RPC_JPEG_DEC_BATCH *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_BATCH_0_svc(VIDEO_RPC_JPEG_DEC_BATCH *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_TRANSITION_ToAgent_Start 6020
extern  HRESULT * VIDEO_RPC_TRANSITION_ToAgent_Start_0(VIDEO_RPC_TRANSITION_EFFECT *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_TRANSITION_ToAgent_Start_0_svc(VIDEO_RPC_TRANSITION_EFFECT *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_MIXER_FILTER_ToAgent_Configure 8010
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_Configure_0(VIDEO_RPC_MIXER_FILTER_CONFIGURE *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_Configure_0_svc(VIDEO_RPC_MIXER_FILTER_CONFIGURE *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow 8020
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow_0(VIDEO_RPC_MIXER_FILTER_CONFIGURE_WIN *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow_0_svc(VIDEO_RPC_MIXER_FILTER_CONFIGURE_WIN *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow 8030
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow_0(VIDEO_RPC_MIXER_FILTER_SET_MASTER_WIN *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow_0_svc(VIDEO_RPC_MIXER_FILTER_SET_MASTER_WIN *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame 8040
extern  HRESULT * VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame_0(VIDEO_RPC_MIXER_PLAY_ONE_MOTION_JPEG_FRAME *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame_0_svc(VIDEO_RPC_MIXER_PLAY_ONE_MOTION_JPEG_FRAME *, RPC_STRUCT *, HRESULT *);

#else /* K&R C */
#define VIDEO_RPC_VOUT_ToAgent_SetV2alpha 3090
extern  HRESULT * VIDEO_RPC_VOUT_ToAgent_SetV2alpha_0();
extern  HRESULT * VIDEO_RPC_VOUT_ToAgent_SetV2alpha_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetSpeed 1010
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetSpeed_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetSpeed_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel 1015
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetErrorConcealmentLevel_0_svc();
#define VIDEO_RPC_DEC_ToAgent_Init 1020
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Init_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Init_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetDeblock 1030
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDeblock_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDeblock_0_svc();
#define VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo 1035
extern  VIDEO_RPC_DEC_SEQ_INFO * VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo_0();
extern  VIDEO_RPC_DEC_SEQ_INFO * VIDEO_RPC_DEC_ToAgent_GetVideoSequenceInfo_0_svc();
#define VIDEO_RPC_DEC_ToAgent_BitstreamValidation 1040
extern  VIDEO_RPC_DEC_BV_RESULT * VIDEO_RPC_DEC_ToAgent_BitstreamValidation_0();
extern  VIDEO_RPC_DEC_BV_RESULT * VIDEO_RPC_DEC_ToAgent_BitstreamValidation_0_svc();
#define VIDEO_RPC_DEC_ToAgent_Capability 1045
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Capability_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_Capability_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass 1050
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDecoderCCBypass_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetDNR 1060
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDNR_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetDNR_0_svc();
#define VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit 1065
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit_0();
extern  HRESULT * VIDEO_RPC_DEC_ToAgent_SetRefSyncLimit_0_svc();
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat 1070
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat_0();
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetVscalerOutputFormat_0_svc();
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold 1080
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold_0();
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetThreshold_0_svc();
#define VIDEO_RPC_FLASH_ToAgent_SetOutput 1085
extern  HRESULT * VIDEO_RPC_FLASH_ToAgent_SetOutput_0();
extern  HRESULT * VIDEO_RPC_FLASH_ToAgent_SetOutput_0_svc();
#define VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber 1090
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber_0();
extern  HRESULT * VIDEO_RPC_THUMBNAIL_ToAgent_SetStartPictureNumber_0_svc();
#define VIDEO_RPC_DEC_ToAgent_PrivateInfo 1095
extern  VIDEO_RPC_DEC_PRIVATEINFO_OUTPUT_PARAMETERS * VIDEO_RPC_DEC_ToAgent_PrivateInfo_0();
extern  VIDEO_RPC_DEC_PRIVATEINFO_OUTPUT_PARAMETERS * VIDEO_RPC_DEC_ToAgent_PrivateInfo_0_svc();
#define VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure 5040
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure_0();
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Configure_0_svc();
#define VIDEO_RPC_SUBPIC_DEC_ToAgent_Page 5050
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Page_0();
extern  HRESULT * VIDEO_RPC_SUBPIC_DEC_ToAgent_Page_0_svc();
#define VIDEO_RPC_JPEG_ToAgent_DEC 6010
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_0();
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_0_svc();
#define VIDEO_RPC_JPEG_ToAgent_DEC_BATCH 6011
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_BATCH_0();
extern  HRESULT * VIDEO_RPC_JPEG_ToAgent_DEC_BATCH_0_svc();
#define VIDEO_RPC_TRANSITION_ToAgent_Start 6020
extern  HRESULT * VIDEO_RPC_TRANSITION_ToAgent_Start_0();
extern  HRESULT * VIDEO_RPC_TRANSITION_ToAgent_Start_0_svc();
#define VIDEO_RPC_MIXER_FILTER_ToAgent_Configure 8010
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_Configure_0();
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_Configure_0_svc();
#define VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow 8020
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow_0();
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_ConfigureWindow_0_svc();
#define VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow 8030
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow_0();
extern  HRESULT * VIDEO_RPC_MIXER_FILTER_ToAgent_SetMasterWindow_0_svc();
#define VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame 8040
extern  HRESULT * VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame_0();
extern  HRESULT * VIDEO_RPC_MIXER_ToAgent_PlayOneMotionJpegFrame_0_svc();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_VIDEO_RPC_DEC_SET_SPEED (XDR *, VIDEO_RPC_DEC_SET_SPEED*);
extern  bool_t xdr_VIDEO_RPC_DEC_SET_ERR_CONCEALMENT_LEVEL (XDR *, VIDEO_RPC_DEC_SET_ERR_CONCEALMENT_LEVEL*);
extern  bool_t xdr_VIDEO_RPC_DEC_INIT (XDR *, VIDEO_RPC_DEC_INIT*);
extern  bool_t xdr_VIDEO_RPC_DEC_SET_DEBLOCK (XDR *, VIDEO_RPC_DEC_SET_DEBLOCK*);
extern  bool_t xdr_VIDEO_RPC_DEC_BITSTREAM_BUFFER (XDR *, VIDEO_RPC_DEC_BITSTREAM_BUFFER*);
extern  bool_t xdr_VIDEO_RPC_DEC_BV_RESULT (XDR *, VIDEO_RPC_DEC_BV_RESULT*);
extern  bool_t xdr_VIDEO_RPC_DEC_SEQ_INFO (XDR *, VIDEO_RPC_DEC_SEQ_INFO*);
extern  bool_t xdr_VIDEO_RPC_DEC_CC_BYPASS_MODE (XDR *, VIDEO_RPC_DEC_CC_BYPASS_MODE*);
extern  bool_t xdr_VIDEO_RPC_DEC_SET_DNR (XDR *, VIDEO_RPC_DEC_SET_DNR*);
extern  bool_t xdr_VIDEO_RPC_DEC_SET_REF_SYNC_LIMIT (XDR *, VIDEO_RPC_DEC_SET_REF_SYNC_LIMIT*);
extern  bool_t xdr_VIDEO_RPC_DEC_CAPABILITY (XDR *, VIDEO_RPC_DEC_CAPABILITY*);
extern  bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_VSCALER_OUTFORMAT (XDR *, VIDEO_RPC_THUMBNAIL_SET_VSCALER_OUTFORMAT*);
extern  bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_THRESHOLD (XDR *, VIDEO_RPC_THUMBNAIL_SET_THRESHOLD*);
extern  bool_t xdr_VIDEO_RPC_FLASH_SET_OUTPUT (XDR *, VIDEO_RPC_FLASH_SET_OUTPUT*);
extern  bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_STARTPIC (XDR *, VIDEO_RPC_THUMBNAIL_SET_STARTPIC*);
extern  bool_t xdr_VIDEO_RPC_SUBPIC_DEC_CONFIGURE (XDR *, VIDEO_RPC_SUBPIC_DEC_CONFIGURE*);
extern  bool_t xdr_VIDEO_RPC_SUBPIC_DEC_PAGE (XDR *, VIDEO_RPC_SUBPIC_DEC_PAGE*);
extern  bool_t xdr_VIDEO_RPC_JPEG_DEC_BATCH (XDR *, VIDEO_RPC_JPEG_DEC_BATCH*);
extern  bool_t xdr_VIDEO_RPC_TRANSITION_EFFECT (XDR *, VIDEO_RPC_TRANSITION_EFFECT*);
extern  bool_t xdr_VIDEO_RPC_MIXER_FILTER_CONFIGURE (XDR *, VIDEO_RPC_MIXER_FILTER_CONFIGURE*);
extern  bool_t xdr_VIDEO_RPC_MIXER_FILTER_CONFIGURE_WIN (XDR *, VIDEO_RPC_MIXER_FILTER_CONFIGURE_WIN*);
extern  bool_t xdr_VIDEO_RPC_MIXER_FILTER_SET_MASTER_WIN (XDR *, VIDEO_RPC_MIXER_FILTER_SET_MASTER_WIN*);
extern  bool_t xdr_VIDEO_RPC_MIXER_PLAY_ONE_MOTION_JPEG_FRAME (XDR *, VIDEO_RPC_MIXER_PLAY_ONE_MOTION_JPEG_FRAME*);

#else /* K&R C */
extern bool_t xdr_VIDEO_RPC_DEC_SET_SPEED ();
extern bool_t xdr_VIDEO_RPC_DEC_SET_ERR_CONCEALMENT_LEVEL ();
extern bool_t xdr_VIDEO_RPC_DEC_INIT ();
extern bool_t xdr_VIDEO_RPC_DEC_SET_DEBLOCK ();
extern bool_t xdr_VIDEO_RPC_DEC_BITSTREAM_BUFFER ();
extern bool_t xdr_VIDEO_RPC_DEC_BV_RESULT ();
extern bool_t xdr_VIDEO_RPC_DEC_SEQ_INFO ();
extern bool_t xdr_VIDEO_RPC_DEC_CC_BYPASS_MODE ();
extern bool_t xdr_VIDEO_RPC_DEC_SET_DNR ();
extern bool_t xdr_VIDEO_RPC_DEC_SET_REF_SYNC_LIMIT ();
extern bool_t xdr_VIDEO_RPC_DEC_CAPABILITY ();
extern bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_VSCALER_OUTFORMAT ();
extern bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_THRESHOLD ();
extern bool_t xdr_VIDEO_RPC_FLASH_SET_OUTPUT ();
extern bool_t xdr_VIDEO_RPC_THUMBNAIL_SET_STARTPIC ();
extern bool_t xdr_VIDEO_RPC_SUBPIC_DEC_CONFIGURE ();
extern bool_t xdr_VIDEO_RPC_SUBPIC_DEC_PAGE ();
extern bool_t xdr_VIDEO_RPC_JPEG_DEC_BATCH ();
extern bool_t xdr_VIDEO_RPC_TRANSITION_EFFECT ();
extern bool_t xdr_VIDEO_RPC_MIXER_FILTER_CONFIGURE ();
extern bool_t xdr_VIDEO_RPC_MIXER_FILTER_CONFIGURE_WIN ();
extern bool_t xdr_VIDEO_RPC_MIXER_FILTER_SET_MASTER_WIN ();
extern bool_t xdr_VIDEO_RPC_MIXER_PLAY_ONE_MOTION_JPEG_FRAME ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_VIDEORPC_SYSTEM_H_RPCGEN */
