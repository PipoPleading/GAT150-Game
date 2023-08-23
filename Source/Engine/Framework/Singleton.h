#pragma once

namespace kiko
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton& other) = delete; //copy constructor
		Singleton& operator = (const Singleton& other) = delete; //these are added implicitly, just as a default constructor

		static T& Instance() //more fluid doing T& than Singleton&
		{
			static T instance;
			return instance;
		}

	protected:
		Singleton() = default;
	};

}