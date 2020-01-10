#ifndef _COMMON_H_
#define _COMMON_H_

#include <cutils/log.h>

#ifdef ANDROID
#undef LOG_TAG
#define LOG_TAG "RTK_DV"
#endif

#define RTKDVLOG(fmt, args...) ALOGD(fmt, ##args);

#define RTKDV_ASSERT(cond)                                    \
{                                                             \
  if (!(cond))                                                \
  {                                                           \
      RTKDVLOG("ASSERT:[%s:%d]", __FUNCTION__, __LINE__);     \
  }                                                           \
}

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

void StartElapseTime(struct timespec &start);
float EndElapseTime(struct timespec &start);

void WarningPerSec(int sec, const char *p_str, ...);


#endif
