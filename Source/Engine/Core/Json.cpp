#include "Json.h"
#include "Logger.h"
#include "FileIO.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include <sstream>

namespace kiko
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer)) //!<read the file into the buffer using readFile() from FileIO.h, log warning if failed>
		{
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}
		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);
		// parse stream to json
		document.ParseStream(istream);
		if (!document.IsObject()) //!<check document is object>
		{
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}
		return true;
	}
	//int
	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetInt(); //<get c string of name>.<get int function>
		return true;
	}
	//float
	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetFloat(); //<get c string of name>.<get int function>
		return false;
	}

	//bool
	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetBool(); //<get c string of name>.<get int function>
		return true;
	}

	//string
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetString(); //<get c string of name>.<get int function>
		return true;
	}


	//vec2
	bool Json::Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required)
	{
		// check if 'name' member exists and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	//Color
	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required)
	{
		// check if 'name' member exists and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return false;
	}

	//Rect
	bool Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required)
	{
		// check if 'name' member exists and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return false;
	}

	//vector string
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required)
	{
		// check if 'name' member exists and is an array 
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsString())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data.push_back(array[i].GetString());
		}
		return false;
	}

	//vector int
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required)
	{
		// check if 'name' member exists and is an array 
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data.push_back(array[i].GetFloat());
		}
		return false;
	}

}