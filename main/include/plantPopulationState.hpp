#ifndef PLANT_POPULATION_STATE_HPP_
#define PLANT_POPULATION_STATE_HPP_

#include <iostream>
#include <nlohmann/json.hpp>

//! Plant population cell state.
struct plantPopulationState {
	bool life;

	//! Default constructor function.
	plantPopulationState() : life(false) {}
};

//! It prints the life of the cell in an output stream.
std::ostream& operator<<(std::ostream& os, const plantPopulationState& x) {
	os << "<" << ((x.life)? 1 : 0) << ">";
	return os;
}

//! The simulator must be able to compare the equality of two state objects
bool operator!=(const plantPopulationState& x, const plantPopulationState& y) {
	return x.life != y.life;
}

//! It parses a JSON file and generates the corresponding plantPopulationState object.
void from_json(const nlohmann::json& j, plantPopulationState& s) {
	j.at("life").get_to(s.life);
}

#endif //PLANT_POPULATION_STATE_HPP_
