#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// Maximum number of treatments and patients
const int MAX_TREATMENTS = 100;
const int MAX_PATIENTS = 100;

// Treatment class
class Treatment {
public:
    string type;
    string date;

    Treatment(string type, string date) {
        this->type = type;
        this->date = date;
    }

    Treatment() : type(""), date("") {}
};

// Patient class
class Patient {
public:
    int id;
    string name;
    string treatmentType;
    bool admitted;
    Treatment treatments[MAX_TREATMENTS];
    int treatmentCount;

    Patient(int id, string name, string treatmentType) {
        this->id = id;
        this->name = name;
        this->treatmentType = treatmentType;
        this->admitted = false;
        this->treatmentCount = 0;
    }

    Patient() : id(0), name(""), treatmentType(""), admitted(false), treatmentCount(0) {}

    void addTreatment(Treatment treatment) {
        if (treatmentCount < MAX_TREATMENTS) {
            treatments[treatmentCount++] = treatment;
        }
    }
};

// Linked List class for managing patient records
class LinkedList {
public:
    struct Node {
        Patient* data;
        Node* next;

        // Node constructor
        Node(Patient* patient) : data(patient), next(nullptr) {}
    };

    LinkedList() : head(nullptr) {}

    // Function to get the head node
    Node* getHead() const {
        return head;
    }

    void addPatient(Patient* patient) {
        Node* newNode = new Node(patient);
        newNode->next = head;
        head = newNode;
    }

    void removePatient(int id) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data->id == id) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    Patient* findPatient(int id) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data->id == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayPatients() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Patient ID: " << current->data->id << ", Name: " << current->data->name << ", Treatment: " << current->data->treatmentType << ", Admitted: " << (current->data->admitted ? "Yes" : "No") << endl;
            current = current->next;
        }
    }

private:
    Node* head;
};

// Stack class for managing patient admissions
class Stack {
private:
    Patient* stack[MAX_PATIENTS];
    int top;

public:
    Stack() : top(-1) {}

    void push(Patient* patient) {
        if (top < MAX_PATIENTS - 1) {
            stack[++top] = patient;
        }
    }

    Patient* pop() {
        if (top == -1) {
            return nullptr;
        }
        return stack[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    void displayPatients() {
        for (int i = 0; i <= top; ++i) {
            cout << "Patient ID: " << stack[i]->id << ", Name: " << stack[i]->name << ", Treatment: " << stack[i]->treatmentType << ", Admitted: Yes" << endl;
        }
    }

    Patient* findAndRemovePatient(int id) {
        std::stack<Patient*> tempStack;
        Patient* foundPatient = nullptr;

        while (!isEmpty()) {
            Patient* patient = pop();
            if (patient->id == id) {
                foundPatient = patient;
                break;
            }
            tempStack.push(patient);
        }

        while (!tempStack.empty()) {
            push(tempStack.top());
            tempStack.pop();
        }

        return foundPatient;
    }
};

// Queue class for managing patient discharges
class Queue {
private:
    Patient* queue[MAX_PATIENTS];
    int front, rear;

public:
    Queue() : front(0), rear(0) {}

    void enqueue(Patient* patient) {
        if (rear < MAX_PATIENTS) {
            queue[rear++] = patient;
        }
    }

    Patient* dequeue() {
        if (front == rear) {
            return nullptr;
        }
        return queue[front++];
    }

    bool isEmpty() {
        return front == rear;
    }

    void displayPatients() {
        for (int i = front; i < rear; ++i) {
            cout << "Patient ID: " << queue[i]->id << ", Name: " << queue[i]->name << ", Treatment: " << queue[i]->treatmentType << ", Admitted: No" << endl;
        }
    }
};

// Function to search patients by name
Patient* searchByName(LinkedList& patientRecords, string name, int& count) {
    static Patient* matchingPatients[MAX_PATIENTS];
    count = 0;
    LinkedList::Node* current = patientRecords.getHead();
    while (current != nullptr) {
        if (current->data->name == name) {
            matchingPatients[count++] = current->data;
        }
        current = current->next;
    }
    return *matchingPatients;
}

// Function to search patients by treatment type
Patient* searchByTreatment(LinkedList& patientRecords, string treatmentType, int& count) {
    static Patient* matchingPatients[MAX_PATIENTS];
    count = 0;
    LinkedList::Node* current = patientRecords.getHead();
    while (current != nullptr) {
        if (current->data->treatmentType == treatmentType) {
            matchingPatients[count++] = current->data;
        }
        current = current->next;
    }
    return *matchingPatients;
}

// Function to sort patients by treatment date
bool compareByTreatmentDate(Patient* p1, Patient* p2) {
    if (p1->treatmentCount == 0 || p2->treatmentCount == 0) {
        return false;
    }
    return p1->treatments[0].date < p2->treatments[0].date;
}

void sortByTreatmentDate(LinkedList& patientRecords) {
    // Extract patients into an array
    Patient* patients[MAX_PATIENTS];
    int count = 0;
    LinkedList::Node* current = patientRecords.getHead();
    while (current != nullptr) {
        patients[count++] = current->data;
        current = current->next;
    }

    // Sort the array using bubble sort
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (!compareByTreatmentDate(patients[j], patients[j + 1])) {
                swap(patients[j], patients[j + 1]);
            }
        }
    }

