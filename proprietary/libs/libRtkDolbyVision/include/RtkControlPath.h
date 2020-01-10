#ifndef __RTK_CONTROL_PATH_H__
#define __RTK_CONTROL_PATH_H__

#include "rtk_metadata.h"
#include <stdint.h>

#define DEF_G2L_LUT_SIZE_2P        8
#define DEF_G2L_LUT_SIZE           (1<<DEF_G2L_LUT_SIZE_2P)

typedef enum graphics_format_e
{
    GF_SDR_YUV = 0,  /* BT.709 YUV BT1886 */
    GF_SDR_RGB = 1,  /* BT.709 RGB BT1886 */
    GF_HDR_YUV = 2,  /* BT.2020 YUV PQ */
    GF_HDR_RGB = 3   /* BT.2020 RGB PQ */
} graphics_format_t;

typedef enum rtk_signal_format
{
    RTK_FORMAT_INVALID = -1,
    RTK_FORMAT_DOVI = 0,
    RTK_FORMAT_HDR10 = 1,
    RTK_FORMAT_SDR = 2,
    RTK_FORMAT_SDR_2020 = 3
} rtk_signal_format;

typedef enum rtk_cp_eotf_e
{
    RTK_CP_EOTF_BT1886 = 0,
    RTK_CP_EOTF_PQ = 1
} rtk_cp_eotf;

typedef enum rtk_cp_signal_range
{
    RTK_SIG_RANGE_SMPTE = 0,
    RTK_SIG_RANGE_FULL  = 1,
    RTK_SIG_RANGE_SDI   = 2
} rtk_cp_signal_range;

typedef enum rtk_cp_clr
{
    RTK_CP_CLR_YUV = 0,
    RTK_CP_CLR_RGB = 1,
    RTK_CP_CLR_IPT = 2
} rtk_cp_clr;

typedef enum rtk_cp_rgb_def
{
  RTK_RGB_DEF_P3d65 = 0,
  RTK_RGB_DEF_Dci,
  RTK_RGB_DEF_R709,
  RTK_RGB_DEF_R2020,
  RTK_RGB_DEF_Aces,
  RTK_RGB_DEF_Alexa,
  RTK_RGB_DEF_Num
} rtk_cp_rgb_def;

typedef enum rtk_cp_chroma_format
{
    RTK_CF_P420 = 0,
    RTK_CF_UYVY = 1,
    RTK_CF_P444 = 2
} rtk_cp_chroma_format;

typedef struct rtk_hdr10_param
{
    uint32_t min_display_mastering_luminance;
    uint32_t max_display_mastering_luminance;
    uint16_t Rx;
    uint16_t Ry;
    uint16_t Gx;
    uint16_t Gy;
    uint16_t Bx;
    uint16_t By;
    uint16_t Wx;
    uint16_t Wy;
    uint16_t max_content_light_level;
    uint16_t max_pic_average_light_level;
} rtk_hdr10_param;

typedef struct rtk_src_param
{
    int src_bit_depth;
    rtk_cp_chroma_format src_chroma_format;
    rtk_cp_signal_range src_yuv_range;
    int width;
    int height;
    rtk_hdr10_param hdr10_param;
} rtk_src_param;

