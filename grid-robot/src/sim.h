#pragma once

#include "modules.h"
#include <vector>

class Sim {
public:
	/**
	 * Initializes sim
	 * @param _run_time_ns Total runtime of simulation, in nanoseconds
	 * @param _dt_ns Step time of simulation, in nanoseconds
	 */
	Sim(uint32_t _run_time_ns, uint32_t _dt_ns)
			: run_time_ns(_run_time_ns), dt_ns(_dt_ns) {
		this->current_time_ns = 0;
	};

	/**
	 * @brief Adds modules to sim to execute. Modules are executed
	 * in the order they are added; e.g., if you add a Controller first,
	 * followed by a LiDAR, at every tick, the Controller will execute first.
	 * @param sim_module A shared pointer to the sim module to you want to execute
	 */
	void addModuleToExecution(std::shared_ptr<ModuleBase> sim_module) {
		this->sim_modules.push_back(sim_module);
	}

	/**
	 * @brief Runs sim to completion. At every tick, calls
	 * the updateState() function on each of the added modules, in the order
	 * they were added
	 */
	void run() {
		while (this->current_time_ns <= this->run_time_ns) {
			for (auto &sim_module : this->sim_modules) {
				sim_module->updateState(this->current_time_ns);
			}
			this->current_time_ns += this->dt_ns;
		}
	}

private:
	uint32_t current_time_ns;
	uint32_t run_time_ns;
	uint32_t dt_ns;
	std::vector<std::shared_ptr<ModuleBase>> sim_modules;
};
