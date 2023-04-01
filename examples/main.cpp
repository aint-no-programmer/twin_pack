#include "twin_pack.h"
#include <iostream>

/* aint-no-programmer
 * 
 * Usage:
 *
 * Before serialization
 * 0. include "twin_pack.h"
 * 1. Inherit class from ISerializableObject
 * 2. In public part of class add macro PACK_IT:
 *														first arg - class name,
 *														other args - fields of class need to be serialzed
 * 3. That's all
 *
 * For serialization:
 *		- serialize / unserialize, examples below.
 *		- serialize / unserialize return bool result, if return value is false, than see msg_error for error code.
 *
 ******************************************************************************************************************************************************
 * Notes:
 *	- property_value - boost::variant wrapper for <bool, int64_t, double, std::string>
 */

using namespace std;

using twin_pack::ISerializableObject;
using twin_pack::property_value;

class Message : public ISerializableObject
{
public:
	int a;
	double b;
	std::string c;
	property_value d;
	std::vector<property_value> m_vector;
	std::map<std::string, property_value> m_map;

	PACK_IT(Message, m_vector)
};

class NestedMessage : public ISerializableObject
{
public:
	int a;
	double b;
	std::string c;
	property_value d;

	Message message;

	PACK_IT(NestedMessage, a, b, c, d, message)
};

int main()
{
	using nlohmann::json;

	Message message;
	message.a = 12;
	message.b = 34.56;
	message.c = "hello c++";
	message.m_vector = {12323.f, 123123213, 4, 56.67, "eve", true};
	message.m_map = {
		{"1", 123123123},
		{"2", 3434.3434},
		{"3", 12},
		{"4", 0},
		{"5", true},
		{"6", "QWERTY23123"},
		{"7", false}
	};

	//error message 
	std::string msg_error;
	auto print = [](const std::string& str) {std::cout << std::endl << str << std::endl; };
	
	//serializing binary
	json v_json;
	bool ok = message.serialize(v_json, msg_error);
	if (!ok) print("Unsuccessfull serialize/unserialize");

	//restore and serializing to binary
	Message restored_from_json;
	ok = restored_from_json.unserialize(v_json, msg_error);
	if (!ok) print("Unsuccessfull serialize/unserialize");
	
	std::stringstream stream;
	ok = restored_from_json.serialize(stream, msg_error);
	if (!ok) print("Unsuccessfull serialize/unserialize");
	
	//restore and serializing to json
	Message restored_from_binary;
	ok = restored_from_binary.unserialize(stream, msg_error);
	if (!ok) print("Unsuccessfull serialize/unserialize");
	
	json output_json;
	ok = restored_from_binary.serialize(output_json, msg_error);
	if (!ok) print("Unsuccessfull serialize/unserialize");
	std::cout << output_json.dump();
	
	//NestedMessage
	NestedMessage nestedMessage;

	//fill nestedMessage
	nestedMessage.a = 12;
	nestedMessage.b = (double)12 / 34;
	nestedMessage.c = "starlite";
	nestedMessage.d = false;
	nestedMessage.message = message;

	//binary serializing
	std::stringstream stream_2;
	nestedMessage.serialize(stream_2, msg_error);

	//restoring && serializing to json
	NestedMessage restored_nestedMessage;
	restored_nestedMessage.unserialize(stream_2, msg_error);
	restored_nestedMessage.serialize(output_json, msg_error);
	std::cout << "\n\nrestored_NestedMessage:\n" << output_json.dump();
	
	return 0;
}
