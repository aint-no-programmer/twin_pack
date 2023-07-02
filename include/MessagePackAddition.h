#pragma once

#include "property_value.h"
#include <msgpack.hpp>

//Converter for property_value
namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

//boost::blank, bool, int64_t, double, std::string
template<>
struct convert<twin_pack::property_value> {
    msgpack::object const& operator()(msgpack::object const& o, twin_pack::property_value& v) const {
        if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
        if (o.via.array.size != 2) throw msgpack::type_error();

		const auto type = o.via.array.ptr[0].as<int>();

		switch (type) {
		case 0:
		{
			v = twin_pack::property_value();
			break;
		}
		case 1:
		{
			v = o.via.array.ptr[1].as<bool>();
			break;
		}
		case 2:
		{
			v = o.via.array.ptr[1].as<int64_t>();
			break;
		}
		case 3:
		{
			v = o.via.array.ptr[1].as<double>();
			break;
		}
		case 4:
		{
			v = o.via.array.ptr[1].as<std::string>();
			break;
		}
		default: 	
		{
			throw msgpack::type_error();
			break;
		}
		}
		
        return o;
    }
};

//Helper for converting from property_value to msgpack::object.
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

template<>
struct pack<twin_pack::property_value> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, twin_pack::property_value const& v) const {
        // packing member variables as an array.
        o.pack_array(2);
        o.pack(v.which());
		boost::apply_visitor(packer_imp<Stream>(o), v);
        return o;
    }
};

} // namespace adaptor
} // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack