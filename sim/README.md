# Interview Option 1

This is the first option for the AF interview challenge. You are asked to develop a program that controls a simple simulation. The goal is to get the included vehicle to hover. The simulation uses very simple 1D kinematics. Your vehicle has a maximum thrust of 20N, and your craft weighs 1KG. You may not change `sim/src/lib.rs`. Ideally, you will write a simple [control loop](https://en.wikipedia.org/wiki/Control_loop). Control loops generally take information about the current state of a system, they calculate a desired change to the system and then command actuators (thrusters, motors, etc) to change the system. The classic example of a control loop is a [PID loop](https://en.wikipedia.org/wiki/PID_controller). If you aren't comfortable writing a control loop, try out the second option instead.

Ask any questions you want, but only some will be answered. 

### Requirments
- The craft must be able to hover within a reasonable error, you can decide what that means.
- You must document what you are doing in the source code with comments, and be prepared to explain your design, tradeoffs, and whatnot.
- You must include a way of visualizing the vehicle, this could be a graph, an animation, or anything you can think of.
- Ensure you use Git as you would in a real project. Commit often, we are here to see your process.
- Please outline how you tested your code. This could be manual testing, automatic testing, or something in-between.

When you are finished push your changes, add `@sphw` as a collaborator, and send an email to your contact at AstroForge.
