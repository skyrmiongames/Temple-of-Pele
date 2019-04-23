#pragma once

#include <cstdarg>
#include <cmath>

/**
Check to see if a value is in a list of values. 

@param value_to_check the value to check the existence of in the variadic list of arguments
@param comparison_value_count the number of veriadic arguments
@param ... list of arguments identical in type to value_to_check to check if value_to_check is among.
@return true if value_to_check is in the first comparison_value_count veriadic arguments, false otherwise.
*/
template <typename T>
bool oneof(T value_to_check, int comparison_value_count, ...) {
	va_list args;
	va_start(args, comparison_value_count);

	bool ret = false;

	for (int i = 0; i < comparison_value_count && !ret; i++) {
		ret |= value_to_check == va_arg(args, T);
	}

	va_end(args);

	return ret;
}

float angleTo(sf::Vector2f start, sf::Vector2f end) {
	return std::atan( // This enemy is 1, player is 2.
		(-end.y + start.y) /
		 (end.x - start.x)
	) + (start.x > end.x ? PI : 0);
}