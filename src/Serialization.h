#pragma once

#include "cinder/Color.h"
#include "cinder/ChanTraits.h"
#include "rapidjson/prettywriter.h"
#include "Shape.h"

using namespace rapidjson;

inline std::string color_to_hex(ci::Color c)
{
	const uint8_t r = ci::CHANTRAIT<uint8_t>::convert(c.r);
	const uint8_t g = ci::CHANTRAIT<uint8_t>::convert(c.g);
	const uint8_t b = ci::CHANTRAIT<uint8_t>::convert(c.b);
	const int val = r << 16 | g << 8 | b;
	
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(6) << std::hex << val;
	return stream.str();
}

template<class T>
void serialize(T& object, Writer<FileWriteStream>& writer, const bool omit_object_start = false)
{
}

template<>
inline void serialize<ci::vec2>(ci::vec2& object, Writer<FileWriteStream>& writer, const bool omit_object_start)
{
	if (!omit_object_start)
		writer.StartObject();
	writer.String("x");
	writer.Double(object.x);
	writer.String("Y");
	writer.Double(object.y);
	if (!omit_object_start)
		writer.EndObject();
}

template<>
inline void serialize<shape>(shape& object, Writer<FileWriteStream>& writer, const bool omit_object_start)
{
	if (!omit_object_start)
		writer.StartObject();
	writer.String("type");
	writer.Int(object.type);
	writer.String("location");
	serialize<ci::vec2>(object.location, writer);
	writer.String("color");
	writer.String(color_to_hex(object.color).c_str());
	if (!omit_object_start)
		writer.EndObject();
}

template<>
inline void serialize<circle>(circle& object, Writer<FileWriteStream>& writer, const bool omit_object_start)
{
	if (!omit_object_start)
		writer.StartObject();
	serialize<shape>(object, writer, true);
	writer.String("radius");
	writer.Double(object.radius);
	if(!omit_object_start)
		writer.EndObject();
}

template<>
inline void serialize<square>(square& object, Writer<FileWriteStream>& writer, const bool omit_object_start)
{
	if (!omit_object_start)
		writer.StartObject();
	serialize<shape>(object, writer, true);
	writer.String("side");
	writer.Double(object.side);
	if(!omit_object_start)
	{
		writer.EndObject();
	}
}

template<>
inline void serialize<rectangle>(rectangle& object, Writer<FileWriteStream>& writer, const bool omit_object_start)
{
	if (!omit_object_start)
		writer.StartObject();
	serialize<shape>(object, writer, true);
	writer.String("size");
	serialize<ci::vec2>(object.size, writer);
	if (!omit_object_start)
		writer.EndObject();
}

template<class T>
void serialize_object(T& object, FileWriteStream& stream)
{
	PrettyWriter<FileWriteStream> writer(stream);
	writer.StartObject();
	serialize<T>(object, writer);
	writer.EndObject();
}

template<class T>
void serialize_array(T* data, const int count, FileWriteStream& stream)
{
	PrettyWriter<FileWriteStream> writer(stream);
	writer.StartArray();
	
	for(T* item = data; data < data + count; ++data)
	{
		serialize<T>(*data, writer);
	}
	
	writer.EndArray();
}