#include "twin_pack.h"
#include <gtest/gtest.h>
#include <iostream>

#define TEST_OUTPUT_FLAG

#ifdef TEST_OUTPUT_FLAG
#define TEST_OUTPUT(x) std::cout << x << std::endl;
#else
#define TEST_OUTPUT(x) {}
#endif

using twin_pack::ISerializableObject;
using twin_pack::property_value;

/*Classes*/
/*--------------------------------------------------------------------------------------------------------*/
struct SimpleStruct
{
	int a;
	float b;
	double c;
	int64_t d;
	bool e;
	property_value f;

	PACKAGE_DEFINE(SimpleStruct, a, b, c, d, e, f)
};

class SimpleClass : public ISerializableObject
{
public:
	std::string str;
	SimpleStruct simple_struct;

	PACK_IT(SimpleClass, str, simple_struct)
};

class SomeMessage : public ISerializableObject
{
public:
	//fields
	property_value m_property_value;
	bool value_bool;
	int value_int;
	int64_t value_int64_t;
	float value_float;
	double value_double;
	std::string value_string;
	//containers
	std::vector<property_value> value_vector;
	std::map<std::string, property_value> value_map;
	//package
	PACK_IT(SomeMessage, value_bool, value_int, value_int64_t, value_float, value_double, value_string, value_vector, value_map, m_property_value)
};

class ComplexMessage : public ISerializableObject
{
public:
	std::string value_string;
	SomeMessage someMessage;

	PACK_IT(ComplexMessage, value_string, someMessage)
};

class BlankMessage : public ISerializableObject
{
public:
	property_value m_value_1, m_value_2;
	std::vector<property_value> m_value_vector;
	std::map<std::string, property_value> m_value_map;

	PACK_IT(BlankMessage, m_value_1, m_value_2, m_value_vector, m_value_map)
};

/*Auxiliary*/
/*--------------------------------------------------------------------------------------------------------*/
bool compare(const float& a, const float& b)
{
	return fabs(a - b) < std::numeric_limits<float>::epsilon();
}

bool compare(const double& a, const double& b)
{
	return fabs(a - b) < std::numeric_limits<double>::epsilon();
}

bool compare(const SomeMessage& first, const SomeMessage& second)
{
	return first.m_property_value == second.m_property_value &&
		first.value_bool == second.value_bool &&
		first.value_int == second.value_int &&
		first.value_int64_t == second.value_int64_t &&
		compare(first.value_float, second.value_float) &&
		compare(first.value_double, second.value_double) &&
		first.value_string == second.value_string &&
		first.value_vector == second.value_vector &&
		first.value_map == second.value_map;
}

bool compare(const ComplexMessage& first, const ComplexMessage& second)
{
	return first.value_string == second.value_string &&
		compare(first.someMessage, second.someMessage);
}

bool compare(const BlankMessage& first, const BlankMessage& second)
{
	return first.m_value_1 == second.m_value_1 &&
		first.m_value_2 == second.m_value_2 &&
		first.m_value_vector == second.m_value_vector &&
		first.m_value_map == second.m_value_map;
}


bool compare(const SimpleStruct& first, const SimpleStruct& second)
{
	return first.a == second.a &&
		first.b == second.b &&
		first.c == second.c &&
		first.d == second.d &&
		first.e == second.e &&
		first.f == second.f;
};

bool compare(const SimpleClass& first, const SimpleClass& second)
{
	return first.str == second.str &&
		compare(first.simple_struct, second.simple_struct);
};

/*Test classes*/
/*--------------------------------------------------------------------------------------------------------*/
class Test_of_SimpleClass : public ::testing::Test
{
protected:
	void SetUp()
	{
		first.str = "There is SimpleClass";

		first.simple_struct.a = 11;
		first.simple_struct.b = 12.12;
		first.simple_struct.c = 13.131313;
		first.simple_struct.d = 123123456789456123;
		first.simple_struct.e = false;
		first.simple_struct.f = "There is a simple struct.";
	}
	void TearDown()
	{

	}

	SimpleClass first;
	SimpleClass second;
};

class Test_of_SimpleStruct : public ::testing::Test
{
protected:
	void SetUp()
	{
		first.a = 11;
		first.b = 12.12;
		first.c = 13.131313;
		first.d = 123123456789456123;
		first.e = false;
		first.f = "There is a simple struct.";
	}
	void TearDown()
	{
		
	}

