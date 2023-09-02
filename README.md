# twin_pack
Simple cross-platform (Windows/Linux) header-only library for binary and json serialization based on popular libraries **msgpack** and **nlohmann-json**
# example
```
#include "twin_pack.h"

using namespace std;

using twin_pack::ISerializableObject;
using twin_pack::property_value;

/*
 * Inherit class from ISerializableObject
 */
class TestMessage : public ISerializableObject
{
public:
	int a;
	double b;
	std::string c;

	/*
	 * property_value class based on boost::variant
	 */
	property_value d;
	std::vector<property_value> m_vector;
	std::map<std::string, property_value> m_map;

	/*
	 * Inherit class from ISerializableObject
	 * In public part of class add macro PACK_IT :
	 * first arg - class name,
	 * other args - fields of class need to be serialized
	*/
	PACK_IT(TestMessage, a, b, c, d, m_vector, m_map)
};

int main()
{
	using nlohmann::json;

	TestMessage test_message;
	test_message.a = 12;
	test_message.b = 34.56;
	test_message.c = "hello world";
	test_message.d = 123;
	test_message.m_vector = {12323.f, 123123213, 4, 56.67, "eve", true};
	test_message.m_map = {
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

	//serializing to json
	json first_json;
	bool ok = test_message.serialize(first_json, msg_error);
	std::cout << first_json.dump(2) << std::endl;

	//restoring from json
	TestMessage restored_from_json;
	ok = restored_from_json.unserialize(first_json, msg_error);

	//serializing to binary
	std::stringstream stream;
	ok = restored_from_json.serialize(stream, msg_error);
	
	//restoring from binary
	TestMessage restored_from_binary;
	ok = restored_from_binary.unserialize(stream, msg_error);

	//serialize to json for comparing
	json output_json;
	ok = restored_from_binary.serialize(output_json, msg_error);
	std::cout << output_json.dump(2) << std::endl;

	if (first_json == output_json)
	{
		std::cout << "\nequal\n";
	}

	return 0;
}
```
# dependency
twin_pack requires [boost](https://www.boost.org/), [msgpack](https://github.com/msgpack/msgpack-c/tree/cpp_master), [nlohmann-json](https://github.com/nlohmann/json) libraries. Tests depend on [googletest](https://github.com/google/googletest) framework and are linked with it, so if you want to build them (BUILD_TESTS=ON), you need to have this dependency installed.
# build
```
mkdir build
cd build
cmake .. -DBoost_DIR=boos_dir -Dnlohmann_json_DIR=nlohmann_json_dir -Dmsgpack-cxx_DIR=msgpack_dir -DGTest_DIR=gtest_dir -DBUILD_TESTS=ON
```
# license
twin_pack is licensed under MIT Software License, see the [LICENSE](LICENSE) file for details.
