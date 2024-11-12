# Ambulance Management System

### Overview
This project is developed as part of the **Data Structures and Algorithms** course at Zewail City of Science and Technology. The goal is to build a centralized system for managing ambulance services across multiple hospitals, simulating ambulance allocation based on real-time patient requests, and optimizing the system's overall performance.

The project applies advanced data structures to handle patients, hospitals, and ambulance car management efficiently.

---

### Project Requirements

The system simulates ambulance service operations and, based on patient requests, assigns ambulances to handle those requests while considering various factors such as patient severity, car types, and distances between hospitals.

The project strictly follows these data structure rules:
- **Data Structures Allowed**: Stack, Queue, Priority Queue (and any derived class).
- **Prohibitions**:
  - No **global variables**.
  - No use of **C++ STL**.
  - No **friendship** usage.
  - No copying of objects between lists, use **pointers** to avoid duplicate memory allocation.

The main objectives are:
- Efficiently assign ambulance cars to patients.
- Handle different patient types (Normal, Special, Emergency).
- Track and simulate the movement of cars between hospitals and patients.
- Generate relevant statistics about the system's performance (e.g., patient waiting time, average utilization of cars).

---

### Project Phases

1. **Phase 1.1 (10%)**: 
   - Selecting the appropriate data structures to manage the project lists (patients, cars, etc.).
   - Deliverable: A report explaining the chosen data structures (Stack, Queue, Priority Queue).

2. **Phase 1.2 (30%)**: 
   - Implementing and testing the chosen data structures.
   - Creating a simple simulator to verify that data structure operations work correctly.
   - No patient-car assignment or final output generation required in this phase.
   - Deliverables: Code, sample input file, and a demo video.

3. **Phase 2 (60%)**: 
   - Extending the code to implement the full system logic and output generation.
   - Deliverables: Full code, six sample input files, output files, and a workload distribution document.

---

### Key Features
- **Simulation Time (Timesteps)**: The system processes patient requests and car assignments in steps, with each step representing a unit of time.
- **Patient Types**: Includes Normal Patients (NP), Special Patients (SP), and Emergency Patients (EP), each with different levels of urgency.
- **Car Management**: Ambulances are categorized into Special Cars (SC) for special needs and Normal Cars (NC) for regular patients.
- **Priority-Based Assignment**: EP patients are given the highest priority, followed by SP and NP, with assignments optimized based on availability and distance.
- **Statistical Output**: The system provides metrics such as average waiting times, average car utilization, and total patient processing time.

---

### Project Structure
```markdown
Ambulance-Management-System/
├── src/                 # Source code files implementing core functionalities
│   ├── Hospital/        # Folder for the Hospital Class
│   │   ├── hospital.h   # Header file for the Hospital Class
│   │   └── hospital.cpp # Implementation file for the Hospital Class
│   ├── Car/             # Folder for the Car Class
│   │   ├── car.h        # Header file for the Car Class
│   │   └── car.cpp      # Implementation file for the Car Class
│   ├── Patient/         # Folder for the Patient Class
│   │   ├── patient.h    # Header file for the Patient Class
│   │   └── patient.cpp  # Implementation file for the Patient Class
│   ├── Organizer/       # Folder for the Organizer Class
│   │   ├── organizer.h  # Header file for the Organizer Class
│   │   └── organizer.cpp# Implementation file for the Organizer Class
│   ├── UI/              # Folder for the UI Class
│   │   ├── ui.h         # Header file for the UI Class
│   │   └── ui.cpp       # Implementation file for the UI Class
│   └── main.cpp         # Main simulation file that brings everything together
├── data/                # Input/output files for simulation
│   ├── input/           # Folder for input files (hospital data, requests, etc.)
│   └── output/          # Folder for output files (simulation results)
├── docs/                # Documentation and project reports
│   ├── report.md        # Detailed project report and design decisions
│   └── planning.md      # Project planning and scheduling information
├── tests/               # Test cases for different system components
│   ├── test_hospital.cpp# Unit tests for the Hospital Class
│   ├── test_car.cpp     # Unit tests for the Car Class
│   ├── test_patient.cpp # Unit tests for the Patient Class
│   └── test_organizer.cpp # Unit tests for the Organizer Class
└── README.md            # Project overview and instructions (this file)
```

---

### Class Structure

- **Patient Class**: Handles patient data and requests.
- **Car Class**: Linked to patients, manages car movements and patient pick-up/drop-off.
- **Hospital Class**: Manages patients and cars, responsible for assignments.
- **Organizer Class**: Main class to manage the overall system operations.
- **UI Class**: Handles user input/output, managing program interaction and printing system status.

---

### How It Works

1. **Input File**: The input file defines the number of hospitals, car speeds, the distance matrix between hospitals, and a list of patient requests sorted by request time.
   - Patient requests include request time, type of patient (NP, SP, EP), and the nearest hospital.
   - The distance matrix is a 2D matrix that specifies the distances between each pair of hospitals.
   
2. **Processing Requests**:
   - Patients are queued based on their type (EP, SP, NP), and cars are assigned based on availability and proximity.
   - Ambulances are dispatched, and the system tracks their status (Ready, Assigned, Loaded).
   
3. **Output File**: After the simulation runs, an output file is generated containing the final assignment of patients and various system statistics such as average patient waiting times and car utilization rates.

---

### Input/Output Example

#### Input Format
The input file specifies:
- Number of hospitals
- Car speeds for Special Cars (SC) and Normal Cars (NC)
- Distance matrix between hospitals
- Patient requests, including type, time of request, and patient details

Example input:

```plaintext
4
110 75
0 154 587 634
154 0 533 214
587 533 0 945
634 214 945 0
3 11
2 5
6 15
1 2
150
NP 3 1 2 159
SP 3 2 1 588
EP 12 3 4 433 5
7
15 1
```

#### Output Format
The output file contains:
- Finish time (FT), Patient ID (PID), Request time (QT), and Waiting time (WT) for each patient.
- Summary statistics such as the total number of patients, average waiting time, and car utilization.

Example output:

```plaintext
FT PID QT WT
245 12 3 77
352 20 5 30
352 1 1 56
...
patients: 744 [NP: 550, SP: 150, EP: 44]
Hospitals = 23
cars: 112 [SCars: 35, NCars: 77]
Avg wait time = 45
Avg busy time = 152
Avg utilization = 77%
```

---

### Deliverables

1. **Phase 1.2 Deliverables**:
   - Code for Phase 1.2.
   - A report on the chosen data structures.
   - A sample input file with non-trivial scheduling requirements.
   - A demo video showing phase 1.2 functionality.

2. **Phase 2 Deliverables**:
   - Final project code (excluding executables).
   - Six comprehensive test cases covering simple to complex scenarios.
   - A workload distribution document.

---

### Team Members
- **Team Leader**: Amr Yasser 
- **Teammates**: Omar Hazem, Amr Abdelfattah, and Momen Sanad

---

### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```