	SimpleStruct first;
	SimpleStruct second;
};

class Test_of_SomeMessage : public ::testing::Test
{
protected:
	void SetUp()
	{
		first_object.value_bool = true;
		first_object.value_int = 345;
		first_object.value_int64_t = 34342423423423424;
		first_object.value_float = 232.2323f;
		first_object.value_double = 2.232323232323;
		first_object.value_string = (const char*)"Hello world!";
		first_object.value_vector = { (int64_t)123, 12.21, (const char*)"kjsdkjskd123213", 123.12313f, true, false, (const char*)"true/false" };//123.12313
		first_object.value_map = { {"property_value", property_value()}, {"PropertyValue2", property_value(212.09090f)}, {"123", 12.21}, {"123213", 123.12313}, {"true", false}, {"true/false", (int64_t)54321}, {"string", (std::string)"bonum vinum laetificat cor hominis"} };
	}
	void TearDown()
	{

	}

	SomeMessage first_object;
	SomeMessage second_object;
};

class Test_of_ComplexMessage : public ::testing::Test
{
protected:
	void SetUp()
	{
		first_object.value_string = "Complex test";
		//
		first_object.someMessage.value_bool = true;
		first_object.someMessage.value_int = 345;
		first_object.someMessage.value_int64_t = 34342423423423424;
		first_object.someMessage.value_float = 232.2323f;
		first_object.someMessage.value_double = 2.232323232323;
		first_object.someMessage.value_string = (const char*)"Hello world!";
		first_object.someMessage.value_vector = { (int64_t)123, 12.21, (const char*)"kjsdkjskd123213", 123.12313f, true, false, (const char*)"true/false" };//123.12313
		first_object.someMessage.value_map = { {"property_value", property_value()}, {"PropertyValue2", property_value(212.09090f)}, {"123", 12.21}, {"123213", 123.12313}, {"true", false}, {"true/false", (int64_t)54321}, {"string", (std::string)"bonum vinum laetificat cor hominis"} };
	}
	void TearDown()
	{

	}

	ComplexMessage first_object;
	ComplexMessage second_object;
};

class Test_of_BlankMessage: public ::testing::Test
{
protected:
	void SetUp()
	{
		first_object.m_value_1 = property_value();
		first_object.m_value_vector = { 123, property_value(), 321 };
		first_object.m_value_map = { {"1", property_value()}, {"2", property_value(212.f)}, {"3", property_value()} };
	}
	void TearDown()
	{

	}

	BlankMessage first_object;
	BlankMessage second_object;
	BlankMessage temporary_object;
};

/*Tests*/
/*--------------------------------------------------------------------------------------------------------*/
TEST(property_value, default_blank)
{
	property_value value;
	ASSERT_EQ(value.which(), 0);
	boost::blank* gotten = boost::get<boost::blank>(&value);
	ASSERT_NE(gotten, nullptr);
}
TEST_F(Test_of_SimpleClass, json_test)
{

	TEST_OUTPUT("SimpleClass json test");
	nlohmann::json v_json;
	std::string msg_error;
	bool ok = false;
	ok = first.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	TEST_OUTPUT(v_json.dump());
	ok = second.unserialize(v_json, msg_error);
	ASSERT_TRUE(ok);

	TEST_OUTPUT("\t\tfirst");
	output::print_variables(first.str);
	output::print_variables(first.simple_struct.a);
	output::print_variables(first.simple_struct.b);
	output::print_variables(first.simple_struct.c);
	output::print_variables(first.simple_struct.d);
	output::print_variables(first.simple_struct.e);
	output::print_variables(first.simple_struct.f);

	TEST_OUTPUT("\t\tsecond");
	output::print_variables(second.str);
	output::print_variables(second.simple_struct.a);
	output::print_variables(second.simple_struct.b);
	output::print_variables(second.simple_struct.c);
	output::print_variables(second.simple_struct.d);
	output::print_variables(second.simple_struct.e);
	output::print_variables(second.simple_struct.f);

	ASSERT_EQ(compare(first, second), true);
}

