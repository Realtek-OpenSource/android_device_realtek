#ifndef __HDMI_DEFINE__
#define __HDMI_DEFINE__

#include "VideoRPC_System.h"
#include "HDMITVSystemTypes.h"
#include "HdmiCommon.h"


#define be32_to_cpu(x)	do {x = __swap32((x));} while(0)

enum MEDIA_LINK_MODE {
	MEDIA_LINK_MODE_UNDEFINED = 0,
	MEDIA_LINK_MODE_HDMI = 1,
	MEDIA_LINK_MODE_MHL = 2
};

enum LINK_MODE {
	LINK_MODE_UNKNOWN = 0,
	LINK_HDMI_DISABLED = 1,
	LINK_HDMI_ENABLED = 2,
	LINK_MHL_ENABLED = 3,
	LINK_MODE_MAX
};

struct HDMI_Audio_desc
{
	unsigned char	coding_type;
	unsigned char	channel_count;
	unsigned char	sample_freq_all;
	unsigned char	sample_size_all;
	unsigned char	max_bit_rate_divided_by_8KHz;
};

struct HDMI_EDID_data
{
	int			VDB_length;	// Video Data Block
	unsigned char	VDB[132];
	char			ADB_length;	// Audio Data Block
	struct HDMI_Audio_desc	*ADB;
	unsigned char		*VSDB;
};

typedef enum CHECK_NAND_TYPE {
	UPDATE_NAND_CHECK_ONLY 			= 0,
	UPDATE_NAND_CHECK_WITH_WRITE 	= 1,
	UPDATE_NAND_WRITE_ONLY 		= 2,
	UPDATE_NAND_READ_ONLY 		= 3
} UPDATE_NAND_TYPE;

struct HDMI_EDID_Info
{
	int 		hdmiVersionMajor;
	int			hdmiVersionMinor;
	char		TV_Name[4];
	//u8 			prod_code[2];;
	//u32 		serial;
	//u8 			mfg_week;
	//u8 			mfg_year;
	int 		deepColor420;
	int 		maxTMDS;
};

#endif
