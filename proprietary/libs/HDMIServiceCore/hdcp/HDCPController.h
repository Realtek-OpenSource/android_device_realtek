#ifndef __HDCP_CONTROLLER_H__
#define __HDCP_CONTROLLER_H__

#include <hardware/hardware.h>
#include "hdcp/rtk_hdcp.h"

#define PK_SIZE 280
#define AKSV_SIZE 5

namespace hdmi_hidl {

class HDCPController
{
public:
    static HDCPController& instance();

    HDCPController();
    ~HDCPController();

    bool enableHDCP();
    bool disableHDCP();
    bool queryStatus(int* status);
    bool querySink(int* capable);
    bool getKsvList(struct hdcp_ksvlist_info *info);
    bool saveHDCPToTemp();

    // API for HDCP 2.2
    void setHDCP22CipherInfo(
            unsigned char *riv,
            unsigned int riv_size,
            unsigned char *ks_xor_lc128,
            unsigned int ks_xor_lc128_size);

    void setHDCP22CipherEnable(int enabled);

private:
    static void cleanup();
    bool decPrivPKeyData(unsigned char *in, unsigned char *out, unsigned long len);
    bool checkKSV(unsigned char *ksvBuf);

    static HDCPController* mInstance;
    struct hdcp_device_t* sHDCPDevice;
    unsigned char PK[PK_SIZE];
    unsigned char Aksv[AKSV_SIZE];
};

}; // namespace hdmi_hidl
#endif
