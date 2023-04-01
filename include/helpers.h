#pragma once

#include <map>
#include <vector>
#include <iostream>
#include "property_value.h"

/**
 * @brief property_value - unit storage for serialization
 */

struct output : public boost::static_visitor<>
{
	void operator()(boost::blank v) const
	{
		std::cout << "boost::blank" << std::endl;
	}
	void operator()(bool v) const
	{
		auto from_bool = [](const bool& value)->std::string {return value ? "true" : "false"; };
		std::cout << from_bool(v) << std::endl;
	}
	template<typename T>
	void operator()(T v) const
	{
		std::cout << (v) << std::endl;
	}

	template<typename T>
	static void print_variables(const T& value)
	{
		std::cout << value << std::endl;
	}

	static void print_variables(const std::vector<twin_pack::property_value>& value_vector)
	{
		std::cout << "\nvector\n" << std::endl;
		for (auto it = value_vector.begin(); it != value_vector.end(); ++it)
		{
			boost::apply_visitor(output(), *it);
		}
	}
	static void print_variables(const std::map<std::string, twin_pack::property_value>& value_map)
	{
		std::cout << "\nmap\n" << std::endl;
		for (auto it = value_map.begin(); it != value_map.end(); ++it)
		{
			auto from_bool = [](const bool& value)->std::string {return value ? "true" : "false"; };
			std::cout << it->first << " : ";
			boost::apply_visitor(output(), it->second);
		}
	}
};

/*--------------------------------------------------------------------------------------------------------*/
