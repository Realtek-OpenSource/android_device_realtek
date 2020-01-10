#ifndef _THREAD_WRAPPER_H_
#define _THREAD_WRAPPER_H_

#include <pthread.h>

#define THREAD_NAME_LEN     128

/**
 * For glinux porting, define our own ThreadWrapper
 */
class ThreadWrapper {

public:
    ThreadWrapper();
    virtual ~ThreadWrapper();
    virtual bool threadLoop() = 0;
    virtual void requestExitAndWait();
    virtual void run(const char *name);
    bool mExit;
    char mName[THREAD_NAME_LEN];

protected:
    pthread_t  mThread;
    //static void * threadEntry(void *instance);
};

#endif
