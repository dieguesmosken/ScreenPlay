// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: account.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "account.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace community {
class LoginDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Login>
     _instance;
} _Login_default_instance_;

namespace protobuf_account_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, username_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Login, password_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(Login)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Login_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "account.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _Login_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Login_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\raccount.proto\022\tcommunity\"+\n\005Login\022\020\n\010u"
      "sername\030\001 \001(\t\022\020\n\010password\030\002 \001(\tb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 79);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "account.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_account_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Login::kUsernameFieldNumber;
const int Login::kPasswordFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Login::Login()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_account_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:community.Login)
}
Login::Login(const Login& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  username_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.username().size() > 0) {
    username_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.username_);
  }
  password_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.password().size() > 0) {
    password_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.password_);
  }
  // @@protoc_insertion_point(copy_constructor:community.Login)
}

void Login::SharedCtor() {
  username_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  password_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

Login::~Login() {
  // @@protoc_insertion_point(destructor:community.Login)
  SharedDtor();
}

void Login::SharedDtor() {
  username_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  password_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Login::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Login::descriptor() {
  protobuf_account_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_account_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Login& Login::default_instance() {
  protobuf_account_2eproto::InitDefaults();
  return *internal_default_instance();
}

Login* Login::New(::google::protobuf::Arena* arena) const {
  Login* n = new Login;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Login::Clear() {
// @@protoc_insertion_point(message_clear_start:community.Login)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool Login::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:community.Login)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string username = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_username()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->username().data(), static_cast<int>(this->username().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "community.Login.username"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string password = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_password()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->password().data(), static_cast<int>(this->password().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "community.Login.password"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:community.Login)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:community.Login)
  return false;
#undef DO_
}

void Login::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:community.Login)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string username = 1;
  if (this->username().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->username().data(), static_cast<int>(this->username().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "community.Login.username");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->username(), output);
  }

  // string password = 2;
  if (this->password().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->password().data(), static_cast<int>(this->password().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "community.Login.password");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->password(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:community.Login)
}

::google::protobuf::uint8* Login::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:community.Login)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string username = 1;
  if (this->username().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->username().data(), static_cast<int>(this->username().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "community.Login.username");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->username(), target);
  }

  // string password = 2;
  if (this->password().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->password().data(), static_cast<int>(this->password().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "community.Login.password");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->password(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:community.Login)
  return target;
}

size_t Login::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:community.Login)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string username = 1;
  if (this->username().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->username());
  }

  // string password = 2;
  if (this->password().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->password());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Login::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:community.Login)
  GOOGLE_DCHECK_NE(&from, this);
  const Login* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Login>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:community.Login)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:community.Login)
    MergeFrom(*source);
  }
}

void Login::MergeFrom(const Login& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:community.Login)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.username().size() > 0) {

    username_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.username_);
  }
  if (from.password().size() > 0) {

    password_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.password_);
  }
}

void Login::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:community.Login)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Login::CopyFrom(const Login& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:community.Login)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Login::IsInitialized() const {
  return true;
}

void Login::Swap(Login* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Login::InternalSwap(Login* other) {
  using std::swap;
  username_.Swap(&other->username_);
  password_.Swap(&other->password_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Login::GetMetadata() const {
  protobuf_account_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_account_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Login

// string username = 1;
void Login::clear_username() {
  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& Login::username() const {
  // @@protoc_insertion_point(field_get:community.Login.username)
  return username_.GetNoArena();
}
void Login::set_username(const ::std::string& value) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:community.Login.username)
}
#if LANG_CXX11
void Login::set_username(::std::string&& value) {
  
  username_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:community.Login.username)
}
#endif
void Login::set_username(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:community.Login.username)
}
void Login::set_username(const char* value, size_t size) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:community.Login.username)
}
::std::string* Login::mutable_username() {
  
  // @@protoc_insertion_point(field_mutable:community.Login.username)
  return username_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Login::release_username() {
  // @@protoc_insertion_point(field_release:community.Login.username)
  
  return username_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Login::set_allocated_username(::std::string* username) {
  if (username != NULL) {
    
  } else {
    
  }
  username_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), username);
  // @@protoc_insertion_point(field_set_allocated:community.Login.username)
}

// string password = 2;
void Login::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& Login::password() const {
  // @@protoc_insertion_point(field_get:community.Login.password)
  return password_.GetNoArena();
}
void Login::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:community.Login.password)
}
#if LANG_CXX11
void Login::set_password(::std::string&& value) {
  
  password_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:community.Login.password)
}
#endif
void Login::set_password(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:community.Login.password)
}
void Login::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:community.Login.password)
}
::std::string* Login::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:community.Login.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Login::release_password() {
  // @@protoc_insertion_point(field_release:community.Login.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Login::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:community.Login.password)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace community

// @@protoc_insertion_point(global_scope)