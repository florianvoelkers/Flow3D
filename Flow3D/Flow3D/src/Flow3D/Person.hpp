#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "MovieInfo.hpp"

#include <iostream>

struct Person {
	// add this if you want to register private members:
	// template <>
	// auto meta::registerMembers<Person>();

	void SetAge(int a)
	{
		//std::cout << "Age is set by calling setter!\n";
		if (a >= 0 && a < 128) { // sorry, if you're older than 128
			age = a;
		}
		else {
			std::cout << "Can't set age. " << a << " is out of allowed range\n";
		}
	}

	int GetAge() const {
		std::cout << "Got age with getter!\n";
		return age;
	}

	void SetName(const std::string& name)
	{
		//std::cout << "Name is set by calling setter!\n";
		this->name = name;
	}

	const std::string& GetName() const
	{
		std::cout << "Got name with getter!\n";
		return name;
	}

	void SetIsMale(bool isMale)
	{
		this->isMale = isMale;
	}

	bool GetIsMale() const
	{
		return isMale;
	}

	int age;
	std::string name;
	bool isMale;
	float salary;
	std::unordered_map<std::string, std::vector<MovieInfo>> favouriteMovies;
};

#include <MetaStuff/include/Meta.h>

namespace meta {

	template <>
	inline auto registerMembers<Person>()
	{
		return members(
			member("age", &Person::GetAge, &Person::SetAge), // access through getter/setter only!
			member("name", &Person::GetName, &Person::SetName), // same, but ref getter/setter
			member("isMale", &Person::GetIsMale, &Person::SetIsMale),
			member("salary", &Person::salary),
			member("favouriteMovies", &Person::favouriteMovies)
		);
	}

} // end of namespace meta