    // Reconstruct the linked list in sorted order
    patientRecords = LinkedList();
    for (int i = count - 1; i >= 0; --i) {
        patientRecords.addPatient(patients[i]);
    }
}

// Function to generate a summary report
void generateSummaryReport(LinkedList& patientRecords, Stack& admissions, Queue& discharges) {
    cout << "Summary Report:" << endl;
    cout << "Admitted Patients:" << endl;
    LinkedList::Node* current = patientRecords.getHead();
    while (current != nullptr) {
        // Print admitted patients
        if (current->data->admitted) {
            cout << "Patient ID: " << current->data->id << ", Name: " << current->data->name << ", Treatment: " << current->data->treatmentType << ", Admitted: Yes" << endl;
        }
        current = current->next;
    }

    // Print patients scheduled for discharge
    cout << "Patients Scheduled for Discharge:" << endl;
    discharges.displayPatients();

    // Print out-patient treatments
    cout << "Out-Patient Treatments:" << endl;
    patientRecords.displayPatients();
}

// Function to display menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add New Patient\n";
    cout << "2. Delete Patient Record\n";
    cout << "3. Display All Patients\n";
    cout << "4. Admit a Patient\n";
    cout << "5. Discharge a Patient\n";
    cout << "6. Add Treatment to a Patient\n";
    cout << "7. Search Patient by Name\n";
    cout << "8. Search Patient by ID\n";
    cout << "9. Search Patient by Treatment Type\n";
    cout << "10. Sort Patients by Treatment Date\n";
    cout << "11. Generate Summary Report\n";
    cout << "12. Exit\n";
    cout << "Enter your choice: ";
}

// Function to search patient by ID
Patient* searchById(LinkedList& patientRecords, int id) {
    return patientRecords.findPatient(id);
}

// Function to add a new patient
void addNewPatient(LinkedList& patientRecords) {
    int id;
    string name, treatmentType;
    cout << "Enter Patient ID: ";
    cin >> id;
    cout << "Enter Patient Name: ";
    cin >> name;
    cout << "Enter Treatment Type: ";
    cin >> treatmentType;
    Patient* patient = new Patient(id, name, treatmentType);
    patientRecords.addPatient(patient);
    cout << "Patient added successfully." << endl;
}

// Function to delete a patient's record
void deletePatientRecord(LinkedList& patientRecords) {
    int id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;
    patientRecords.removePatient(id);
    cout << "Patient record deleted successfully." << endl;
}

