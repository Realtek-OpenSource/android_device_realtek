/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(HAVE_PTHREADS)
#include <sys/resource.h>
#endif

#include <cutils/sched_policy.h>
#include <cutils/properties.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Sideband.h"

using namespace android;

int main(int, char**) {
#ifndef HACK_SIDEBAND 
    ALOGI("[Sideband] enable vendor Binder");
    android::ProcessState::initWithDriver("/dev/vndbinder");
#else
    ALOGI("[Sideband] enable system Binder");
    android::ProcessState::initWithDriver("/dev/binder");
#endif
    // When SF is launched in its own process, limit the number of
    // binder threads to 4.
    ProcessState::self()->setThreadPoolMaxThreadCount(4);

    // start the thread pool
    sp<ProcessState> ps(ProcessState::self());
    ps->startThreadPool();

    // instantiate Sideband
    sp<Sideband> sideband = new Sideband();

#if defined(HAVE_PTHREADS)
    setpriority(PRIO_PROCESS, 0, PRIORITY_URGENT_DISPLAY);
#endif
    set_sched_policy(0, SP_FOREGROUND);

    // initialize before clients can connect
    sideband->init();

    // publish surface sideband
    sp<IServiceManager> sm(defaultServiceManager());
#ifndef HACK_SIDEBAND 
    ALOGI("[Sideband] addSidebandService: %s", Sideband::getServiceName());
    sideband->setHackSideband(false);
    sm->addService(String16(Sideband::getServiceName()), sideband, false);
#else
    ALOGI("[Sideband] addSidebandService: Hack_Sideband");
    sideband->setHackSideband(true);
    sm->addService(String16("Hack_Sideband"), sideband, false);
#endif
    // run in this thread
    //sideband->run();

    IPCThreadState::self()->joinThreadPool();;
    return 0;
}
