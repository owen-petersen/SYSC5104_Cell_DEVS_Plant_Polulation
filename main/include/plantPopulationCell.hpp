#ifndef PLANT_POPULATION_CELL_HPP
#define PLANT_POPULATION_CELL_HPP

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "plantPopulationState.hpp"

using namespace cadmium::celldevs;

//! Plant population cell.
class plantPopulation : public GridCell<plantPopulationState, double> {
	public:
	plantPopulation(const std::vector<int>& id, 
			const std::shared_ptr<const GridCellConfig<plantPopulationState, double>>& config
		  ): GridCell<plantPopulationState, double>(id, config) { }

	[[nodiscard]] plantPopulationState localComputation(plantPopulationState state,
		const std::unordered_map<std::vector<int>, NeighborData<plantPopulationState, double>>& neighborhood) const override {
		int live_neighbors = 0;

		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nState = neighborData.state;

			
		}
		

		return state;
	}

	[[nodiscard]] double outputDelay(const plantPopulationState& state) const override {
		return 1.;
	}
};

#endif //PLANT_POPULATION_CELL_HPP
