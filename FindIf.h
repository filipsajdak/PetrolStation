#pragma once
#include <algorithm>

template <typename Container, typename Fun>
auto find_if(Container&& c, Fun&& fun) {
	return std::find_if(std::begin(std::forward<Container>(c)),
		std::end(std::forward<Container>(c)),
		std::forward<Fun>(fun));
}

template <typename T>
auto WithID(T ID) {
	return [ID](auto&& e) {
		return e.GetID() == ID;
	};
};
