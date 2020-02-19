// Copyright (C) <2019> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#ifndef SyncGroup_h
#define SyncGroup_h

#include <logger.h>
#include "MediaFramePipeline.h"

namespace owt_base {

class SyncedFrameListener {
    DECLARE_LOGGER();

public:
    virtual void OnSyncedFrame(const Frame& frame) = 0;
};

class SyncGroup : public FrameSource {
    DECLARE_LOGGER();

public:
    SyncGroup();
    ~SyncGroup();

    void setVideoSyncedFrameListener(SyncedFrameListener *listener);
    void sendVideoFrame(const Frame& frame);

    void setAudioSyncedFrameListener(SyncedFrameListener *listener);
    void sendAudioFrame(const Frame& frame);

private:
    SyncedFrameListener *a_listener;
    SyncedFrameListener *v_listener;
};

}
#endif /* SyncGroup_h */
