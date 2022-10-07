# CJ IoT Assignment

This Assignment want you connect a device to `Thingsboard` [IoT Platform] through MQTT, The device can send a telemetry `temperature1`, `temperature2` to platform by using an `AccessToken` that generate from Thingsboard.

In the Thingsboard platform, Your device should present a telemetry on Dashboard [Thingsboard has a Dashboard service inside.]

## Prerequisite

- ESP32 x 1
- DS18B20 x 2
- Thingsboard
  - URL: http://senseme.ddns.net:9000/login
  - MQTT Port: 1883

![Schematic](./schematic.png)

## Features

- Read a temperature from 2xDS18B20.
- Device can read a temperature individual channel.
- Device can send a telemetry through MQTT.

## Telemetry Format

```
{
    "temperature1": number,
    "temperature2": number
}
```

## Configuration

First, Change a config file in `/include/CONFIG.h`

```c++
// WiFi
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "psk1234"

// Thingsboard platform
#define THINGS_BOARD_HOSTNAME "xxxxxxx"
#define THINGS_BOARD_TOKEN "xxxxxx"

// DS18B20
#define DS18B20_1 16 // For DS18B20 Channel 1.
#define DS18B20_2 17 // For DS18B20 Channel 2.
```

## Deliverable

- Source code on Git repository.

## Documentation

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/)
- [Thingsboard](https://thingsboard.io/docs/)
- [ESP32](https://www.espressif.com/en/products/socs/esp32)
- [DS18B20](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf)

## 🚀 Notes

- Try your best. If you cannot cover all tasks above, you can send your deliverable source code to us.
- You can enhance your idea to improve application. Maybe it can increase your points.


## Unit test

![Unit test](./code_test.png)
![Table](./dashboard.png)

- unit test send data 10 times
  - ✅{"temperature1":-41.867,"temperature2":-3.618}
  - ✅{"temperature1":-2.766,"temperature2":1.513}
  - ✅{"temperature1":36.281,"temperature2":22.632}
  - ✅{"temperature1":9.282,"temperature2":33.240}
  - ✅{"temperature1":-39.714,"temperature2":43.400}
  - ✅{"temperature1":-11.672,"temperature2":-49.320}
  - ✅{"temperature1":33.832,"temperature2":40.842}
  - ✅{"temperature1":-11.834,"temperature2":-14.176}
  - ✅{"temperature1":30.030,"temperature2":-24.893}
  - ✅{"temperature1":23.079,"temperature2":-17.742}

ThingsBoard can reciver data and show Chart on Dashboards✅