typedef struct rtk_register_ipcore_1
{
    uint32_t SRange;
    uint32_t Srange_Inverse;
    uint32_t IPT_Scale;
    uint32_t IPT_Offset_01;
    uint32_t IPT_Offset_2;
    uint32_t Y2RGB_Coefficient_1;
    uint32_t Y2RGB_Coefficient_2;
    uint32_t Y2RGB_Coefficient_3;
    uint32_t Y2RGB_Coefficient_4;
    uint32_t Y2RGB_Coefficient_5;
    uint32_t Y2RGB_Offset_1;
    uint32_t Y2RGB_Offset_2;
    uint32_t Y2RGB_Offset_3;
    uint32_t EOTF;
    uint32_t A2B_Coefficient_1;
    uint32_t A2B_Coefficient_2;
    uint32_t A2B_Coefficient_3;
    uint32_t A2B_Coefficient_4;
    uint32_t A2B_Coefficient_5;
    uint32_t C2D_Coefficient_1;
    uint32_t C2D_Coefficient_2;
    uint32_t C2D_Coefficient_3;
    uint32_t C2D_Coefficient_4;
    uint32_t C2D_Coefficient_5;
    uint32_t C2D_Offset;
    uint32_t Active_area_left_top;
    uint32_t Active_area_bottom_right;
    uint32_t reserved_dm[17];
    uint32_t Composer_Mode;
    uint32_t VDR_Resolution;
    uint32_t Bit_Depth;
    uint32_t Coefficient_Log2_Denominator;
    uint32_t BL_Num_Pivots_Y;
    uint32_t BL_Pivot[5];
    uint32_t BL_Order;
    uint32_t BL_Coefficient_Y[8][3];
    uint32_t EL_NLQ_Offset_Y;
    uint32_t EL_Coefficient_Y[3];
    uint32_t Mapping_IDC_U;
    uint32_t BL_Num_Pivots_U;
    uint32_t BL_Pivot_U[3];
    uint32_t BL_Order_U;
    uint32_t BL_Coefficient_U[4][3];
    uint32_t MMR_Coefficient_U[22][2];
    uint32_t MMR_Order_U;
    uint32_t EL_NLQ_Offset_U;
    uint32_t EL_Coefficient_U[3];
    uint32_t Mapping_IDC_V;
    uint32_t BL_Num_Pivots_V;
    uint32_t BL_Pivot_V[3];
    uint32_t BL_Order_V;
    uint32_t BL_Coefficient_V[4][3];
    uint32_t MMR_Coefficient_V[22][2];
    uint32_t MMR_Order_V;
    uint32_t EL_NLQ_Offset_V;
    uint32_t EL_Coefficient_V[3];
    uint32_t reserved_comp[8];
} rtk_register_ipcore_1;

typedef struct rtk_register_ipcore_2
{
    uint32_t SRange;
    uint32_t Srange_Inverse;
    uint32_t Y2RGB_Coefficient_1;
    uint32_t Y2RGB_Coefficient_2;
    uint32_t Y2RGB_Coefficient_3;
    uint32_t Y2RGB_Coefficient_4;
    uint32_t Y2RGB_Coefficient_5;
    uint32_t Y2RGB_Offset_1;
    uint32_t Y2RGB_Offset_2;
    uint32_t Y2RGB_Offset_3;
    uint32_t Frame_Format;
    uint32_t EOTF;
    uint32_t A2B_Coefficient_1;
    uint32_t A2B_Coefficient_2;
    uint32_t A2B_Coefficient_3;
    uint32_t A2B_Coefficient_4;
    uint32_t A2B_Coefficient_5;
    uint32_t C2D_Coefficient_1;
    uint32_t C2D_Coefficient_2;
    uint32_t C2D_Coefficient_3;
    uint32_t C2D_Coefficient_4;
    uint32_t C2D_Coefficient_5;
    uint32_t C2D_Offset;
    uint32_t VDR_Resolution;
} rtk_register_ipcore_2;

typedef struct rtk_register_ipcore_3
{
    uint32_t IP_Version;
    uint32_t Control_Register;
    uint32_t Metadata_Program_Start;
    uint32_t Metadata_Program_Finish;
    uint32_t Interrupt_Raw;
    uint32_t Interrupt_Enable;
    uint32_t D2C_coefficient_1;
    uint32_t D2C_coefficient_2;
    uint32_t D2C_coefficient_3;
    uint32_t D2C_coefficient_4;
    uint32_t D2C_coefficient_5;
    uint32_t B2A_Coefficient_1;
    uint32_t B2A_Coefficient_2;
    uint32_t B2A_Coefficient_3;
    uint32_t B2A_Coefficient_4;
    uint32_t B2A_Coefficient_5;
    uint32_t Eotf_param_1;
    uint32_t Eotf_param_2;
    uint32_t IPT_Scale   ;
    uint32_t IPT_Offset_1;
    uint32_t IPT_Offset_2;
    uint32_t IPT_Offset_3;
    uint32_t Output_range_1;
    uint32_t Output_range_2;
    uint32_t RGB2YUV_coefficient_register1;
    uint32_t RGB2YUV_coefficient_register2;
    uint32_t RGB2YUV_coefficient_register3;
    uint32_t RGB2YUV_coefficient_register4;
    uint32_t RGB2YUV_coefficient_register5;
    uint32_t RGB2YUV_offset_0;
    uint32_t RGB2YUV_offset_1;
    uint32_t RGB2YUV_offset_2;
    uint32_t Reserved1[4];
    uint32_t Raw_metadata_statistics;
    uint32_t Raw_metadata[211];
    uint32_t Video_Diagnostic_Control_Register;
    uint32_t Frame_Error_Statistics_1;
    uint32_t Frame_Error_Statistics_2;
    uint32_t CRC_Control;
    uint32_t Input_CSC_CRC;
    uint32_t Output_CSC_CRC;
    uint32_t Reserved2[2];
} rtk_register_ipcore_3;

