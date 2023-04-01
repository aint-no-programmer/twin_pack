#pragma once

#include "property_value.h"

/*
 * 1. Forward declaration of the template specialization need for correct configuring on Linux,
 * (otherwise msgpack's specializations are not found)
 * 
 * 2. After declaring the template specialization, we include <msgpack.hpp> and make the actual definition of specializations.
 * 
 * Look at: https://gist.github.com/redboltz/3ef4718a9e4429b21e21
 */

#include <msgpack/object_fwd_decl.hpp>
#include "msgpack/pack_decl.hpp"

namespace msgpack {
	inline twin_pack::property_value& operator>>(object const& o, twin_pack::property_value& v);
	template <typename Stream>
	inline packer<Stream>& operator<< (packer<Stream>& o, const twin_pack::property_value& v);
}

#include <msgpack.hpp>

/*-----------------------------------------------------------------------------------------------------------------------------*/
// Custom converter for property_value
namespace msgpack {

	// Convert from msgpacl::object to property_value.
	inline twin_pack::property_value& operator>>(object const& o, twin_pack::property_value& v) {
		switch (o.type) {
		case type::BOOLEAN:
		{
			v = bool();
			const auto temp = boost::get<bool>(&v);
			o.convert(temp);
			break;
		}
		//make int64_t anyway
		case type::POSITIVE_INTEGER:
		{
			v = int64_t();
			const auto temp = boost::get<int64_t>(&v);
			o.convert(temp);
			break;
		}
		//make int64_t anyway
		case type::NEGATIVE_INTEGER:
		{
			v = int64_t();
			const auto temp = boost::get<int64_t>(&v);
			o.convert(temp);
			break;
		}
		//make double anyway
		case type::FLOAT32:
		{
			v = double();
			const auto temp = boost::get<double>(&v);
			o.convert(temp);
			break;
		}
		case type::FLOAT64:
		{
			v = double();
			const auto temp = boost::get<double>(&v);
			o.convert(temp);
			break;
		}
		case type::STR:
		{
			v = std::string();
			const auto temp = boost::get<std::string>(&v);
			o.convert(temp);
			break;
		}
		//just in case
		case type::NIL:
			v = twin_pack::property_value();
			break;
		default:
			throw msgpack::type_error();
			break;
		}
		return v;
	}


	// Convert from property_value to msgpacl::object.
	template <typename Stream>
	struct packer_imp :boost::static_visitor<void> {
		void operator()(boost::blank const& value) const {
			//serialize to NIL type
			o_.pack(msgpack::type::nil_t());
		}
		template <typename T>
		void operator()(T const& value) const {
			o_.pack(value);
		}
		packer_imp(packer<Stream>& o) :o_(o) {}
		packer<Stream>& o_;
	};

	template <typename Stream>
	inline packer<Stream>& operator<< (packer<Stream>& o, const twin_pack::property_value& v)
	{
		boost::apply_visitor(packer_imp<Stream>(o), v);
		return o;
	}

} // namespace msgpack