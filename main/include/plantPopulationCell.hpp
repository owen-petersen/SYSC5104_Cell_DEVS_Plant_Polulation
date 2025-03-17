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
		plantResources total_neighbourhood_resources = plantResources();

		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nState = neighborData.state;

			total_neighbourhood_resources.water += nState.water;
			total_neighbourhood_resources.sunlight += nState.sunlight;
			total_neighbourhood_resources.nitrogen += nState.nitrogen;
			total_neighbourhood_resources.potassium += nState.potassium;
		}
		plantResources average_resources = plantPopulation();
		average_resources.water = total_neighbourhood_resources.water / neighborhood.size();
		average_resources.sunlight = total_neighbourhood_resources.sunlight / neighborhood.size();
		average_resources.nitrogen = total_neighbourhood_resources.nitrogen / neighborhood.size();
		average_resources.potassium = total_neighbourhood_resources.potassium / neighborhood.size();

		return state;
	}

	[[nodiscard]] double outputDelay(const plantPopulationState& state) const override {
		return 1.;
	}
};

#endif //PLANT_POPULATION_CELL_HPP
