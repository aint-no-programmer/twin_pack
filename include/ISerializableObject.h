#pragma once

#include "property_value.h"
#include "MessagePackAddition.h"
#include "NlohmannJsonAddition.h"
#include <sstream>

namespace twin_pack
{

	class ISerializableObject
	{
	public:
		virtual ~ISerializableObject() = default;
		bool unserialize(const std::stringstream& stream, std::string& msg_error)
		{
			try
			{
				binary_unserialize(stream);
				return true;
			}
			catch (const msgpack::unpack_error& er)
			{
				msg_error = "msgpack unpack error: " + std::string(er.what());
				return false;
			}
			catch (const msgpack::type_error& er)
			{
				msg_error = "msgpack unpack error: " + std::string(er.what());
				return false;
			}
			catch (const std::bad_alloc& er)
			{
				msg_error = "msgpack unpack error: " + std::string(er.what());
				return false;
			}
			catch (...)
			{
				msg_error = "unknown msgpack unpack error while unserialize object";
				return false;
			}
		}
		bool serialize(std::stringstream& stream, std::string& msg_error)
		{
			try {
				binary_serialize(stream);
				return true;
			}
			catch (const std::bad_alloc& er)
			{
				msg_error = "msgpack pack error: " + std::string(er.what());
				return false;
			}
			catch (const std::runtime_error& er)
			{
				msg_error = "msgpack pack error: " + std::string(er.what());
				return false;
			}
			catch(...)
			{
				msg_error = "unknown msgpack pack error while serialize object";
				return false;
			}
		}
		bool unserialize(const nlohmann::json& a_json, std::string& msg_error)
		{
			try
			{
				json_unserialize(a_json);
				return true;
			}
			catch (const nlohmann::json::exception& e)
			{
				msg_error = "nlohmann::json unpack error: " + std::string(e.what());
				return false;
			}
			catch(...)
			{
				msg_error = "unknown nlohmann::json unpack error while serialize object";
				return false;
			}
		}
		bool serialize(nlohmann::json& a_json, std::string& msg_error)
		{
			try
			{
				json_serialize(a_json);
				return true;
			}
			catch (const nlohmann::json::exception& e)
			{
				msg_error = "nlohmann::json pack error: " + std::string(e.what());
				return false;
			}
			catch (...)
			{
				msg_error = "unknown nlohmann::json pack error while serialize object";
				return false;
			}
		}

	protected:
		virtual void json_serialize(nlohmann::json& a_json) = 0;
		virtual void json_unserialize(const nlohmann::json& a_json) = 0;
		virtual void binary_serialize(std::stringstream& stream) = 0;
		virtual void binary_unserialize(const std::stringstream& stream) = 0;
	};
}

/*Macro*/
/*=======================================================================================================*/
#define BINARY_PACK(stream)\
					{\
						msgpack::pack(stream, *this);\
					}

#define BINARY_UNPACK(stream)\
					{\
						std::string str(stream.str());\
						msgpack::unpack(str.data(), str.size())->convert(*this);\
					}

#define JSON_PACK(json)\
					{\
						json = *this;\
					}

#define JSON_UNPACK(json)\
					{\
						*this = json.get<std::remove_pointer<decltype(this)>::type>();\
					}

#define PACKAGE_BOX\
			void binary_serialize(std::stringstream& stream) override\
			{\
				BINARY_PACK(stream);\
			}\
			void binary_unserialize(const std::stringstream& stream) override\
			{\
				BINARY_UNPACK(stream);\
			}\
			void json_serialize(nlohmann::json& a_json) override\
			{\
				JSON_PACK(a_json)\
			}\
			void json_unserialize(const nlohmann::json& a_json) override\
			{\
				JSON_UNPACK(a_json)\
			}

#define PACKAGE_DEFINE(type, ...)\
	MSGPACK_DEFINE(__VA_ARGS__)\
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(type, __VA_ARGS__)\

#define PACK_IT(type, ...)\
	PACKAGE_DEFINE(type, __VA_ARGS__)\
	PACKAGE_BOX
/*========================================================================================================*/
