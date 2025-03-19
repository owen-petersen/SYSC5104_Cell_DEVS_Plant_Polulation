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
		const std::unordered_map<std::vector<int>, NeighborData<plantPopulationState, double>>& neighborhood) const override 
	{
		treeSpecies best_seed = treeSpecies::None;
		plantResources total_neighbourhood_resources = plantResources();

		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nStateResources = neighborData.state->current_resources;

			state.current_resources.water += 
				0.25 * (total_neighbourhood_resources.water - nStateResources.water);
			state.current_resources.sunlight += 
				0.25 * (total_neighbourhood_resources.sunlight - nStateResources.sunlight);
			state.current_resources.nitrogen += 
				0.25 * (total_neighbourhood_resources.nitrogen - nStateResources.nitrogen);
			state.current_resources.potassium += 
				0.25 * (total_neighbourhood_resources.potassium - nStateResources.potassium);

				
			best_seed = (treeSpecies)std::max((int)best_seed, (int)(neighborData.state->tree_type));
		}

		// Cell produces its own resources
		state.current_resources.water += state.produced_resources.water;
		state.current_resources.sunlight += state.produced_resources.sunlight;
		state.current_resources.nitrogen += state.produced_resources.nitrogen;
		state.current_resources.potassium += state.produced_resources.potassium;

		if (treeSpecies::None == state.tree_type) {
			state.tree_type = best_seed;
		} else {
			if ((state.req_to_survive.water > state.current_resources.water) ||
				(state.req_to_survive.sunlight > state.current_resources.sunlight) ||
				(state.req_to_survive.nitrogen > state.current_resources.nitrogen) ||
				(state.req_to_survive.potassium > state.current_resources.potassium))
			{
				// TODO Clear tree height/type to 0 when cell dies
			} else if ((state.req_to_grow.water > state.current_resources.water) ||
				(state.req_to_grow.sunlight > state.current_resources.sunlight) ||
				(state.req_to_grow.nitrogen > state.current_resources.nitrogen) ||
				(state.req_to_grow.potassium > state.current_resources.potassium))
			{
				// Cell survives but does not grow
				state.current_resources.water - state.req_to_survive.water;
				state.current_resources.sunlight - state.req_to_survive.sunlight;
				state.current_resources.nitrogen - state.req_to_survive.nitrogen;
				state.current_resources.potassium - state.req_to_survive.potassium;
			} else {
				// Cell grows
				state.current_resources.water - state.req_to_grow.water;
				state.current_resources.sunlight - state.req_to_grow.sunlight;
				state.current_resources.nitrogen - state.req_to_grow.nitrogen;
				state.current_resources.potassium - state.req_to_grow.potassium;
			
				state.tree_height++;
			}
		}
		return state;
	}

	[[nodiscard]] double outputDelay(const plantPopulationState& state) const override {
		return 1.;
	}
};

#endif //PLANT_POPULATION_CELL_HPP
