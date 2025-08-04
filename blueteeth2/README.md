| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)

This Porgram is to about how to use the Bluetooth Classic with the GAP API to find and discover devices that are in 'pairing' or discoverable state. 

the API works as descirbed in the comments of the program in detail. 

the API allows you to register your own callback fucntion, which will be called once the API detects a device (which are registered through events, the host(for the API) enters a discovery state and raises event dicovery started, when it starts, it raises event device discovering, et cetera, you get it ;)). 

Now the callback receivs this event and the parameters of discovery that contain the device information such as the device address (analogous to the mac address), name, class of device et cetera. 

The project **Blueteeth2** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
