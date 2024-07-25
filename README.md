# To-do list application

## Overview
This is a command-line based To-Do List application written in C++. Users can register, log in, and manage their tasks. Tasks and user data are saved to text files for persistence.

## Features
- User registration and login
- Task management (add, complete, view tasks)
- Persistent storage

## Getting Started
### Prerequisites
- C++ compiler (e.g., g++)
- Standard C++ library

### Building the Project
1. Clone the repository:

    ```git clone https://github.com/midoriya-2-0/CodeAlpha_To_do_list_application.git```

    ```cd CodeAlpha_To_do_list_application.git ```

2. Compile the project:

    ```g++ -o todo main.cpp```

3. Run the executable:

   ```./todo```

## Usage
1. Run the application.
2. Register or log in.
3. Use the menu to manage tasks:
   - `1. Add Task`
   - `2. Mark Task as Completed`
   - `3. View Tasks`
   - `4. View Completed Tasks`
   - `5. Exit`

## File Structure
- `main.cpp: The main source file.`
- `users.txt: Stores user credentials.`
- `[username]_tasks.txt: Stores user tasks.`
- `[username]_completed_tasks.txt: Stores completed tasks.`

## License
This project is licensed under the MIT License.
