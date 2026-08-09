# Student Academic & Examination Management System

[![C++ Version](https://img.shields.io/badge/Language-C%2B%2B11%2B-blue.svg)](https://isocpp.org/)
[![Development IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20%2F%20CLion-black.svg?style=flat&logo=visualstudio&logoColor=white)](https://visualstudio.microsoft.com/)

A modular, production-grade console application built in C++ utilizing custom data structures and Object-Oriented Programming (OOP) principles to manage student academic records, parse trimester examination results, calculate CGPA/GPA metrics, and perform cohort-wide academic analytics[cite: 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36]. Designed with clean architectural separation to decouple domain models from dynamic singly-linked list management and file-stream persistence[cite: 28, 29, 32, 33, 36].

---

## 🚀 Key Engineering Features

* **Custom Data Structure Implementation:** Engineered a dynamic, pointer-based singly-linked list (`List` / `Node`) without relying on C++ STL containers, supporting insertion sorted alphabetically by student name, dynamic deletions, and positional access[cite: 28, 29, 30, 31].
* **Automated GPA & CGPA Engine:** Evaluates grade points and letter grades (A+ to F) from raw subject marks, dynamically computing credit-weighted trimester GPAs and cumulative CGPAs[cite: 26, 32, 34].
* **Relational Data File Ingestion:** Features custom file-stream parsers to ingest student profiles (`student.txt`) and link multi-subject trimester exam histories (`exam.txt`) via unique student IDs[cite: 36].
* **Advanced Academic Analytics & Filtering:** Includes custom analytical algorithms to compute cohort CGPAs, major demographics (CS, IA, IB, CN, CT, IR), and filter students by enrollment year, course, and earned credit thresholds[cite: 36].
* **First Class Honors Screening Engine:** Analyzes term-by-term performance profiles to detect candidates eligible for First Class Honors (evaluating credit loads $\ge 12$ and trimester GPAs $\ge 3.75$)[cite: 36].
* **Dynamic Data Sanitation:** Automatically normalizes student IDs (e.g., prepending degree tags like `BCS`) and cleans/formats contact numbers dynamically in memory[cite: 36].

---

## 🛠️ Technical Stack & Framework

* **Core Language:** C++ (C++11 or higher)[cite: 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36]
* **Data Structures:** Custom Singly Linked List (`List`, `Node`)[cite: 28, 29, 30, 31]
* **Data Layer:** Flat-file stream I/O (`<fstream>`) parsing structured text databases[cite: 26, 36]
* **Formatting & I/O:** Output stream manipulation (`<iomanip>`) for academic transcripts and reports[cite: 26, 35, 36]

---

## 📊 Class Architecture Design

The system is structured around hierarchical domain models managed through pointer-based linked memory:

* `Subject`: Encapsulates course details (subject code, name, credit hours, raw marks) and provides grade point conversion algorithms ($4.00$ scale)[cite: 34, 35].
* `Exam`: Manages trimester metadata (Jan/May/Oct terms), subject arrays (`Subject sub[6]`), and calculates credit-weighted term GPA[cite: 26, 27].
* `Student`: Domain model tracking student profile data, phone numbers, course codes, cumulative CGPAs, total credits earned, and historical exam arrays (`Exam exam[10]`)[cite: 32, 33].
* `Node` & `List`: The underlying dynamic memory framework supporting linked node management, alphabetical insertion sorting, position queries, and element removal[cite: 28, 29, 30, 31].

---

## 🖥️ User Operations Control Portal

The application runs an interactive CLI console providing 9 primary operational channels[cite: 36]:

1. **Create Student List** — Ingests student profiles from `student.txt` into the linked list while filtering duplicate IDs[cite: 36].
2. **Delete Student** — Locates and removes a student record from linked memory by student ID[cite: 36].
3. **Print Student List** — Generates complete academic transcripts outputted to the console or exported to `student_result.txt`[cite: 36].
4. **Insert Exam Result** — Parses `exam.txt`, links trimester exam scores to student profiles, and recalculates CGPA metrics[cite: 36].
5. **Print Exam Statistics** — Displays cohort demographic distribution, overall average CGPA, and semestral workload averages[cite: 36].
6. **Filter Student** — Filters cohort records by major (CS/IR/IB/IA/CN/CT), enrollment year, and minimum credits earned into a secondary list[cite: 36].
7. **Update Student's ID and Phone** — Standardizes ID formatting with course tags and sanitizes phone numbers[cite: 36].
8. **Find Potential First Class Student** — Screens students who meet sustained high academic achievement standards ($\text{GPA} \ge 3.50$ across terms with $\ge 3$ terms at $\text{GPA} \ge 3.75$)[cite: 36].
9. **Exit** — Safely terminates application execution[cite: 36].
