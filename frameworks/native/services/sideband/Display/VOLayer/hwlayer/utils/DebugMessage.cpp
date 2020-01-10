#define ATRACE_TAG (ATRACE_TAG_VIDEO)
#include <cstring>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#include <cutils/compiler.h>
#include "DebugMessage.h"

#include <utils/Timers.h>
#include <utils/Trace.h>

#define PLOCK_PRINT ALOGD

void DebugMessage::updataATraceInfo(Client * /*client*/, struct Client::debug_message *message){
	char atrace_name[5][50];
	memset(atrace_name, 0, sizeof(atrace_name));
	sprintf(atrace_name[0], "buf (PLANE:%s ID:%d ts:%.2f ms)", getPlaneInfo(), message->bufferId, message->timestamp);
	sprintf(atrace_name[1], "%s display_time", getPlaneInfo());
	sprintf(atrace_name[2], "%s release_time", getPlaneInfo());
	sprintf(atrace_name[3], "%s displat_cnt", getPlaneInfo());
	sprintf(atrace_name[4], "%s drop_cnt", getPlaneInfo());
	if(atrace_start)
		ATRACE_END();
	ATRACE_BEGIN(atrace_name[0]);

	ATRACE_INT(atrace_name[1], message->display_time);
	ATRACE_INT(atrace_name[2], message->release_time);
	ATRACE_INT(atrace_name[3], message->display_cnt);
	ATRACE_INT(atrace_name[4], message->drop_cnt);

	atrace_start = true;
}
const char *DebugMessage::getPlaneInfo()
{
	switch(mPlane){
		case VO_VIDEO_PLANE_V1:
			return "V1";
		case VO_VIDEO_PLANE_V2:
			return "V2";
		default:
			return "UNKNOWN";
	}
}

DebugMessage::~DebugMessage()
{
	ATRACE_END();
}
