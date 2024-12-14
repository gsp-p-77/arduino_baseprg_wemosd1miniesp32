# Demo app for Mqtt over Wifi as server for a nodeRED client

Target:
AZDelivery 1 x ESP32 D1 Mini NodeMCU

Base Features:
- Blinking LED (GPIO 10)
- 3 cyclic tasks (10 ms, 100 ms, 1000 ms) and one task for remaining operaration time (background)
- Task profile output (average and max time of the sum of all executed tasks together) => To be checked not to overrun the scheduled tasks

Demo app for Mqtt over Wifi:
- Application with mqtt interface to turn on, off LED for 10 s, before it toggles again (topic "ledState", payload "on"/"off" to control LED)
  (tested with nodeRED sketch)


  
