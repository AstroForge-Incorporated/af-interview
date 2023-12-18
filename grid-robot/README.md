# The challenge
In this challenge, you'll be implementing an algorithm to move a robot from a start location
to a goal location on a 2D grid with obstacles. Your robot has a rotating LiDAR sensor and perfect knowledge of its current position, but nothing else (i.e., it does not have a map of the environment).

We've provided a simple sim framework in C++ (in `src`) if helpful, but feel free to use whatever language you'd like.

## Getting started with the C++ sim
If you do decide to use the C++ boilerplate, implement your algorithm as a set of C++ classes inheriting from the `ModuleBase`, found in `modules.h`. 

We've implemented a simple ROS-style pub-sub system (`messaging.h`) for you to use, along with a simple Sim class (`sim.h`) to test your modules. In order to move the robot, you must publish to the `Topic<ControlMsg>` topic. If a control message will result in the robot moving to a free square within the map bounds, the robot will execute this trajectory. To read from the LiDAR sensor, subscribe to the `Topic<LiDARScanMsg>` topic.

To compile the code, use any compiler that supports C++ 20.

See an example of how to use the C++ sim in `main.cpp`.

## What we'll be looking for
We'll be looking for a few things when reviewing your code:

Primary:
- Algorithm efficiency and correctness (is the robot successfully, and quickly (in as few steps as possible) able to end up at the goal?)
- Clarity (how easy is the code, and the underlying algorihtm to understand?)

Secondary (don't go too crazy with these things, but broadly keep them in the back of your head):
- Efficiency (how efficient is the code itself?)
- Testing (how well tested is the algorithm? The code implementing the algorithm?)
