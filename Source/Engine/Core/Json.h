#pragma once
#include "rapidjson/include/rapidjson/document.h"
#include "Vector2.h"
#include <string>
#include <vector>
#include "Color.h"
#include "Rect.h"

#define READ_DATA(value, data) kiko::Json::Read(value, #data, data)
#define READ_DATA_REQURED(value, data) kiko::Json::Read(value, #data, data, true);
#define READ_NAME_DATA(value, name, data) kiko::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) kiko::Json::Read(value, name, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

namespace kiko
{

	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);

		//int
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		//float
		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		//bool
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		//string
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		//vec2
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& readVec2, bool required = false);
		//color
		static bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false);
		//rect
		static bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required = false); //rect not working?
		//vector of string
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required = false);
		//vector of int
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required = false);
	};

	using json_t = rapidjson::Value; //t stands for type here
} 