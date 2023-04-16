#pragma once

#include "property_value.h"
#include <nlohmann/json.hpp>

namespace nlohmann {
	template<>
	struct adl_serializer<twin_pack::property_value> {
		static void to_json(json& j, const twin_pack::property_value& value) {
			json v;
			switch (value.which())
			{
			case 0: v = { "value", "boost::blank" }; break;	//serialize null type
			case 1: v = { "value", boost::get<bool>(value) }; break;
			case 2: v = { "value", boost::get<int64_t>(value) }; break;
			case 3: v = { "value", boost::get<double>(value) }; break;
			case 4: v = { "value", boost::get<std::string>(value) }; break;
			default:
			{
				throw json::out_of_range::create(401, "Not valid type of property_value when use <to_json>. It is out of range [0 - 4]. Not valid type is " + std::to_string(value.which()), &j);
				break;
			}
			}
			j = { {"type", value.which()}, v };
		}
		static void from_json(const json& j, twin_pack::property_value& value) {
			auto type = j.at("type").get<int>();
			switch (type)
			{
			case 0: value = twin_pack::property_value(); break;
			case 1: value = j.at("value").get<bool>(); break;
			case 2: value = j.at("value").get<int64_t>(); break;
			case 3: value = j.at("value").get<double>(); break;
			case 4: value = j.at("value").get<std::string>(); break;
			default:
			{
				throw json::out_of_range::create(401, "Not valid json type of property_value when use <from_json>. It is out of range [0 - 4]. Not valid type is " + std::to_string(type), &j);
				break;
			}
			}
		}
	};
}
