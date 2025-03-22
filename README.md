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
│   ├── conway_config.json
│   ├── conwayVisualization_config.json
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

### **Loader Test**  
**File:** [main_loader_tester.cpp](main/test_runs/main_loader_tester.cpp)  

This test runs the **Loader** component to verify its behavior when processing images. The simulation logs will display the **image processing sequence** in the terminal.  

#### **Running Different Tests**

- **Basic Image Loading Test (Test 1)** → Set `image_list = {"image1.jpeg", "image2.jpeg"}`

- **Empty List Test (Test 2)** → Set `image_list = {}`

Modify the following line in `main_loader_tester.cpp` to switch between tests::  

```cpp
std::vector<std::string> image_list = {"image1.jpeg", "image2.jpeg"};
```

---

### **Filter Test**  
**File:** [main_filter_tester.cpp](main/test_runs/main_filter_tester.cpp)

This test runs the **Filter** component to validate its behavior when processing images and handling the "done" signal from the Analyzer.
When executed, the simulation logs will display the image filtering process in the terminal.  

#### **Setup Instructions**  
Before running the test, update the following lines in `filter_tester.hpp` to match your system's file path:

```cpp
std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_input_test.txt";

std::string filter_done_signal_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_done_signal_test.txt"
```

#### **Running Different Tests**

- **Basic Image Filtering Test (Test 1)** → Set `test = "test1"`

- **No "Done" Signal Test (Test 2)** → Set `test = "test2"`

Modify the following line in `filter_tester.hpp` to switch between tests::  

```cpp
std::string test = "test1"
```

---

### **Analyzer Test**  
**File:** [main_analyzer_tester.cpp](main/test_runs/main_analyzer_tester.cpp)  

This test runs the **Analyzer** component to validate its ability to process filtered images and generate reports.  
When executed, the simulation logs will display the processing sequence and generated reports in the terminal.  

#### **Setup Instructions**  
Before running the test, update the following line in `analyzer_tester.hpp` to match your system's file path:

```cpp
std::string analyzer_test = "/absolute/path/to/devs-image-processing-system/test_files/analyzer/" + test + "/analyzer_test.txt"
```

#### **Running Different Tests**  

- **Standard Image Analysis Test (Test 1)** → Set `test = "test1"`

- **Simultaneous Image Input Test (Test 2)** → Set `test = "test2"`  

Modify the following line in `analyzer_tester.hpp` to switch between tests:  

```cpp
std::string test = "test1";
```

---

### **FilterAnalyzer Test**  
**File:** [main_filterAnalyzer_tester.cpp](main/test_runs/main_filterAnalyzer_tester.cpp)  

This test runs the **FilterAnalyzer** coupled model to validate the integration of the **Filter** and **Analyzer** components.  
When executed, the simulation logs will display the filtering and analysis process, including image processing and the generation of reports.

#### **Setup Instructions**  
Before running the test, update the following line in `filterAnalyzer_tester.hpp` to match your system's file path:

```cpp
std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filterAnalyzer/" + test + "/filterAnalyzer_test.txt";
```

#### **Running Different Tests**  

- **Sequential Image Processing Pipeline Test (Test 1)** → Set `test = "test1"`

- **Simultaneous Image Processing Test (Test 2)** → Set `test = "test2"`  

Modify the following line in `filterAnalyzer_tester.hpp` to switch between tests:  

```cpp
std::string test = "test1";
```

---

### **Top System Test**  
**File:** [main_top_system_tester.cpp](main/test_runs/main_top_system_tester.cpp)  

This test runs the **Top System** coupled model, which integrates the **Loader** and **FilterAnalyzer** components. It verifies the full pipeline from image generation to filtering and analysis. The simulation logs will display the **entire image processing sequence** in the terminal.  

#### **Running Different Tests**

- **Standard Processing Test (Test 1)** → Set `image_list = {"image1.jpeg", "image2.jpeg"}`

- **No Images Test (Test 2)** → Set `image_list = {}`

Modify the following line in `main_top_system_tester.cpp` to switch between tests::  

```cpp
std::vector<std::string> image_list = {"image1.jpeg", "image2.jpeg"};
```

---

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

### **Loader Test**  
To test the **Loader** model, run:  
```sh
./bin/Loader_Tester
```
This will execute the **Loader** model and display its behavior in the terminal logs.

### **Filter Test**  
To test the **Filter** model, run:  
```sh
./bin/Filter_Tester
```
This will execute the **Filter** model and log how it processes images and handles the "done" signal.

### **Analyzer Test**  
To test the **Analyzer** model, run:  
```sh
./bin/Analyzer_Tester
```
This will execute the **Analyzer** model and log how it generates reports and sends the "done" signal.

### **FilterAnalyzer Coupled Model Test**  
To test the **FilterAnalyzer** coupled model, run:  
```sh
./bin/FilterAnalyzer_Tester
```
This will execute the **FilterAnalyzer** system, combining Filter and Analyzer, and log the full filtering and analysis process.

### **Top System Test**  
To test the **Top System** coupled model, run:  
```sh
./bin/Top_System_Tester
```
This will execute the **Top System**, which integrates the Loader and FilterAnalyzer, and log the full image processing workflow, from loading images to filtering and analysis.

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