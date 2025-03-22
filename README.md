# Plant Population - Cell DEVS Model

## Introduction
This repository presents a **Cell-DEVS Plant Population model** that simulates tree growth, competition, and reproduction under limited environmental resources such as **water**, **nitrogen**, **potassium**, and **sunlight**.

The model is based on the paper *“Simulation of Vegetable Population Dynamics Based on Cellular Automata”* by **Stefania Bandini** and **Giulio Pavesi**, and is implemented using the Cadmium DEVS framework. It captures ecological processes like resource diffusion, growth thresholds, and seed dispersal through localized cell interactions and event-driven updates.

The system is structured using **atomic** and **coupled DEVS models**, ensuring a modular, scalable, and realistic simulation of plant dynamics.

## Repository Structure
This repository is arranged in the following manner:

```sh
.
├── config/                             # Configuration files for visualization or simulation
│   ├── plant_population_config.json
│   ├── plant_population_visualization_config.json
├── main/                               # Source code directory
│   ├── include/                        # Header files for the model
│   │   ├── plantPopulationCell.hpp     # Defines cell behavior and resource-based state updates
│   │   ├── plantPopulationState.hpp    # Defines cell state: resources, tree type, and height
│   │   ├── plantResources.hpp          # Defines and compares cell resources (water, sunlight, nitrogen, potassium)
│   ├── main.cpp                        # Main file to simulate the full system
│   ├── CMakeLists.txt                  # CMake configuration for the project
├── build_sim.sh                        # Build script for Cadmium simulation
├── grid_log.csv                        # Output log file of the simulation
├── CMakeLists.txt                      # CMake configuration for building the project
├── .gitignore                          # Git ignore file
└── README.md                           # This documentation file
```

## System Components (Atomic and Coupled Models)

This project includes one **atomic model** that defines the behavior of each vegetation cell, and a **coupled model** automatically generated using Cadmium’s Grid Cell-DEVS infrastructure to simulate interactions across the grid.

### **1. plantPopulation (Atomic Cell-DEVS)**  
**File:** [`plantPopulationCell.hpp`](main/include/plantPopulationCell.hpp)  

The **plantPopulation** atomic model defines the local behavior of each cell. At every simulation step, each cell:
- Exchanges **water**, **sunlight**, **nitrogen**, and **potassium** with neighboring cells through diffusion.
- Produces its own resources.
- Determines whether to **germinate a tree**, **survive**, or **grow** based on resource thresholds.
- Increments tree height or dies based on environmental conditions.

---

### **2. Grid Coupled Model**  
**Constructed in:** [`main.cpp`](main/main.cpp)  
**Type:** `GridCellDEVSCoupled<plantPopulationState, double>`

The **Grid Coupled Model** automatically connects a grid of `plantPopulation` atomic models using the **Von Neumann neighborhood**. Each cell interacts with its neighbors, allowing for realistic spatial dynamics such as:
- Resource distribution across the grid.
- Propagation of seed types.
- Local competition and survival mechanisms.

The coupled model is instantiated from a JSON config file and executed using Cadmium's simulation engine, with outputs logged to `grid_log.csv`.

## **Main Simulation Files**  

This section contains different main files used to execute and test the **Image Processing System**. Each file initializes the system components and runs simulations under various configurations.  

### **Standard Simulation**  
**File:** [main.cpp](main/main.cpp)  

This file initializes and runs the **Image Processing System** using Cadmium. It sets up the **Top Model**, which integrates the **Loader, Filter, and Analyzer**, processes a predefined list of images, and executes the simulation for **25 seconds** to complete the full workflow.  

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.
_This dependency would be met by default if you are using the DEVSsim servers. To check, try `echo $CADMIUM` in the terminal_

## Build
To build this project, run:
```sh
source build_sim.sh
```

__NOTE__: Everytime you run build_sim.sh, the contents of `build/` and `bin/` will be replaced.


## **Execute**  

To test each model, run the corresponding executable and check the logs in your terminal.  

### **Full System Execution**  
To test the entire **Image Processing System**, run:  
```sh
./bin/Image_Processing_System
```
This will simulate the complete image processing workflow, from loading images to generating analysis reports.

## **Logging Configuration**  
By default, the simulation outputs logs to the terminal. If you prefer to log results into a **CSV file instead**, follow these steps:  

1. **Disable terminal output** by commenting out the following line in your main test files (`main_loader_tester.cpp`, `main_filter_tester.cpp`, etc.):  
   ```cpp
   // rootCoordinator.setLogger<STDOUTLogger>(";");
   ```

2. **Enable CSV logging** by uncommenting the line below and specifying the appropriate log file path:
   ```cpp
   rootCoordinator.setLogger<CSVLogger>("log_files/loader/test_1_output.csv", ";");
   ```
This allows you to capture simulation results in structured CSV files instead of printing them directly to the terminal.