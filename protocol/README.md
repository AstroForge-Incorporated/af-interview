# Interview Option 2

For this challenge, you need to write both ends of a simple protocol for a sensor. Get creative with the choice of the sensor, it could be a thermocouple, an ultrasonic range finder, or anything else. Whatever you choose shouldn't be too complex. You don't need to actually interact with a real sensor and your protocol should not be a carbon copy of an existing sensor's protocol. You'll need to write a driver and a mock / simulation of the sensor. You can substitute a real serial port, for a Linux pseudo serial port. The following command will set up two virtual serial ports that can correspond to the host and sensor.

Ask any questions you want, but only some will be answered.

``` sh

socat -d -d pty,raw,echo=0 pty,raw,echo=0
```


### Requirments
- Your code must be written in Rust or modern C++.
- Please ensure that both ends of the protocol are written to be as safe as possible. Please document anywhere you cut corners. Also document any design decisions you make.
- Write some documentation on how to use the driver and simulator you have created.
- Your sensor only needs to return a single value, please ensure that those values make some sense for whatever type of sensor you have chosen.
- Please use Git like you would on a real project.


When you are finished push your changes, add `@sphw` as a collaborator, and send an email to your contact at AstroForge.
