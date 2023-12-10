# PiNanoConnect: Centralized Control for Remote Devices

This repository contains the source code for the Control Software for Raspberry Pi and Jetson Nano. It is a software application that allows users to control various devices or systems remotely via gRPC.

## Features

- GRPC Based API to access Raspberry Pi or Jetson Nano
- Plugin Architecture to select the device or enter into Simulation Mode
- Can be able to connect any gRPC based client.
- Real-time monitoring of the devices and real-time access.

## Getting Started

### Prerequisites

- All the prerequisites will be downloaded from cmake.
### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/AKSoftCode/Controller.git
   ```
2. Run the cmake command from the build directory:

   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. You can also use CMakeSettings.json file to build the project on Visual Studio.
   
Note: You can set the device from Controller.DeviceInterface.
   ```bash  
   option(JETSON_NANO_HOST "Use Jetson GPIO" ON)
   ```
       
   Default is Jetson Nano device. These plugins go to the plugin folder in the output directory. If any         device plugin is not present, then copy the simulation library into the plugin directory to load it 
   into simulation mode.





