TEST_F(Test_of_SimpleClass, binary_test)
{
	TEST_OUTPUT("SimpleClass binary test");
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	ok = second.unserialize(stream, msg_error);
	ASSERT_TRUE(ok);

	TEST_OUTPUT("\t\tfirst");
	output::print_variables(first.str);
	output::print_variables(first.simple_struct.a);
	output::print_variables(first.simple_struct.b);
	output::print_variables(first.simple_struct.c);
	output::print_variables(first.simple_struct.d);
	output::print_variables(first.simple_struct.e);
	output::print_variables(first.simple_struct.f);

	TEST_OUTPUT("\t\tsecond");
	output::print_variables(second.str);
	output::print_variables(second.simple_struct.a);
	output::print_variables(second.simple_struct.b);
	output::print_variables(second.simple_struct.c);
	output::print_variables(second.simple_struct.d);
	output::print_variables(second.simple_struct.e);
	output::print_variables(second.simple_struct.f);

	ASSERT_TRUE(compare(first, second));
}

TEST_F(Test_of_SomeMessage, binary_test)
{
	TEST_OUTPUT("binary_test");
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	ok = second_object.unserialize(stream, msg_error);
	ASSERT_TRUE(ok);

	TEST_OUTPUT("\t\tfirst_object");
	output::print_variables(first_object.value_vector);
	output::print_variables(second_object.value_map);
	TEST_OUTPUT("\t\tsecond_object");
	output::print_variables(first_object.value_vector);
	output::print_variables(second_object.value_map);

	ASSERT_TRUE(compare(first_object, second_object));
}

TEST_F(Test_of_SomeMessage, json_test)
{
	TEST_OUTPUT("json_test");
	nlohmann::json v_json;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	TEST_OUTPUT(v_json.dump());
	ok = second_object.unserialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	
	TEST_OUTPUT("\t\tfirst_object");
	output::print_variables(first_object.value_vector);
	output::print_variables(second_object.value_map);
	TEST_OUTPUT("\t\tsecond_object");
	output::print_variables(first_object.value_vector);
	output::print_variables(second_object.value_map);
	
	ASSERT_TRUE(compare(first_object, second_object));
}

TEST_F(Test_of_ComplexMessage, complex_message_binary_test)
{
	TEST_OUTPUT("complex_message_binary_test");
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	ok = second_object.unserialize(stream, msg_error);
	ASSERT_TRUE(ok);

	ASSERT_TRUE(compare(first_object, second_object));
}

TEST_F(Test_of_ComplexMessage, complex_message_json_test)
{
	using nlohmann::json;
	TEST_OUTPUT("complex_message_json_test");
	nlohmann::json v_json;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	TEST_OUTPUT(v_json.dump());
	ok = second_object.unserialize(v_json, msg_error);
	ASSERT_TRUE(ok);

	ASSERT_TRUE(compare(first_object, second_object));
}

TEST_F(Test_of_BlankMessage, blank_test_positive)
{
	using nlohmann::json;
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	ok = temporary_object.unserialize(stream, msg_error);
	ASSERT_TRUE(ok);
	json v_json;
	ok = temporary_object.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	ok = second_object.unserialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	
	ASSERT_TRUE(compare(first_object, second_object));
}

TEST_F(Test_of_BlankMessage, blank_test_negative)
{
	using nlohmann::json;
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	ok = temporary_object.unserialize(stream, msg_error);
	ASSERT_TRUE(ok);
	json v_json;
	ok = temporary_object.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	ok = second_object.unserialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	
	//make objects not equal
	second_object.m_value_1 = 5;

	ASSERT_FALSE(compare(first_object, second_object));
}

TEST_F(Test_of_SomeMessage, binary_unserialize_exception)
{
	using nlohmann::json;
	std::stringstream stream;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(stream, msg_error);
	ASSERT_TRUE(ok);
	stream.str("bad message");
	ok = second_object.unserialize(stream, msg_error);
	ASSERT_FALSE(ok);
	TEST_OUTPUT(msg_error)
}

TEST_F(Test_of_SomeMessage, json_unserialize_exception)
{
	using nlohmann::json;
	json v_json;
	std::string msg_error;
	bool ok = false;
	ok = first_object.serialize(v_json, msg_error);
	ASSERT_TRUE(ok);
	v_json = {"bad message"};
	ok = second_object.unserialize(v_json, msg_error);
	ASSERT_FALSE(ok);
	TEST_OUTPUT(msg_error)
}

/*--------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}