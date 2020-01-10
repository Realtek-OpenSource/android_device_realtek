#ifndef HDMI_HDCP_API_H_
#define HDMI_HDCP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

// basic API to enable a new HDCP session.
typedef void (*auth_complete_handler)(unsigned char *riv, unsigned int riv_size, unsigned char *ks, unsigned int ks_size);
// basic API to pause HDCP cipher, but would not clear cipher state like frame counter, data counter.
// do it outside the HDCP engine
//typedef void (*pause_hdcp_cipher_handler)(void);
// basic API to disable entire HDCP engine, all state would be cleared, to start HDCP again, a key nego flow is required.
typedef void (*disable_hdcp_session_handler)(void);

// some basic API for HDMI to control HDCPTx22 engine
int enable_hdcptx_22();
int disable_hdcptx_22();
int get_hdcp_22_version_bit();
void set_hdcp_22_auth_complete_handler(auth_complete_handler handler);
//void set_hdcp_22_pause_hdcp_cipher_handler(pause_hdcp_cipher_handler handler);
void set_hdcp_22_disable_hdcp_session_handler(disable_hdcp_session_handler handler);

#ifdef __cplusplus
}
#endif

#endif

