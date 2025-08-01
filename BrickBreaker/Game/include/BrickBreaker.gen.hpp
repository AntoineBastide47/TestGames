// Auto-generated – DO NOT EDIT

#pragma once

namespace Engine::Reflection {
  #define SERIALIZE_BACKGROUND _e_SERIALIZE_RECORD \
  static inline const bool _reg = [] {\
    Engine::Reflection::ReflectionFactory::RegisterType<Background>("Background");\
    return true;\
  }();\
  void _e_save(const Engine::Reflection::Format format, Engine::JSON &json) const override { \
    if (format == Engine::Reflection::Format::JSON) { \
      json = Engine::JSON::Object();\
      Engine::Reflection::_e_saveImpl(active, format, json["active"]);\
    }\
  }\
  void _e_load(const Engine::Reflection::Format format, const Engine::JSON &json) override { \
    if (format == Engine::Reflection::Format::JSON) { \
      Engine::Reflection::_e_loadImpl(active, format, json["active"]);\
    }\
  }\
  private: 
} // namespace Engine::Reflection
