#pragma once

#include <visit_struct/visit_struct.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// debug_print
struct debug_printer {
	template <typename T>
	void operator()(const char * name, const T & t) const {
		std::cout << "  " << name << ": " << t << " of type " << typeid(t).name() << std::endl;
	}
};

using spair = std::pair<std::string, std::string>;
struct test_visitor_type {
	std::vector<spair> result;

	void operator()(const char* name, visit_struct::type_c<int>) {
		result.emplace_back(spair{ std::string{name}, "int" });
	}

	void operator()(const char* name, visit_struct::type_c<float>) {
		result.emplace_back(spair{ std::string{name}, "float" });
	}

	void operator()(const char* name, visit_struct::type_c<std::string>) {
		result.emplace_back(spair{ std::string{name}, "std::string" });
	}
};

using ppair = std::pair<const char *, const void *>;

struct test_visitor_two {
	std::vector<ppair> result;

	template <typename T>
	void operator()(const char * name, const T & t) {
		result.emplace_back(ppair{ name, static_cast<const void *>(&t) });
	}
};

template <typename T>
void debug_print(const T & t) {
	std::cout << "Number of members: " << visit_struct::field_count(t) << std::endl;
	std::cout << "{\n";
	visit_struct::apply_visitor(debug_printer{}, t);
	std::cout << "}" << std::endl;
}