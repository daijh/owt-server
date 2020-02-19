// Copyright (C) <2019> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include "MediaDefinitions.h"
#include "SyncGroupWrapper.h"

using namespace v8;

Persistent<Function> SyncGroup::constructor;
SyncGroup::SyncGroup() {};
SyncGroup::~SyncGroup() {};

void SyncGroup::Init(v8::Local<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "SyncGroup"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "close", close);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "SyncGroup"), tpl->GetFunction());
}

void SyncGroup::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  SyncGroup* obj = new SyncGroup();
  obj->me = new owt_base::SyncGroup();

  obj->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void SyncGroup::close(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  SyncGroup* obj = ObjectWrap::Unwrap<SyncGroup>(args.Holder());
  owt_base::SyncGroup* me = obj->me;
  delete me;
}
