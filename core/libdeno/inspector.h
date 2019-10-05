// Copyright 2018-2019 the Deno authors. All rights reserved. MIT license.
#ifndef INSPECTOR_H_
#define INSPECTOR_H_

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "v8/include/libplatform/libplatform.h"
#include "v8/include/v8-inspector.h"
#include "v8/include/v8.h"
#include "v8/src/base/macros.h"

#include "internal.h"

namespace deno {
class DenoIsolate;
}

namespace v8 {

enum { kInspectorClientIndex };

class InspectorFrontend final : public v8_inspector::V8Inspector::Channel {
 public:
  explicit InspectorFrontend(Local<Context> context);
  ~InspectorFrontend() override = default;

  deno::DenoIsolate* deno_;

 private:
  void sendResponse(
      int callId, std::unique_ptr<v8_inspector::StringBuffer> message) override;
  void sendNotification(
      std::unique_ptr<v8_inspector::StringBuffer> message) override;

  void flushProtocolNotifications() override {}

  void Send(const v8_inspector::StringView& string);

  Isolate* isolate_;
  Global<Context> context_;
};

class InspectorClient : public v8_inspector::V8InspectorClient {
 public:
  InspectorClient(Local<Context> context, deno::DenoIsolate* deno_);
  ~InspectorClient() override = default;

  void runMessageLoopOnPause(int context_group_id) {
    std::cerr << "pause\n";
    std::unique_lock<std::mutex> guard(pause_mutex_);
    std::cerr << "pause -- locked\n";
    paused_ = true;

    v8::Unlocker unlock_isolate(isolate_);

    pause_cv_.wait(guard, [&] { return !paused_; });
    std::cerr << "pause -- ended\n";
  }

  void quitMessageLoopOnPause() override {
    std::cerr << "end pause\n";
    std::unique_lock<std::mutex> guard(pause_mutex_);
    std::cerr << "end pause -- locked\n";
    paused_ = false;
    pause_cv_.notify_all();
    std::cerr << "end pause -- notified\n";
  }

  static v8_inspector::V8InspectorSession* GetSession(Local<Context> context);

  static const int kContextGroupId = 1;

  deno::DenoIsolate* deno_;
  std::unique_ptr<v8_inspector::V8Inspector> inspector_;
  std::unique_ptr<v8_inspector::V8InspectorSession> session_;
  std::unique_ptr<v8_inspector::V8Inspector::Channel> channel_;
  Global<Context> context_;
  Isolate* isolate_;

  bool paused_;
  std::mutex pause_mutex_;
  std::condition_variable pause_cv_;
};

class DispatchOnInspectorBackendTask : public v8::Task {
 public:
  explicit DispatchOnInspectorBackendTask(
      v8_inspector::V8InspectorSession* session,
      std::unique_ptr<uint16_t[]> message, int length)
      : length_(length), message_(std::move(message)), session_(session) {}

  void Run() override {
    v8_inspector::StringView message_view(message_.get(), length_);
    session_->dispatchProtocolMessage(message_view);
  }

 private:
  int length_;
  std::unique_ptr<uint16_t[]> message_;
  v8_inspector::V8InspectorSession* session_;
};

}  // namespace v8

#endif  // INSPECTOR_H_
