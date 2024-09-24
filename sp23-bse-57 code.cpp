#include <iostream>
#include <string>

using namespace std;

// Node structure to represent each task
struct Node {
    int task_id;
    string description;
    int priority;
    Node *next;

    Node(int tid, string desc, int pri) {
        task_id = tid;
        description = desc;
        priority = pri;
        next = NULL;
    }
};

class TaskManagementSystem {
public:
    Node *head = NULL;

    // Insert task at the correct position based on priority (higher priority first)
    void insert_task(int tid, string description, int priority) {
        Node *task = new Node(tid, description, priority);

        if (head == NULL || head->priority < priority) { // Insert at the start if head is null or higher priority
            task->next = head;
            head = task;
        } else {
            Node *current = head;
            while (current->next != NULL && current->next->priority >= priority) {  // Traverse to the correct position
                current = current->next;
            }
            task->next = current->next;
            current->next = task;
        }
    }

    // Print all tasks
    void print_tasks() {
        if (head == NULL) {
            cout << "No tasks available." << endl;
            return;
        }

        Node *current = head;
        while (current != NULL) {
            cout << "Task ID: " << current->task_id
                 << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    // Delete the task with the highest priority (first task in the list)
    void delete_from_start() {
        if (head == NULL) {
            cout << "No tasks to delete." << endl;
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
        cout << "Task with the highest priority deleted." << endl;
    }

    // Delete a specific task by its ID
    void delete_task_using_id(int tid) {
        if (head == NULL) {
            cout << "No tasks to delete." << endl;
            return;
        }

        if (head->task_id == tid) {
            delete_from_start();  // If the task to be deleted is the first one
            return;
        }

        Node *current = head;
        while (current->next != NULL && current->next->task_id != tid) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Task with ID " << tid << " not found." << endl;
        } else {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            cout << "Task with ID " << tid << " deleted." << endl;
        }
    }
};

int main() {
    TaskManagementSystem tms;
    int choice, tid, priority;
    string description;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> tid;
                cout << "Enter task description: ";
                cin.ignore();  // To ignore the newline character after integer input
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                tms.insert_task(tid, description, priority);
                break;
            case 2:
                tms.print_tasks();
                break;
            case 3:
                tms.delete_from_start();
                break;
            case 4:
                cout << "Enter task ID to delete: ";
                cin >> tid;
                tms.delete_task_using_id(tid);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
