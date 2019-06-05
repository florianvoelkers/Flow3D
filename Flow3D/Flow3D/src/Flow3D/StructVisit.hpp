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
		std::cout << "  " << name << ": " << t << std::endl;
	}
};

template <typename T>
void debug_print(const T & t) {
	std::cout << "Number of members: " << visit_struct::field_count(t);
	std::cout << "{\n";
	visit_struct::apply_visitor(debug_printer{}, t);
	std::cout << "}" << std::endl;
}