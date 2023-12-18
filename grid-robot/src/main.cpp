#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "messaging.h"
#include "modules.h"
#include "sim.h"
#include "types.h"
#include "utils.h"

int main() {
	// Dummy map. Would recommend using a more complex one.
	// clang-format off
	std::vector<std::vector<int>> map = { // Remember that on the map, higher row indices == +y
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	// clang-format on

	std::shared_ptr<Robot> robot = std::make_shared<Robot>(map, 1, 1);
	std::shared_ptr<LiDAR> lidar = std::make_shared<LiDAR>(map);
	std::shared_ptr<DummyController> controller =
			std::make_shared<DummyController>();

	Sim sim(5, 1);
	sim.addModuleToExecution(robot);
	sim.addModuleToExecution(lidar);
	sim.addModuleToExecution(controller);

	sim.run();
	return 0;
}
