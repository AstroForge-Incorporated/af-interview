#pragma once

#include "types.h"
#include "utils.h"
#include <stdexcept>

/// Base class for all Simulation modules
class ModuleBase {
public:
	virtual void updateState(uint32_t current_time_ns){};
};

class Robot : public ModuleBase {
public:
	/**
	 * Robot constructor
	 * @param _map Map of environment
	 * @param init_x Initial x position of the robot. Must be within the map
	 * bounds
	 * @param init_y Initial y position of the robot. Must be within the map
	 * bounds
	 * @throws std::runtime_error Thrown if (init_x, init_y) refer to either
	 * occupied or out of bounds map positions
	 */
	Robot(Map _map, int init_x, int init_y) : map(_map) {
		if (!this->map.inBounds(init_x, init_y) || this->map(init_x, init_y) == 1) {
			throw std::runtime_error("Robot initialized in map location either out of bounds or in occupied square.");
		}
		this->control_sub = Topic<ControlMsg>::getInstance().subscribeTo();
		this->true_x = init_x;
		this->true_y = init_y;
	}

	/**
	 * @brief Robot tick function. Tries to execute control if there is an
	 * published control message, and publishes the true map position of the robot
	 * @param current_time_ns Current simulation time, in nanoseconds
	 */
	void updateState(uint32_t current_time_ns) override {
		if (!this->control_sub->empty()) {
			// Get control
			ControlMsg control_msg = this->control_sub->front();
			this->control_sub->pop();

			// Try to execute. If control places us out of bounds
			// or in an occupied cell, position doesn't change
			this->tryExecuteControl(control_msg);
		}
		// Write out true position
		TrueStateMsg true_state_msg(true_x, true_y, current_time_ns);
		Topic<TrueStateMsg>::getInstance().publishTo(true_state_msg);
		std::cout << "Robot at position: (" << this->true_x << ", " << this->true_y
							<< ")"
							<< "\n";
	}

	/**
	 * @brief Tries to execute control. If control would place the robot
	 * in free and in bounds map location, updates the position of the robot.
	 * @param control Requested control input
	 */
	void tryExecuteControl(const ControlMsg &control) {
		int new_x = this->true_x;
		int new_y = this->true_y;

		switch (control.direction) {
		case Direction::UP:
			new_y--;
		case Direction::DOWN:
			new_y++;
		case Direction::LEFT:
			new_x--;
		case Direction::RIGHT:
			new_x++;
		default:
			break;
		}

		if (this->map.inBounds(new_x, new_y) && this->map(new_x, new_y) == 0) {
			this->true_x = new_x;
			this->true_y = new_y;
		}
	}

private:
	Map map;
	int true_x;
	int true_y;
	std::shared_ptr<std::queue<ControlMsg>> control_sub;
};

/**
 * @brief The LiDAR object. LiDARs can detect obstacles
 * that are either directly above, directly below,
 * directly to the right, or directly to the left
 * of the robot, within 10 cells
 */
class LiDAR : public ModuleBase {
public:
	/**
	 * LiDAR constructor
	 * @param _map Map of environment
	 */
	LiDAR(Map _map) : map(_map) {
		this->num_increments = 4;
		this->max_range = 10;
		this->state_sub = Topic<TrueStateMsg>::getInstance().subscribeTo();
	}

	/**
	 * LiDAR tick function. Gets and publishes LiDAR scans
	 * @param current_time_ns Current simulation time, in nanoseconds
	 */
	void updateState(uint32_t current_time_ns) override {
		if (!this->state_sub->empty()) {
			TrueStateMsg true_state = this->state_sub->front();
			this->state_sub->pop();
			std::vector<LiDARPoint> point_cloud = this->getLiDARScan(true_state);
			LiDARScanMsg lidar_scan_msg(point_cloud);
			Topic<LiDARScanMsg>::getInstance().publishTo(lidar_scan_msg);
		}
	}

	/// Constructs LiDAR scan
	std::vector<LiDARPoint> getLiDARScan(const TrueStateMsg &true_state) const {
		std::pair<int, int> map_dims = this->map.getDims();

		std::vector<LiDARPoint> point_cloud;
		double ang_increment = 360.0 / this->num_increments;
		double theta = 0;

		for (int i = 0; i < num_increments; ++i) {
			theta = degToRad(ang_increment * i);
			for (double range = 0.0; range <= max_range; range += 0.5) {
				int grid_x = static_cast<int>(true_state.x + range * cos(theta));
				int grid_y = static_cast<int>(true_state.y + range * sin(theta));

				// Check to make sure is in bounds
				if (this->map.inBounds(grid_x, grid_y) &&
						this->map(grid_x, grid_y) == 1) {
					point_cloud.push_back(LiDARPoint(theta, range));
					break;
				}
			}
		}

		return point_cloud;
	}

private:
	// LiDAR parameters
	int num_increments;
	double max_range;

	// World map
	Map map;

	// Subscriber queue
	std::shared_ptr<std::queue<TrueStateMsg>> state_sub;
};

/**
* @brief Dummy controller, to demonstrate how to use the framework.
* Constantly outputs control to move the Robot to the right.
*/
class DummyController : public ModuleBase {
public:
	DummyController() {
		this->lidar_sub = Topic<LiDARScanMsg>::getInstance().subscribeTo();
	}

	void updateState(uint32_t current_time_ns) override {
		if (!this->lidar_sub->empty()) {
			LiDARScanMsg lidar_msg = this->lidar_sub->front();
			this->lidar_sub->pop();

			for (auto &point : lidar_msg.point_cloud) {
				std::cout << "Point: (" << point.theta << ", " << point.range << ")\n";
			}

			// Write dummy message out
			ControlMsg control_msg(Direction::RIGHT, current_time_ns);
			Topic<ControlMsg>::getInstance().publishTo(control_msg);
		}
	}

private:
	// Subscriber queue
	std::shared_ptr<std::queue<LiDARScanMsg>> lidar_sub;
};