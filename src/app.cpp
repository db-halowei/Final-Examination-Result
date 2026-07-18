#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include    <cctype> 
#include	"List.h"
#include	"Student.h"
#include    "Subject.h"
using namespace std;


bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(const char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, const char*);
int menu(List*, List*);

using namespace std;


int main() {

    List list1, list2;
    menu(&list1, &list2);


    system("pause");
    return 0;
}
int menu(List* list1, List* list2) {

    bool correctForm = false;

    while (!correctForm) {
        int choice;
        do {

            cout << "1. Create Student List" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Print Student List" << endl;
            cout << "4. Insert Exam Result" << endl;
            cout << "5. Print Exam Statistics" << endl;
            cout << "6. Filter Student" << endl;
            cout << "7. Update Student's ID and Phone" << endl;
            cout << "8. Find Potential First Class Student" << endl;
            cout << "9. Exit" << endl;

            cout << "\nEnter choice (1-9): ";

            if (!(cin >> choice)) {
                cout << "Invalid input\n\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }


            switch (choice) {
            case 1:
                if (!CreateStuList("student.txt", list1)) {
                    cout << "Failed to load student data\n";
                }
                else {
                    cout << "Successfully load student data\n\n";
                }

                break;
            case 2:
                char sid[12];
                cout << "Enter the student ID to delete: ";
                cin >> sid;

                if (!DeleteStudent(list1, sid))
                    cout << "Deletion failed. Student not found.\n\n";
                break;

            case 3: {
                bool correctChoice = false;

                while (!correctChoice) {
                    int source;
                    cout << "Do you want to print student list on screen or in txt file (PRESS 0-both, 1-screen, 2-txt file): ";

                    //input validation
                    if (!(cin >> source)) {
                        cout << "Invalid input\n\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                    }

                    if (source == 1) {

                        if (!PrintList(*list1, 1))
                            cout << "List is empty.\n";

                        correctChoice = true;
                    }
                    else if (source == 2) {
                        if (!(PrintList(*list1, 2)))
                            cout << "List is empty.\n";
                        cout << "\nStudent list printed to student_result.txt file\n\n";
                        correctChoice = true;
                    }
                    else if (source == 0) {
                        if (!PrintList(*list1, 1) && !PrintList(*list1, 2)) {
                            cout << "List is empty.\n";
                        }

                        correctChoice = true;
                    }
                    else {
                        cout << "\nInvalid choice.\n\n";
                    }

                }



                break;
            }

            case 4:
                if (!InsertExamResult("exam.txt", list1)) {
                    cout << "Failed to load exam data\n";
                }
                else {
                    cout << "Successfully load exam data\n\n";
                }
                break;
            case 5:
                if (!PrintStatistic(*list1))
                    cout << "Failed to print exam statistics.\n";
                break;
            case 6: {
                char course[3];
                bool valid = false;
                int year, credit;
                while (!valid) {
                    cout << "Enter course (CS/IR/IB/IA/CN/CT): ";
                    cin >> course;

                    for (int i = 0; course[i] != '\0'; i++) {
                        course[i] = toupper(course[i]);
                    }
                    if (strcmp(course, "CS") == 0 || strcmp(course, "IR") == 0 || strcmp(course, "IB") == 0 || strcmp(course, "IA") == 0 || strcmp(course, "CN") == 0 || strcmp(course, "CT") == 0 && strlen(course) == 2)  {
                        valid = true;

                    }
                    else {
                        cout << "Invalid course. Please try again.\n";
                    }

                }

                cout << "Enter year: ";
                if (!(cin >> year)) {
                    cout << "Invalid input\n\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                cout << "Enter minimum credit: ";
                if (!(cin >> credit)) {
                    cout << "Invalid input\n\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }



                if (FilterStudent(*list1, list2, course, year, credit)) {
                    if (!PrintList(*list2, 1)) {
                        cout << "No student found.\n";
                    }
                }
                else {
                    cout << "Filter failed.\n";
                }

            }


                  break;

            case 7:
                if (UpdateIDandPhone(list1)) {
                    cout << "IDs and phone numbers updated successfully.\n";
                    PrintList(*list1, 1);
                }
                else {
                    cout << "The student list is empty. Update failed.\n";
                }

                break;
            case 8: {
                char course[3];
                bool valid = false;

                while (!valid) {
                    cout << "Enter course (CS/IR/IB/IA/CN/CT): ";
                    cin >> course;

                    for (int i = 0; course[i] != '\0'; i++) {
                        course[i] = toupper(course[i]);
                    }


                    if (strcmp(course, "CS") == 0 || strcmp(course, "IR") == 0 || strcmp(course, "IB") == 0 || strcmp(course, "IA") == 0 || strcmp(course, "CN") == 0 || strcmp(course, "CT") == 0 && strlen(course) == 2) {
                        valid = true;

                    }
                    else {
                        cout << "Invalid course. Please try again.\n";
                    }

                }

                *list2 = List();

                if (FindPotentialFirstClass(*list1, list2, course)) {
                    PrintList(*list2, 1);
                }


                break;
            }
            case 9:
                cout << "Exitting system" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            }


        } while (choice != 9);


        return 0;

    }


}



bool CreateStuList(const char* filename, List* list) {
    ifstream file(filename);

    if (!file) {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    Student s;

    while (getline(file, line)) {

        if (line.find("Student Id") != string::npos) {

            // --- Read ID ---
            strcpy_s(s.id, line.substr(line.find("=") + 2).c_str());

            // --- Read Name ---
            getline(file, line);
            strcpy_s(s.name, line.substr(line.find("=") + 2).c_str());

            // --- Read Course ---
            getline(file, line);
            strcpy_s(s.course, line.substr(line.find("=") + 2).c_str());

            // --- Read Phone ---
            getline(file, line);
            strcpy_s(s.phone_no, line.substr(line.find("=") + 2).c_str());

            s.exam_cnt = 0;

            //  Check duplicate (by ID)
            bool duplicate = false;
            for (int i = 1; i <= list->size(); i++) {
                Student temp;
                list->get(i, temp);

                if (strcmp(temp.id, s.id) == 0) {
                    duplicate = true;
                    break;
                }
            }

            //  Insert if not duplicate
            if (!duplicate) {
                list->insert(s);
            }
        }
    }

    file.close();
    return true;
}

bool InsertExamResult(const char* filename, List* list) {

    ifstream file(filename);

    if (!file) {
        cout << "Error opening exam file!" << endl;
        return false;
    }

    char id[12];

    while (file >> id) {

        //  Find matching student
        Node* current = list->head;

        while (current != NULL) {

            if (strcmp(current->item.id, id) == 0) {

                Exam e;

                // Read exam info
                file >> e.trimester;
                file >> e.year;
                file >> e.numOfSubjects;

                // Read subjects
                for (int i = 0; i < e.numOfSubjects; i++) {


                    file >> e.sub[i].subject_code;
                    file >> e.sub[i].subject_name;
                    file >> e.sub[i].credit_hours;
                    file >> e.sub[i].marks;
                }

                //  Calculate GPA for this exam
                e.calculateGPA();

                //  Insert exam into student
                current->item.exam[current->item.exam_cnt] = e;
                current->item.exam_cnt++;

                //  Update CGPA
                current->item.calculateCurrentCGPA();

                break; // stop searching after match
            }

            current = current->next;
        }
    }

    file.close();
    return true;
}
bool PrintList(List list, int source) {

    if (list.empty()) {
        return false;
    }
    ostream* out;
    ofstream file;

    if (source == 2) {
        file.open("student_result.txt");

        if (!file) {
            cout << "Error opening file!" << endl;
            return false;
        }
        out = &file;
    }
    else {
        out = &cout;
    }

    Node* current = list.head;
    int count = 1;
    while (current != NULL) {
        Student s = current->item;

        *out << "******************************************************STUDENT "
            << count << "******************************************************\n\n";

        s.print(*out);

        *out << "\n--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------\n";

        if (s.exam_cnt == 0) {
            *out << "\nTHIS STUDENT HAVEN'T TAKEN ANY EXAM YET\n";
        }
        else {
            for (int i = 0; i < s.exam_cnt; i++) {
                s.exam[i].print(*out);
                *out << endl;
            }
        }


        current = current->next;
        count++;
    }

    if (source == 2)
        file.close();

    return true;
}

bool FindPotentialFirstClass(List list1, List* list2, const char* course) {

    // check conditions
    if (list1.head == NULL || !list2->empty()) {
        return false;
    }

    Node* current = list1.head;
    bool found = false;

    while (current != NULL) {

        Student s = current->item;

        //  check course
        if (strcmp(s.course, course) == 0) {

            //  must have at least 3 exams
            if (s.exam_cnt >= 3) {

                int highGPAcount = 0;
                bool valid = true;

                for (int i = 0; i < s.exam_cnt; i++) {

                    double gpa = s.exam[i].gpa;

                    // calculate total credit hours 
                    int totalCredits = 0;
                    for (int j = 0; j < s.exam[i].numOfSubjects; j++) {
                        totalCredits += s.exam[i].sub[j].credit_hours;
                    }

                    // gpa not enough
                    if (gpa < 3.50) {
                        valid = false;
                        break;
                    }

                    // strong trimester
                    if (gpa >= 3.75 && totalCredits >= 12) {
                        highGPAcount++;
                    }
                }

                // final check
                if (valid && highGPAcount >= 3) {
                    list2->insert(s);  // copy student
                    found = true;
                }
            }

        }

        current = current->next;
    }

    //if no student found
    if (!found) {
        cout << "\n\nThere is no student in " << course << " that has potential to get first class\n" << endl;
    }

    return true;
}

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {

    if (list1.empty() || !list2->empty()) {
        return false;
    }

    Node* current = list1.head;

    while (current != NULL) {

        Student s = current->item;

        int yearEnroll = 2000 + (s.id[0] - '0') * 10 + (s.id[1] - '0');

        if (strcmp(s.course, course) == 0 &&
            yearEnroll == year &&
            s.totalCreditsEarned >= totalcredit) {

            list2->insert(s);
        }

        current = current->next;
    }

    return true;
}

bool DeleteStudent(List* list, char* id) {
    if (list->empty()) return false;

    Node* cur = list->head;
    int pos = 1;

    // Traverse the linked list to find the matching student ID
    while (cur != NULL) {
        if (strcmp(cur->item.id, id) == 0) {

            // Delete the node from the linked list using its position index
            list->remove(pos);

            cout << "Student with ID " << id << " deleted successfully from memory." << endl;
            return true;
        }

        cur = cur->next;
        pos++;
    }

    cout << "Student with ID " << id << " not found in the list.\n\n";
    return false;
}


bool PrintStatistic(List list) {
    if (list.empty()) {
        cout << "The student list is empty.\n";
        return false;
    }

    int totalStudents = 0;
    int cs = 0, ia = 0, ib = 0, cn = 0, ct = 0, ir = 0;

    int totalSubjects = 0;
    int totalSemesters = 0;

    // Tracks overall cumulative academic metrics across the entire cohort
    double grandTotalPoints = 0.0;
    int grandTotalCredits = 0;

    Node* cur = list.head;

    while (cur != NULL) {
        Student s = cur->item;

        totalStudents++;

        // Track enrollment breakdown per major
        if (strcmp(s.course, "CS") == 0) cs++;
        else if (strcmp(s.course, "IA") == 0) ia++;
        else if (strcmp(s.course, "IB") == 0) ib++;
        else if (strcmp(s.course, "CN") == 0) cn++;
        else if (strcmp(s.course, "CT") == 0) ct++;
        else if (strcmp(s.course, "IR") == 0) ir++;

        totalSemesters += s.exam_cnt;

        // Loop through all individual exam terms
        for (int i = 0; i < s.exam_cnt; i++) {
            Exam e = s.exam[i];

            // Loop through each subject in the exam to calculate exact credit-weighted values
            for (int j = 0; j < e.numOfSubjects; j++) {
                int credit = e.sub[j].credit_hours;
                double mark = e.sub[j].marks;

                // Standard 4.0 grading scale conversion matching your system boundaries
                double gradePoint = 0.0;
                if (mark >= 85) gradePoint = 4.0;
                else if (mark >= 80) gradePoint = 3.75;
                else if (mark >= 75) gradePoint = 3.5;
                else if (mark >= 70) gradePoint = 3.0;
                else if (mark >= 65) gradePoint = 2.5;
                else if (mark >= 60) gradePoint = 2.0;
                else if (mark >= 50) gradePoint = 1.0;
                else gradePoint = 0.0;

                grandTotalPoints += (gradePoint * credit);
                grandTotalCredits += credit;
                totalSubjects += 1;
            }
        }

        cur = cur->next;
    }

    // Cohort CGPA calculated accurately as Total Points / Total Credits Attempted
    double cohortCGPA;
    double avgSubjects;
    double avgCredits;

    if (grandTotalCredits > 0)
        cohortCGPA = grandTotalPoints / grandTotalCredits;
    else
        cohortCGPA = 0.0;

    if (totalSemesters > 0)
        avgSubjects = (double)totalSubjects / totalSemesters;
    else
        avgSubjects = 0.0;

    if (totalSemesters > 0)
        avgCredits = (double)grandTotalCredits / totalSemesters;
    else
        avgCredits = 0.0;

    // --- EXACT EXPECTED FORMAT OUTPUT MATCHING YOUR SPECIFICATION ---
    cout << "Total Students:  " << totalStudents << endl;
    cout << "CS Students - " << cs << endl;
    cout << "IA Students - " << ia << endl;
    cout << "IB Students - " << ib << endl;
    cout << "CN Students - " << cn << endl;
    cout << "CT Students - " << ct << endl;

    // CGPA printed precisely with 5 decimal places (e.g., 3.15670)
    cout << fixed << setprecision(5);
    cout << "Average CGPA: " << cohortCGPA << endl;

    // Semestral averages printed precisely with 2 decimal places (e.g., 3.23, 10.57)
    cout << fixed << setprecision(2);
    cout << "Average Subjects Taken Per Semester: " << avgSubjects << endl;
    cout << "Average Credits Earned Per Semester: " << avgCredits << endl;

    return true;
}


bool UpdateIDandPhone(List* list) {
    if (list->empty()) {
        return false;
    }

    Node* cur = list->head;
    while (cur != NULL) {
        Student& s = cur->item;

        char newId[12] = "";
        strcpy_s(newId, "B");
        strcat_s(newId, s.course);
        strcat_s(newId, s.id);
        strcpy_s(s.id, newId);

        char digits[10] = "";
        int j = 0;
        for (int i = 0; s.phone_no[i] != '\0'; i++) {
            if (s.phone_no[i] != '-') {
                digits[j++] = s.phone_no[i];
            }
        }
        digits[j] = '\0';

        char newPhone[12] = "";
        if ((digits[0] - '0') % 2 == 1) {
            strcpy_s(newPhone, "01");
        }
        else {
            strcpy_s(newPhone, "02");
        }
        strcat_s(newPhone, digits);
        strcpy_s(s.phone_no, newPhone);

        cur = cur->next;
    }

    return true;

}
