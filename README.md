# OPC-UA-Server-ESP32-Platform.io-Implementation

## *Version:* Server still works on the 6.9.0 version of Espressif 32 IDF

## *Context:*
This project involves deploying an OPC-UA server on an ESP32 microcontroller with a minimalistic information model, using either WIFI or Ethernet. The server retrieves data from the MSA311 sensor, mapping the X, Y, and Z axis components into individual OPC-UA nodes. The primary objective is to enable efficient server-client communication between a workstation and a Node-RED implementation, which processes the sensor data.

Building upon cmbahadir's ESP-IDF 5.0 implementation, I migrated the project to Platform.io to enhance ease of management and support the addition of new features. This migration streamlines the development process by avoiding manual configuration files or complex linking. The project utilizes both the Espressif IDF 5.0 framework for managing the OPC-UA server and the Arduino framework for handling sensor integration, leveraging widely updated Arduino libraries for the ESP32.

The combination of these frameworks ensures flexibility, a user-friendly development environment, and continuous compatibility with new sensor libraries, offering a seamless solution that minimizes the need for manual intervention. The goal was to simplify the entire approach, making it more accessible and less reliant on intricate tweaks while maintaining a powerful, robust system.

## *References:* https://github.com/cmbahadir/opcua-esp32

## *Improvements:*
This approach removes the necessity of manually creating CMakeLists files to manage the project structure, significantly simplifying integration and organization. With Platform.io, libraries for new sensors can be easily installed and managed through the Platform.io Libraries section. This not only streamlines the development process but also allows for rapid integration of additional sensors and features without the need for manually configuring dependencies or project files. By automating these tasks, developers can focus on expanding functionality and refining the project instead of dealing with tedious setup procedures.

## *Prerequisites:*
ESP32 microcontroller (i used the ESP32-WROOM-32D module)
Sensors (i used the MSA311 from Adafruit)

## *Getting Started:*
This will be a representation on how to create a new node on the sensor.
First go into src folder where all the source files are located and create a new node with the default approach, using a setup node (type void) and a read node (type UA_StatusCode).
Don't forget to reference them on the model.h file on the include folder. Don't forget tom change the displayName, currentNodeId and currentName attributes.

On the read node you have a call to read the data from the sensor function. 
All the code for the sensors are inside the src folder on the sensors.cpp file.

To insert a new node you created into the OPC-UA server task, you need to acess the src folder and the main.cpp file, and insert the new function call where you see "Add Information Model Objects Here"
Than on the condition which checks for the creation of the server, inside void app_main(void), 
you can insert the setup function for your sensor.

Remember always to add the new libraries via the Platform.io tool, to make the process easier and automatic.

If you get an error on your first build on esp_wifi.h, apply this change 

```
CONFIG_ESP32_WIFI_DYNAMIC_TX_BUFFER_NUM 
```

## *Configuration:*
To change your Wi-Fi SSID, password, and static IP configuration on your ESP32, you need to access the Platform.io IDF menuconfig by executing the following command in the terminal:

```
pio run -t menuconfig
```

Here’s the menu structure you created for the in the menuconfig:

```
Component Config -> Connection Configuration
```

You can also configure the type of connection, WIFI or Ethernet (the project was only tested with WIFI):

```
Component Config -> Connection Configuration -> Connection Type
```


