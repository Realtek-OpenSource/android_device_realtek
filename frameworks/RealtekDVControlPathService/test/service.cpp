#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <RealtekDVControlPathService.h>

using namespace android;

int main()
{
#ifdef DVCP_Is_Android8
    android::ProcessState::initWithDriver("/dev/vndbinder");
#endif
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGD("ServiceManager: %p", sm.get());
    defaultServiceManager()->addService(String16("realtek.DVCP"), new RealtekDVControlPathService());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
}
