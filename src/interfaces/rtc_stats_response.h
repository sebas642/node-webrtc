/* Copyright (c) 2019 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include <nan.h>

namespace v8 { class Function; }
namespace v8 { class Object; }
namespace v8 { template <class T> class Local; }

namespace node_webrtc {

class RTCStatsResponse
  : public Nan::ObjectWrap {
 public:
  RTCStatsResponse() = delete;

  ~RTCStatsResponse() override = default;

  //
  // Nodejs wrapping.
  //
  static void Init(v8::Handle<v8::Object> exports);

  static RTCStatsResponse* Create(double timestamp, const std::vector<std::map<std::string, std::string>>& reports);

 private:
  explicit RTCStatsResponse(double timestamp, const std::vector<std::map<std::string, std::string>>& reports)
    : _timestamp(timestamp), _reports(reports) {}

  static Nan::Persistent<v8::Function>& constructor();

  static NAN_METHOD(New);

  static NAN_METHOD(result);

  double _timestamp;
  std::vector<std::map<std::string, std::string>> _reports;
};

}  // namespace node_webrtc
