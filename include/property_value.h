#pragma once

#include <boost/variant.hpp>

/**
 * @brief property_value - unit storage for serialization
 */

#define TWIN_PACK_SERIALIZATION_TYPES boost::blank, bool, int64_t, double, std::string

namespace twin_pack
{
	class property_value : public boost::variant<TWIN_PACK_SERIALIZATION_TYPES>
	{
	public:
		property_value(const property_value& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) { }
		property_value(property_value&& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(std::move(value)) { }
		property_value& operator=(const property_value& value)
		{
			boost::variant<TWIN_PACK_SERIALIZATION_TYPES>::operator=(value);
			return *this;
		}
		property_value& operator=(property_value&& value)
		{
			boost::variant<TWIN_PACK_SERIALIZATION_TYPES>::operator=(std::move(value));
			return *this;
		}

		property_value() = default;
		~property_value() = default;

		property_value(const boost::variant<TWIN_PACK_SERIALIZATION_TYPES>& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) {}
		property_value(const bool& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) {}
		property_value(const int32_t& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(int64_t(value)) {}
		property_value(const int64_t& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) {}
		property_value(const float& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(double(value)) {}
		property_value(const double& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) {}
		property_value(const std::string& value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(value) {}
		property_value(const char* value) : boost::variant<TWIN_PACK_SERIALIZATION_TYPES>(std::string(value)) {}

		//overloading compare operator
		bool operator==(const property_value& rhs) const
		{
			return boost::variant<TWIN_PACK_SERIALIZATION_TYPES>::operator==(static_cast<boost::variant<TWIN_PACK_SERIALIZATION_TYPES>>(rhs));
		}
	};
}