typedef struct rtk_dm_lut_ipcore
{
    uint32_t TmLutI[64*4];
    uint32_t TmLutS[64*4];
    uint32_t SmLutI[64*4];
    uint32_t SmLutS[64*4];
    uint32_t G2L[DEF_G2L_LUT_SIZE];
} rtk_dm_lut_ipcore;

typedef struct rtk_dv_control_path_param_s {
  rtk_signal_format  input_format;
  rtk_src_param src_param;
  rpu_ext_config_fixpt_main src_comp_metadata;
  struct dm_metadata dm_metadata;
} rtk_dv_control_path_param;


/*! @brief HDR10 infoframe data structure.
           This is the data structure used for the HDR10 infoframe.
           Details for each entry can be found in CEA-861.3
*/
typedef struct rtk_hdr_10_infoframe_s
{
    uint8_t infoframe_type_code      ;
    uint8_t infoframe_version_number ;
    uint8_t length_of_info_frame     ;
    uint8_t data_byte_1              ;
    uint8_t data_byte_2              ;
    uint8_t display_primaries_x_0_LSB;
    uint8_t display_primaries_x_0_MSB;
    uint8_t display_primaries_y_0_LSB;
    uint8_t display_primaries_y_0_MSB;
    uint8_t display_primaries_x_1_LSB;
    uint8_t display_primaries_x_1_MSB;
    uint8_t display_primaries_y_1_LSB;
    uint8_t display_primaries_y_1_MSB;
    uint8_t display_primaries_x_2_LSB;
    uint8_t display_primaries_x_2_MSB;
    uint8_t display_primaries_y_2_LSB;
    uint8_t display_primaries_y_2_MSB;
    uint8_t white_point_x_LSB        ;
    uint8_t white_point_x_MSB        ;
    uint8_t white_point_y_LSB        ;
    uint8_t white_point_y_MSB        ;
    uint8_t max_display_mastering_luminance_LSB;
    uint8_t max_display_mastering_luminance_MSB;
    uint8_t min_display_mastering_luminance_LSB;
    uint8_t min_display_mastering_luminance_MSB;
    uint8_t max_content_light_level_LSB        ;
    uint8_t max_content_light_level_MSB        ;
    uint8_t max_frame_average_light_level_LSB  ;
    uint8_t max_frame_average_light_level_MSB  ;
} rtk_hdr_10_infoframe_t;


typedef struct rtk_dv_vo_register_s {
  rtk_register_ipcore_1 dst_dm_reg1 __attribute__((aligned(16)));
  rtk_register_ipcore_2 dst_dm_reg2 __attribute__((aligned(16)));
  rtk_register_ipcore_3 dst_dm_reg3 __attribute__((aligned(16)));
  rtk_dm_lut_ipcore dv_lut1 __attribute__((aligned(16)));  //dm_lut_ipcore_s
  rtk_dm_lut_ipcore dv_lut2 __attribute__((aligned(16))); //dm_lut_ipcore_s
} rtk_dv_vo_register;


#ifdef __cplusplus
extern "C" {
#endif

//int Rtk_DV_Metadata_to_reg_service(DV_CP_SERVICE_SFD dv_sfd);
int Rtk_DV_Metadata_to_reg(rtk_dv_control_path_param *dv_cp_param, rtk_dv_vo_register *dv_vo_register, rtk_hdr_10_infoframe_t *rtk_out_info_frame);
void set_hdr10_param_default();
void set_cp_sink_param_default();
int Rtk_DV_Control_Path_Init(int is_from_service);
void Rtk_DV_Control_Path_Delete();
int RTK_Control_Path_is_Dolby_Vision_On();
#ifdef __cplusplus
}
#endif
#endif
