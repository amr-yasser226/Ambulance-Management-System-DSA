# **Ambulance Management System**

### **Overview**
This project is developed as part of the **Data Structures and Algorithms** course at Zewail City of Science and Technology. The goal is to build a centralized system for managing ambulance services across multiple hospitals, simulating ambulance allocation based on real-time patient requests, and optimizing the system's overall performance.

The project applies advanced data structures to handle patients, hospitals, and ambulance car management efficiently.

### **Project Requirements**
The system simulates ambulance service operations, and based on patient requests, assigns ambulances to handle those requests while considering various factors such as patient severity, car types, and distances between hospitals.

The main objectives are:
- Efficiently assign ambulance cars to patients.
- Handle different patient types (Normal, Special, Emergency).
- Track and simulate the movement of cars between hospitals and patients.
- Generate relevant statistics about the system's performance (e.g., patient waiting time, average utilization of cars).

### **Project Phases**
1. **Phase 1.1 (10%)** - Basic setup: Input/output file handling, hospital distance matrix, and initial car management.
2. **Phase 1.2 (30%)** - Implementation of patient queue management with priority and car assignment based on requests.
3. **Phase 2 (60%)** - Full system simulation, finalizing algorithms, testing, and output generation.

### **Key Features**
- **Simulation Time (Timesteps)**: The system processes patient requests and car assignments in steps, with each step representing a unit of time.
- **Patient Types**: Includes Normal Patients (NP), Special Patients (SP), and Emergency Patients (EP), each with different levels of urgency.
- **Car Management**: Ambulances are categorized into Special Cars (SC) for special needs and Normal Cars (NC) for regular patients.
- **Priority-Based Assignment**: EP patients are given the highest priority, followed by SP and NP, with assignments optimized based on availability and distance.
- **Statistical Output**: The system provides metrics such as average waiting times, average car utilization, and total patient processing time.

### **Project Structure**
- `src/`: Contains the source code, including the implementation of data structures and algorithms used for managing patients, hospitals, and ambulance cars.
- `docs/`: Documentation related to the project, including reports, planning documents, and other references.
- `tests/`: Contains unit and integration tests to validate different aspects of the system.
- `data/`: Stores the input files (hospital data, patient requests, etc.) and output files generated during the simulation.
- `scripts/`: Optional scripts for automation, such as generating test cases or formatting input/output files.

### **How It Works**
1. **Input File**: The input file defines the number of hospitals, car speeds, the distance matrix between hospitals, and a list of patient requests sorted by request time.
   - Patient requests include request time, type of patient (NP, SP, EP), and the nearest hospital.
   - The distance matrix is a 2D matrix that specifies the distances between each pair of hospitals.
   
2. **Processing Requests**:
   - Patients are queued based on their type (EP, SP, NP), and cars are assigned based on availability and proximity.
   - Ambulances are dispatched, and the system tracks their status (Ready, Assigned, Loaded).
   
3. **Output File**: After the simulation runs, an output file is generated containing the final assignment of patients and various system statistics such as average patient waiting times and car utilization rates.

### **Input/Output Example**

#### **Input Format**
The input file specifies:
- Number of hospitals
- Car speeds for Special Cars (SC) and Normal Cars (NC)
- Distance matrix between hospitals
- Patient requests, including type, time of request, and patient details

Example input:

```
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

#### **Output Format**
The output file contains:
- Finish time (FT), Patient ID (PID), Request time (QT), and Waiting time (WT) for each patient.
- Summary statistics such as the total number of patients, average waiting time, and car utilization.

Example output:

```
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

### **Setup and Running the Project**
1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/Ambulance-Management-System.git
   ```

2. **Compile and run the project**:
   Depending on the language you're using (e.g., Python, C++), the steps to compile and run will differ. Include specific instructions based on your team's implementation.

   Example for C++:
   ```bash
   g++ -o ambulance_system src/*.cpp
   ./ambulance_system data/input.txt
   ```

3. **Run Tests**:
   Ensure that the system runs correctly by executing test cases.
   ```bash
   ./run_tests.sh
   ```

### **How to Contribute**
1. **Create a feature branch**:
   ```bash
   git checkout -b feature/<feature-name>
   ```

2. **Commit your changes**:
   ```bash
   git commit -m "Add feature or fix"
   ```

3. **Push your changes**:
   ```bash
   git push origin feature/<feature-name>
   ```

4. **Submit a pull request** for code review before merging into the `main` branch.

### **License**
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### **Team Members**
- **Team Leader**: Amr Yasser
- **Teammates**: Amr Mahmoud, Momen Sanad, Omar Hazem