int main() {
    LinkedList patientRecords;
    Stack admissions;
    Queue discharges;

    // Add preset patients
    Patient* patient1 = new Patient(1, "John Doe", "Surgery");
    patientRecords.addPatient(patient1);

    Patient* patient2 = new Patient(2, "Jane Smith", "Cardiology");
    patientRecords.addPatient(patient2);

    Patient* patient3 = new Patient(3, "Michael Johnson", "Orthopedics");
    patientRecords.addPatient(patient3);

    Patient* patient4 = new Patient(4, "Emily Brown", "Pediatrics");
    patientRecords.addPatient(patient4);

    Patient* patient5 = new Patient(5, "David Lee", "Oncology");
    patientRecords.addPatient(patient5);

    Patient* patient6 = new Patient(6, "Alice Walker", "Neurology");
    patientRecords.addPatient(patient6);

    Patient* patient7 = new Patient(7, "Bob Martin", "Dermatology");
    patientRecords.addPatient(patient7);

    Patient* patient8 = new Patient(8, "Carol King", "Psychiatry");
    patientRecords.addPatient(patient8);

    Patient* patient9 = new Patient(9, "Dan Moore", "Gastroenterology");
    patientRecords.addPatient(patient9);

    Patient* patient10 = new Patient(10, "Eve Turner", "ENT");
    patientRecords.addPatient(patient10);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addNewPatient(patientRecords);
                break;
            case 2:
                deletePatientRecord(patientRecords);
                break;
            case 3:
                patientRecords.displayPatients();
                break;
            case 4: {
                int id;
                cout << "Enter Patient ID to admit: ";
                cin >> id;
                Patient* patient = patientRecords.findPatient(id);
                if (patient != nullptr) {
                    patient->admitted = true;
                    admissions.push(patient);
                    cout << "Patient admitted successfully." << endl;
                } else {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 5: {
                int id;
                cout << "Enter Patient ID to discharge: ";
                cin >> id;
                Patient* patient = admissions.findAndRemovePatient(id);
                if (patient != nullptr) {
                    patient->admitted = false;
                    discharges.enqueue(patient);
                    cout << "Patient discharged successfully." << endl;
                } else {
                    cout << "Patient not found in admissions." << endl;
                }
                break;
            }
            case 6: {
                int id;
                string type, date;
                cout << "Enter Patient ID to add treatment: ";
                cin >> id;
                cout << "Enter Treatment Type: ";
                cin >> type;
                cout << "Enter Treatment Date (YYYY-MM-DD): ";
                cin >> date;
                Patient* patient = patientRecords.findPatient(id);
                if (patient != nullptr) {
                    patient->addTreatment(Treatment(type, date));
                    cout << "Treatment added successfully." << endl;
                } else {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 7: {
                string name;
                int count;
                cout << "Enter Patient Name to search: ";
                cin >> name;
                Patient* patients = searchByName(patientRecords, name, count);
                if (count > 0) {
                    for (int i = 0; i < count; ++i) {
                        cout << "Patient ID: " << patients[i].id << ", Name: " << patients[i].name << ", Treatment: " << patients[i].treatmentType << ", Admitted: " << (patients[i].admitted ? "Yes" : "No") << endl;
                    }
                } else {
                    cout << "No patients found with the name " << name << "." << endl;
                }
                break;
            }
            case 8: {
                int id;
                cout << "Enter Patient ID to search: ";
                cin >> id;
                Patient* patient = searchById(patientRecords, id);
                if (patient != nullptr) {
                    cout << "Patient ID: " << patient->id << ", Name: " << patient->name << ", Treatment: " << patient->treatmentType << ", Admitted: " << (patient->admitted ? "Yes" : "No") << endl;
                } else {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 9: {
                string treatmentType;
                int count;
                cout << "Enter Treatment Type to search: ";
                cin >> treatmentType;
                Patient* patients = searchByTreatment(patientRecords, treatmentType, count);
                if (count > 0) {
                    for (int i = 0; i < count; ++i) {
                        cout << "Patient ID: " << patients[i].id << ", Name: " << patients[i].name << ", Treatment: " << patients[i].treatmentType << ", Admitted: " << (patients[i].admitted ? "Yes" : "No") << endl;
                    }
                } else {
                    cout << "No patients found with the treatment type " << treatmentType << "." << endl;
                }
                break;
            }
            case 10:
                sortByTreatmentDate(patientRecords);
                cout << "Patients sorted by treatment date." << endl;
                break;
            case 11:
                generateSummaryReport(patientRecords, admissions, discharges);
                break;
            case 12:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
