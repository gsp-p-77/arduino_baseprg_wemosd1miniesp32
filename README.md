# Simple base program as template for my Arduino, ESP32 projects with platform.io and additional WIFI manager feature

Target:
AZDelivery 1 x ESP32 D1 Mini NodeMCU

Base Features:
- Blinking LED (GPIO 10)
- 3 cyclic tasks (10 ms, 100 ms, 1000 ms) and one task for remaining operaration time (background)
- Task profile output (average and max time of the sum of all executed tasks together) => To be checked not to overrun the scheduled tasks

WIFI Manager feature:
- wifiM with credentials.h to define SSID and Password
- API wifiM_init to connect to WIFI router

  
