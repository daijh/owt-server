// Copyright (C) <2019> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#include "SyncGroup.h"

namespace owt_base {

DEFINE_LOGGER(SyncGroup, "owt.SyncGroup");

SyncGroup::SyncGroup()
    : a_listener(NULL)
    , v_listener(NULL)
{
}

SyncGroup::~SyncGroup()
{
}

void SyncGroup::setVideoSyncedFrameListener(SyncedFrameListener *listener)
{
    v_listener = listener;
}

void SyncGroup::sendVideoFrame(const Frame& frame)
{
    if (v_listener)
        v_listener->OnSyncedFrame(frame);
}

void SyncGroup::setAudioSyncedFrameListener(SyncedFrameListener *listener)
{
    a_listener = listener;
}

void SyncGroup::sendAudioFrame(const Frame& frame)
{
    if (a_listener)
        a_listener->OnSyncedFrame(frame);
}

}
