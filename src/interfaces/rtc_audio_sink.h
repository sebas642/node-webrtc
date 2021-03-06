/* Copyright (c) 2019 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#pragma once

#include <cstddef>

#include <nan.h>
#include <webrtc/api/media_stream_interface.h>
#include <webrtc/api/scoped_refptr.h>

#include "src/node/async_object_wrap_with_loop.h"

namespace v8 { class FunctionTemplate; }
namespace v8 { class Object; }
namespace v8 { template <class T> class Local; }

namespace node_webrtc {

class RTCAudioSink
  : public AsyncObjectWrapWithLoop<RTCAudioSink>
  , public webrtc::AudioTrackSinkInterface {
 public:
  ~RTCAudioSink() override = default;

  static void Init(v8::Handle<v8::Object> exports);

  void OnData(
      const void* audio_data,
      int bits_per_sample,
      int sample_rate,
      size_t number_of_channels,
      size_t number_of_frames) override;

 protected:
  void Stop() override;

 private:
  explicit RTCAudioSink(rtc::scoped_refptr<webrtc::AudioTrackInterface>);

  static Nan::Persistent<v8::FunctionTemplate>& tpl();

  static NAN_METHOD(New);

  static NAN_GETTER(GetStopped);

  static NAN_METHOD(JsStop);

  bool _stopped = false;
  rtc::scoped_refptr<webrtc::AudioTrackInterface> _track;
};

}  // namespace node_webrtc
