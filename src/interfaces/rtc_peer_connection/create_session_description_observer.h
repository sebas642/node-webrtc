/* Copyright (c) 2019 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */
#pragma once

#include <memory>

#include <webrtc/api/jsep.h>
#include <v8.h>

#include "src/interfaces/rtc_peer_connection.h"
#include "src/node/promise.h"

namespace webrtc { class RTCError; }

namespace node_webrtc {

class RTCPeerConnection;

class CreateSessionDescriptionObserver
  : public PromiseCreator<RTCPeerConnection>
  , public webrtc::CreateSessionDescriptionObserver {
 public:
  CreateSessionDescriptionObserver(
      RTCPeerConnection* peer_connection,
      v8::Local<v8::Promise::Resolver> resolver)
    : PromiseCreator(peer_connection, resolver)
    , _peer_connection(peer_connection) {}

  void OnSuccess(webrtc::SessionDescriptionInterface*) override;

  void OnFailure(webrtc::RTCError) override;

 private:
  RTCPeerConnection* _peer_connection;
};

}  // namespace node_webrtc
