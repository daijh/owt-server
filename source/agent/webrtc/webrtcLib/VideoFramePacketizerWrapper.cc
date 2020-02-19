// Copyright (C) <2019> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include "MediaDefinitions.h"
#include "VideoFramePacketizerWrapper.h"
#include <MediaStream.h>
#include "WebRtcConnection.h"
#include "MediaStream.h"

#include "SyncGroupWrapper.h"

using namespace v8;

Persistent<Function> VideoFramePacketizer::constructor;
VideoFramePacketizer::VideoFramePacketizer() {};
VideoFramePacketizer::~VideoFramePacketizer() {};

void VideoFramePacketizer::Init(v8::Local<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "VideoFramePacketizer"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "close", close);

  NODE_SET_PROTOTYPE_METHOD(tpl, "bindTransport", bindTransport);
  NODE_SET_PROTOTYPE_METHOD(tpl, "unbindTransport", unbindTransport);
  NODE_SET_PROTOTYPE_METHOD(tpl, "enable", enable);
  NODE_SET_PROTOTYPE_METHOD(tpl, "ssrc", getSsrc);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setFoV", setFoV);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSyncGroup", setSyncGroup);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "VideoFramePacketizer"), tpl->GetFunction());
}

void VideoFramePacketizer::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  bool supportRED = (args[0]->ToBoolean())->BooleanValue();
  bool supportULPFEC = (args[1]->ToBoolean())->BooleanValue();
  VideoFramePacketizer* obj = new VideoFramePacketizer();
  int transportccExt = (args.Length() == 3) ? args[2]->IntegerValue() : -1;
  if (transportccExt > 0) {
    obj->me = new owt_base::VideoFramePacketizer(supportRED, supportULPFEC, true, false, transportccExt);
  } else {
    obj->me = new owt_base::VideoFramePacketizer(supportRED, supportULPFEC);
  }
  obj->dest = obj->me;

  obj->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void VideoFramePacketizer::close(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;
  delete me;
}

void VideoFramePacketizer::bindTransport(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  MediaStream* param = Nan::ObjectWrap::Unwrap<MediaStream>(Nan::To<v8::Object>(args[0]).ToLocalChecked());
  auto wr = std::shared_ptr<erizo::MediaStream>(param->me).get();

  //MediaSink* param = Nan::ObjectWrap::Unwrap<MediaSink>(args[0]->ToObject());
  erizo::MediaSink* transport = wr;

  me->bindTransport(transport);
}

void VideoFramePacketizer::unbindTransport(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  me->unbindTransport();
}

void VideoFramePacketizer::enable(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  bool b = (args[0]->ToBoolean())->BooleanValue();
  me->enable(b);
}

void VideoFramePacketizer::getSsrc(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  uint32_t ssrc = me->getSsrc();
  args.GetReturnValue().Set(Number::New(isolate, ssrc));
}

void VideoFramePacketizer::setFoV(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  int yaw = args[0]->Int32Value();
  int pitch = args[1]->Int32Value();
  me->setFoV(yaw, pitch);
}

void VideoFramePacketizer::setSyncGroup(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  VideoFramePacketizer* obj = ObjectWrap::Unwrap<VideoFramePacketizer>(args.Holder());
  owt_base::VideoFramePacketizer* me = obj->me;

  SyncGroup* param = node::ObjectWrap::Unwrap<SyncGroup>(args[0]->ToObject());
  owt_base::SyncGroup* syncGroup = param->me;

  me->SetSyncGroup(syncGroup);
}

