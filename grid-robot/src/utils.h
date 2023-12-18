#pragma once

#include <numbers>

/// Converts input degrees to radians
double degToRad(double degrees) { return degrees * (std::numbers::pi / 180.0); }