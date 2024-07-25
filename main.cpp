#include <bits/stdc++.h>
using namespace std;
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class ToDoList
{
private:
    struct Task
    {
        string Task_Name;
        bool completed;
    };

    vector<Task> tasks;
    string taskFile;
    string completedTaskFile;

    void loadTasks()
    {
        ifstream file(taskFile);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                tasks.push_back({line, false});
            }
            file.close();
        }
    }

    void saveTasks()
    {
        ofstream file(taskFile, ios::trunc);
        if (file.is_open())
        {
            for (const auto &task : tasks)
            {
                if (!task.completed)
                {
                    file << task.Task_Name << endl;
                }
            }
            file.close();
        }
    }

    void saveCompletedTasks(const string &Task_Name)
    {
        ofstream file(completedTaskFile, ios::app);
        if (file.is_open())
        {
            file << Task_Name << endl;
            file.close();
        }
    }

public:
    ToDoList(const string &username)
    {
        taskFile = username + "_tasks.txt";
        completedTaskFile = username + "_completed_tasks.txt";
        loadTasks();
    }

    ~ToDoList()
    {
        saveTasks();
    }

    void addTask(const string &Task_Name)
    {
        tasks.push_back({Task_Name, false});
        ofstream file(taskFile, ios::app);
        if (file.is_open())
        {
            file << Task_Name << endl;
            file.close();
        }
    }

    void markTaskCompleted(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks[index].completed = true;
            saveCompletedTasks(tasks[index].Task_Name);
        }
        else
        {
            cout << "Invalid task index." << endl;
        }
    }

    void viewTasks() const
    {
        if (tasks.empty())
        {
            cout << "No tasks available." << endl;
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i)
        {
            if (!tasks[i].completed)
            {
                cout << YELLOW << i + 1 << ". " << tasks[i].Task_Name << RESET << endl;
            }
        }
    }

    void viewCompletedTasks() const
    {
        ifstream file(completedTaskFile);
        if (file.is_open())
        {
            string line;
            int count = 1;
            while (getline(file, line))
            {
                cout << GREEN << count << ". " << line << RESET << endl;
                count++;
            }
            file.close();
        }
        else
        {
            cout << "No completed tasks available." << endl;
        }
    }
};

class UserManager
{
private:
    const string userFile = "users.txt";

    bool userExists(const string &username)
    {
        ifstream file(userFile);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find(username + " - ") == 0)
                {
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    bool passwordExists(const string &password)
    {
        ifstream file(userFile);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find(" - " + password) != string::npos)
                {
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    bool validateUser(const string &username, const string &password)
    {
        ifstream file(userFile);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line == username + " - " + password)
                {
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    void saveUser(const string &username, const string &password)
    {
        ofstream file(userFile, ios::app);
        if (file.is_open())
        {
            file << username << " - " << password << endl;
            file.close();
        }
    }

public:
    bool registerUser(const string &username, const string &password)
    {
        if (userExists(username))
        {
            cout << RED << "Username already exists. Please try a different one." << RESET << endl;
            return false;
        }
        if (passwordExists(password))
        {
            cout << RED << "Password already in use. Please try a different one." << RESET << endl;
            return false;
        }
        saveUser(username, password);
        return true;
    }

    bool loginUser(const string &username, const string &password)
    {
        if (validateUser(username, password))
        {
            return true;
        }
        else
        {
            cout << RED << "Invalid username or password." << RESET << endl;
            return false;
        }
    }
};

int main()
{
    UserManager userManager;
    ToDoList *toDoList = nullptr;
    int choice;
    string username, password;

    do
    {
        cout << "\nTO-DO LIST APPLICATION\n";
        cout << "------------------------\n";
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (choice == 1)
        {
            if (userManager.registerUser(username, password))
            {
                cout << "Registration successful. Please log in." << endl;
                cout << "------------------------" << endl;
            }
        }

        if (choice == 2 && userManager.loginUser(username, password))
        {
            cout << "Login successful." << endl;
            cout << "------------------------" << endl;
            toDoList = new ToDoList(username);
            break;
        }
    } while (true);

    do
    {
        cout << "\n1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. View Tasks\n";
        cout << "4. View Completed Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "------------------------" << endl;

        switch (choice)
        {
        case 1:
        {
            string Task_Name;
            cout << "Enter task name: ";
            cin.ignore(); // To ignore the newline character left by cin
            getline(cin, Task_Name);
            toDoList->addTask(Task_Name);
            cout << "\nTask added successfully." << endl;
            cout << "------------------------" << endl;
            break;
        }
        case 2:
        {
            int index;
            cout << "Enter task number to mark as completed: ";
            cin >> index;
            toDoList->markTaskCompleted(index - 1);
            break;
        }
        case 3:
            toDoList->viewTasks();
            cout << "------------------------" << endl;
            break;
        case 4:
            toDoList->viewCompletedTasks();
            cout << "------------------------" << endl;
            break;
        case 5:
            cout << "Exiting application." << endl;
            delete toDoList;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}