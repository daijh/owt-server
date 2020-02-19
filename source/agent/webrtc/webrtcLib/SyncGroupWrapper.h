// Copyright (C) <2019> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#ifndef SyncGroupWRAPPER_H
#define SyncGroupWRAPPER_H

#include <SyncGroup.h>
#include <node.h>
#include <node_object_wrap.h>

/*
 * Wrapper class of owt_base::SyncGroup
 */
class SyncGroup : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  owt_base::SyncGroup* me;

 private:
  SyncGroup();
  ~SyncGroup();
  static v8::Persistent<v8::Function> constructor;

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void close(const v8::FunctionCallbackInfo<v8::Value>& args);
};

#endif
