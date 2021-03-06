// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_error.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "msg_error.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::EnumDescriptor* SERR_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_msg_5ferror_2eproto() {
  protobuf_AddDesc_msg_5ferror_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "msg_error.proto");
  GOOGLE_CHECK(file != NULL);
  SERR_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_msg_5ferror_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_msg_5ferror_2eproto() {
}

void protobuf_AddDesc_msg_5ferror_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017msg_error.proto*\236\004\n\004SERR\022\013\n\007SERR_OK\020\000\022"
    "\022\n\016SERR_Exception\020\001\022\014\n\010SERR_Msg\020\002\022\017\n\013SER"
    "R_Notplt\020\003\022\020\n\014SERR_Illegal\020\004\022\014\n\010SERR_Arg"
    "\020\005\022\016\n\nSERR_State\020\006\022\017\n\013SERR_Remote\020\007\022\016\n\nS"
    "ERR_Noacc\020\010\022\017\n\013SERR_Passwd\020\t\022\024\n\020SERR_Inv"
    "alidName\020\n\022\022\n\016SERR_ExistName\020\013\022\024\n\020SERR_N"
    "ameChanged\020\014\022\021\n\rSERR_Nocopper\020\025\022\017\n\013SERR_"
    "Nogold\020\026\022\021\n\rSERR_Noticket\020\027\022\016\n\nSERR_Noma"
    "t\020\036\022\017\n\013SERR_Norole\020\037\022\022\n\016SERR_Notfriend\020P"
    "\022\022\n\016SERR_Friendyet\020Q\022\022\n\016SERR_HasInvite\020R"
    "\022\021\n\rSERR_Blackyet\020S\022\022\n\016SERR_FightGone\020T\022"
    "\025\n\021SERR_ReenterFight\020U\022\022\n\016SERR_ExitFight"
    "\020V\022\021\n\rSERR_IsBinded\020e\022\024\n\020SERR_IsForbidde"
    "n\020f\022\021\n\rSERR_HasLogin\020g\022\022\n\016SERR_EmptyMail"
    "\020h", 562);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "msg_error.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_msg_5ferror_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_msg_5ferror_2eproto {
  StaticDescriptorInitializer_msg_5ferror_2eproto() {
    protobuf_AddDesc_msg_5ferror_2eproto();
  }
} static_descriptor_initializer_msg_5ferror_2eproto_;
const ::google::protobuf::EnumDescriptor* SERR_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SERR_descriptor_;
}
bool SERR_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 21:
    case 22:
    case 23:
    case 30:
    case 31:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 101:
    case 102:
    case 103:
    case 104:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
