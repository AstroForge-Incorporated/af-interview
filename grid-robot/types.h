#pragma once

#include <vector>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct LiDARPoint {
	double theta;
	double range;
	LiDARPoint(double _theta, double _range) : theta(_theta), range(_range) {}
};

struct ControlMsg {
	Direction direction;
	uint32_t time_ns;
	ControlMsg(Direction _dir, uint32_t _time_ns)
			: direction(_dir), time_ns(_time_ns) {}
};

struct TrueStateMsg {
	int x;
	int y;
	uint32_t time_ns;
	TrueStateMsg(int _x, int _y, uint32_t _time_ns)
			: x(_x), y(_y), time_ns(_time_ns) {}
};

struct LiDARScanMsg {
	std::vector<LiDARPoint> point_cloud;
	uint32_t time_ns;
	LiDARScanMsg(std::vector<LiDARPoint> _point_cloud)
			: point_cloud(_point_cloud) {}
};

class Map {
public:
	Map(std::vector<std::vector<int>> _map) : map(_map) {
		this->dims = std::make_pair(this->map.size(), this->map[0].size());
	};

	/// Returns map dimensions as a (dim_y, dim_x) pair
	std::pair<int, int> getDims() const { return this->dims; }

	/**
	 * @brief Indexes map with map coordinates; returns 1 if
	 * map is occupied at that coordinate, else 0
	 */
	int operator()(int grid_x, int grid_y) const {
		if (!this->inBounds(grid_x, grid_y)) {
			throw std::runtime_error("Index is out of bounds.");
		}
		return this->map[grid_y][grid_x];
	}

	/**
	 * Checks whether input map coordinates are within the map bounds.
	 */
	bool inBounds(int grid_x, int grid_y) const {
		return (grid_y >= 0 && grid_y < this->dims.first && grid_x >= 0 &&
						grid_x < this->dims.second);
	}

private:
	std::vector<std::vector<int>> map;
	std::pair<int, int> dims;
};
