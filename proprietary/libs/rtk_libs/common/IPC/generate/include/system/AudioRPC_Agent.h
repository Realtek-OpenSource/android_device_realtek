/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _AUDIORPC_AGENT_H_RPCGEN
#define _AUDIORPC_AGENT_H_RPCGEN

#include <RPCstruct.h>

#include "AudioRPC_Agent_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <RPCBaseDS.h>
#include <AudioRPCBaseDS.h>

#define AUDIO_AGENT 202
#define VERSION 0

struct REG_STRUCT * AUDIO_AGENT_0_register(struct REG_STRUCT *rnode);

#if defined(__STDC__) || defined(__cplusplus)
#define AUDIO_RPC_ToSystem_ErrorStatus 1
extern  HRESULT * AUDIO_RPC_ToSystem_ErrorStatus_0(AUDIO_RPC_ERROR *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_ErrorStatus_0_svc(AUDIO_RPC_ERROR *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_DeliverFlush 2
extern  HRESULT * AUDIO_RPC_ToSystem_DeliverFlush_0(AUDIO_RPC_SENDIO *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_DeliverFlush_0_svc(AUDIO_RPC_SENDIO *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_EndOfStream 3
extern  HRESULT * AUDIO_RPC_ToSystem_EndOfStream_0(AUDIO_RPC_SENDPIN_LONG *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_EndOfStream_0_svc(AUDIO_RPC_SENDPIN_LONG *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_ENC_GeneralInfo 11
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_GeneralInfo_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_GeneralInfo_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_ENC_FrameInfo 12
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_FrameInfo_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_FrameInfo_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_ENC_EndOfStream 13
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_EndOfStream_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_EndOfStream_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_DEC_GeneralInfo 21
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_GeneralInfo_0(AUDIO_RPC_DEC_GENERAL_INFO *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_GeneralInfo_0_svc(AUDIO_RPC_DEC_GENERAL_INFO *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_DEC_FrameInfo 22
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_FrameInfo_0(AUDIO_RPC_DEC_GENERAL_INFO *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_FrameInfo_0_svc(AUDIO_RPC_DEC_GENERAL_INFO *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate 31
extern  HRESULT * AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus 32
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus_0(AUDIO_RPC_SPDIF_CHANNEL_STATUS *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus_0_svc(AUDIO_RPC_SPDIF_CHANNEL_STATUS *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_AO_PostMastership 33
extern  HRESULT * AUDIO_RPC_ToSystem_AO_PostMastership_0(AUDIO_RPC_MASTERSHIP *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_AO_PostMastership_0_svc(AUDIO_RPC_MASTERSHIP *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_AO_ConfigDACDone 34
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ConfigDACDone_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ConfigDACDone_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_DAC_HardwareMute 40
extern  HRESULT * AUDIO_RPC_ToSystem_DAC_HardwareMute_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_DAC_HardwareMute_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_ADC_HardwareMute 41
extern  HRESULT * AUDIO_RPC_ToSystem_ADC_HardwareMute_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_ADC_HardwareMute_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_HashCheck 42
extern  RPCRES_LONG * AUDIO_RPC_ToSystem_HashCheck_0(AUDIO_RPC_HASH *, CLNT_STRUCT *);
extern  RPCRES_LONG * AUDIO_RPC_ToSystem_HashCheck_0_svc(AUDIO_RPC_HASH *, RPC_STRUCT *, RPCRES_LONG *);
#define AUDIO_RPC_ToSystem_HDMI_Mute 49
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Mute_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Mute_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_HDMI_Setting 50
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Setting_0(struct AUDIO_HDMI_SETTING_INFO *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Setting_0_svc(struct AUDIO_HDMI_SETTING_INFO *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_AudioHaltDone 51
extern  HRESULT * AUDIO_RPC_ToSystem_AudioHaltDone_0(long *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_AudioHaltDone_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_PrivateInfo 52
extern  HRESULT * AUDIO_RPC_ToSystem_PrivateInfo_0(AUDIO_RPC_PRIVATEINFO_TO_SYS *, CLNT_STRUCT *);
extern  HRESULT * AUDIO_RPC_ToSystem_PrivateInfo_0_svc(AUDIO_RPC_PRIVATEINFO_TO_SYS *, RPC_STRUCT *, HRESULT *);
#define AUDIO_RPC_ToSystem_ARMFW_PrivateInfo 53
extern  AUDIO_RPC_PRIVATEINFO_RETURNVAL * AUDIO_RPC_ToSystem_ARMFW_PrivateInfo_0(AUDIO_RPC_PRIVATEINFO_TO_SYS *, CLNT_STRUCT *);
extern  AUDIO_RPC_PRIVATEINFO_RETURNVAL * AUDIO_RPC_ToSystem_ARMFW_PrivateInfo_0_svc(AUDIO_RPC_PRIVATEINFO_TO_SYS *, RPC_STRUCT *, AUDIO_RPC_PRIVATEINFO_RETURNVAL *);
#define VIDEO_RPC_ToSystem_EndOfStream 61
extern  HRESULT * VIDEO_RPC_ToSystem_EndOfStream_0(VIDEO_RPC_ENDOFSTREAM *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_EndOfStream_0_svc(VIDEO_RPC_ENDOFSTREAM *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_DEC_ToSystem_FatalError 63
extern  HRESULT * VIDEO_RPC_DEC_ToSystem_FatalError_0(VIDEO_RPC_DEC_ERROR_INFO *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_DEC_ToSystem_FatalError_0_svc(VIDEO_RPC_DEC_ERROR_INFO *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_ToSystem_ScaleModeSCART 64
extern  HRESULT * VIDEO_RPC_ToSystem_ScaleModeSCART_0(long *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_ScaleModeSCART_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_ToSystem_VideoHaltDone 65
extern  HRESULT * VIDEO_RPC_ToSystem_VideoHaltDone_0(long *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_VideoHaltDone_0_svc(long *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_ToSystem_VideoAssistant 66
extern  RPCRES_LONG * VIDEO_RPC_ToSystem_VideoAssistant_0(VIDEO_RPC_VideoAssistant *, CLNT_STRUCT *);
extern  RPCRES_LONG * VIDEO_RPC_ToSystem_VideoAssistant_0_svc(VIDEO_RPC_VideoAssistant *, RPC_STRUCT *, RPCRES_LONG *);
#define VIDEO_RPC_ToSystem_DecoderMessage 67
extern  HRESULT * VIDEO_RPC_ToSystem_DecoderMessage_0(VIDEO_RPC_DEC_MESSAGE *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_DecoderMessage_0_svc(VIDEO_RPC_DEC_MESSAGE *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_ToSystem_DVControlPathService 68
extern  VIDEO_RPC_VOUT_GET_DV_REGISTER * VIDEO_RPC_ToSystem_DVControlPathService_0(int *, CLNT_STRUCT *);
extern  VIDEO_RPC_VOUT_GET_DV_REGISTER * VIDEO_RPC_ToSystem_DVControlPathService_0_svc(int *, RPC_STRUCT *, VIDEO_RPC_VOUT_GET_DV_REGISTER *);
#define VIDEO_RPC_ToSystem_PrivateInfo 69
extern  HRESULT * VIDEO_RPC_ToSystem_PrivateInfo_0(VIDEO_RPC_PRIVATEINFO_TO_SYS *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_PrivateInfo_0_svc(VIDEO_RPC_PRIVATEINFO_TO_SYS *, RPC_STRUCT *, HRESULT *);
#define VIDEO_RPC_ToSystem_OutputControl_Notify 70
extern  HRESULT * VIDEO_RPC_ToSystem_OutputControl_Notify_0(VIDEO_RPC_DMX_OUTPUT_CONTROL_TO_SYS *, CLNT_STRUCT *);
extern  HRESULT * VIDEO_RPC_ToSystem_OutputControl_Notify_0_svc(VIDEO_RPC_DMX_OUTPUT_CONTROL_TO_SYS *, RPC_STRUCT *, HRESULT *);

#else /* K&R C */
#define AUDIO_RPC_ToSystem_ErrorStatus 1
extern  HRESULT * AUDIO_RPC_ToSystem_ErrorStatus_0();
extern  HRESULT * AUDIO_RPC_ToSystem_ErrorStatus_0_svc();
#define AUDIO_RPC_ToSystem_DeliverFlush 2
extern  HRESULT * AUDIO_RPC_ToSystem_DeliverFlush_0();
extern  HRESULT * AUDIO_RPC_ToSystem_DeliverFlush_0_svc();
#define AUDIO_RPC_ToSystem_EndOfStream 3
extern  HRESULT * AUDIO_RPC_ToSystem_EndOfStream_0();
extern  HRESULT * AUDIO_RPC_ToSystem_EndOfStream_0_svc();
#define AUDIO_RPC_ToSystem_ENC_GeneralInfo 11
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_GeneralInfo_0();
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_GeneralInfo_0_svc();
#define AUDIO_RPC_ToSystem_ENC_FrameInfo 12
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_FrameInfo_0();
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_FrameInfo_0_svc();
#define AUDIO_RPC_ToSystem_ENC_EndOfStream 13
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_EndOfStream_0();
extern  HRESULT * AUDIO_RPC_ToSystem_ENC_EndOfStream_0_svc();
#define AUDIO_RPC_ToSystem_DEC_GeneralInfo 21
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_GeneralInfo_0();
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_GeneralInfo_0_svc();
#define AUDIO_RPC_ToSystem_DEC_FrameInfo 22
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_FrameInfo_0();
extern  HRESULT * AUDIO_RPC_ToSystem_DEC_FrameInfo_0_svc();
#define AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate 31
extern  HRESULT * AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate_0();
extern  HRESULT * AUDIO_RPC_ToSystem_AO_KaraokeModeIndicate_0_svc();
#define AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus 32
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus_0();
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ReportSPDIFStatus_0_svc();
#define AUDIO_RPC_ToSystem_AO_PostMastership 33
extern  HRESULT * AUDIO_RPC_ToSystem_AO_PostMastership_0();
extern  HRESULT * AUDIO_RPC_ToSystem_AO_PostMastership_0_svc();
#define AUDIO_RPC_ToSystem_AO_ConfigDACDone 34
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ConfigDACDone_0();
extern  HRESULT * AUDIO_RPC_ToSystem_AO_ConfigDACDone_0_svc();
#define AUDIO_RPC_ToSystem_DAC_HardwareMute 40
extern  HRESULT * AUDIO_RPC_ToSystem_DAC_HardwareMute_0();
extern  HRESULT * AUDIO_RPC_ToSystem_DAC_HardwareMute_0_svc();
#define AUDIO_RPC_ToSystem_ADC_HardwareMute 41
extern  HRESULT * AUDIO_RPC_ToSystem_ADC_HardwareMute_0();
extern  HRESULT * AUDIO_RPC_ToSystem_ADC_HardwareMute_0_svc();
#define AUDIO_RPC_ToSystem_HashCheck 42
extern  RPCRES_LONG * AUDIO_RPC_ToSystem_HashCheck_0();
extern  RPCRES_LONG * AUDIO_RPC_ToSystem_HashCheck_0_svc();
#define AUDIO_RPC_ToSystem_HDMI_Mute 49
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Mute_0();
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Mute_0_svc();
#define AUDIO_RPC_ToSystem_HDMI_Setting 50
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Setting_0();
extern  HRESULT * AUDIO_RPC_ToSystem_HDMI_Setting_0_svc();
#define AUDIO_RPC_ToSystem_AudioHaltDone 51
extern  HRESULT * AUDIO_RPC_ToSystem_AudioHaltDone_0();
extern  HRESULT * AUDIO_RPC_ToSystem_AudioHaltDone_0_svc();
#define AUDIO_RPC_ToSystem_PrivateInfo 52
extern  HRESULT * AUDIO_RPC_ToSystem_PrivateInfo_0();
extern  HRESULT * AUDIO_RPC_ToSystem_PrivateInfo_0_svc();
#define AUDIO_RPC_ToSystem_ARMFW_PrivateInfo 53
extern  AUDIO_RPC_PRIVATEINFO_RETURNVAL * AUDIO_RPC_ToSystem_ARMFW_PrivateInfo_0();
extern  AUDIO_RPC_PRIVATEINFO_RETURNVAL * AUDIO_RPC_ToSystem_ARMFW_PrivateInfo_0_svc();
#define VIDEO_RPC_ToSystem_EndOfStream 61
extern  HRESULT * VIDEO_RPC_ToSystem_EndOfStream_0();
extern  HRESULT * VIDEO_RPC_ToSystem_EndOfStream_0_svc();
#define VIDEO_RPC_DEC_ToSystem_FatalError 63
extern  HRESULT * VIDEO_RPC_DEC_ToSystem_FatalError_0();
extern  HRESULT * VIDEO_RPC_DEC_ToSystem_FatalError_0_svc();
#define VIDEO_RPC_ToSystem_ScaleModeSCART 64
extern  HRESULT * VIDEO_RPC_ToSystem_ScaleModeSCART_0();
extern  HRESULT * VIDEO_RPC_ToSystem_ScaleModeSCART_0_svc();
#define VIDEO_RPC_ToSystem_VideoHaltDone 65
extern  HRESULT * VIDEO_RPC_ToSystem_VideoHaltDone_0();
extern  HRESULT * VIDEO_RPC_ToSystem_VideoHaltDone_0_svc();
#define VIDEO_RPC_ToSystem_VideoAssistant 66
extern  RPCRES_LONG * VIDEO_RPC_ToSystem_VideoAssistant_0();
extern  RPCRES_LONG * VIDEO_RPC_ToSystem_VideoAssistant_0_svc();
#define VIDEO_RPC_ToSystem_DecoderMessage 67
extern  HRESULT * VIDEO_RPC_ToSystem_DecoderMessage_0();
extern  HRESULT * VIDEO_RPC_ToSystem_DecoderMessage_0_svc();
#define VIDEO_RPC_ToSystem_DVControlPathService 68
extern  VIDEO_RPC_VOUT_GET_DV_REGISTER * VIDEO_RPC_ToSystem_DVControlPathService_0();
extern  VIDEO_RPC_VOUT_GET_DV_REGISTER * VIDEO_RPC_ToSystem_DVControlPathService_0_svc();
#define VIDEO_RPC_ToSystem_PrivateInfo 69
extern  HRESULT * VIDEO_RPC_ToSystem_PrivateInfo_0();
extern  HRESULT * VIDEO_RPC_ToSystem_PrivateInfo_0_svc();
#define VIDEO_RPC_ToSystem_OutputControl_Notify 70
extern  HRESULT * VIDEO_RPC_ToSystem_OutputControl_Notify_0();
extern  HRESULT * VIDEO_RPC_ToSystem_OutputControl_Notify_0_svc();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_AUDIORPC_AGENT_H_RPCGEN */
