# Bank-System
Bank Management System (C Language)

This is a simple console-based Bank Management System developed in the C programming language. The project simulates basic banking operations and supports two types of users: Admin and Client.
-Features:
  -Admin Functions:
    -Admin login using username and password
    -Create new client bank accounts
    -View and manage client accounts
    -Change account status (Active / Restricted / Closed)
    -Make transactions between accounts
    -Deposit and withdraw funds
  
  -Client Functions:
    -Login using bank account ID and password
    -View account details
    -Make transactions
    -Deposit and withdraw funds
    -Change account password
  
  -Technical Details:
    -Language: C
    -Data Structure Used: Linked Lists
    -Interface: Console-based
    -Data Handling: In-memory (no file/database persistence)
    -ID & Password Generation: Randomly generated during account creation

-Notes
  -This project is intended for educational purposes.
  -All data is lost when the program terminates, as it is stored in memory.

-Future Improvements
  -Add file or database persistence
  -Improve user input validation and error handling
  -Implement graphical interface or web-based frontend
