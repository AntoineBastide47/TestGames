// Auto-generated – DO NOT EDIT

#pragma once

namespace Engine::Reflection {
  #define SERIALIZE_BRICK _e_SERIALIZE_RECORD \
  static inline const bool _reg = [] {\
    Engine::Reflection::ReflectionFactory::RegisterType<Brick>("Brick");\
    return true;\
  }();\
  void _e_save(const Engine::Reflection::Format format, Engine::JSON &json) const override { \
    if (format == Engine::Reflection::Format::JSON) { \
      json = Engine::JSON::Object();\
      Engine::Reflection::_e_saveImpl(lives, format, json["lives"]);\
      Engine::Reflection::_e_saveImpl(isSolid, format, json["isSolid"]);\
    }\
  }\
  void _e_load(const Engine::Reflection::Format format, const Engine::JSON &json) override { \
    if (format == Engine::Reflection::Format::JSON) { \
      Engine::Reflection::_e_loadImpl(lives, format, json["lives"]);\
      Engine::Reflection::_e_loadImpl(isSolid, format, json["isSolid"]);\
    }\
  }\
  private: 
} // namespace Engine::Reflection
