# WordsServer

**WordsServer** is a modular, multithreaded TCP server written in C++ using the **Reactor design pattern**.  
This project is part of a desktop application for learning English vocabulary through interactive games.

---

## Features

- Core networking based on the Reactor pattern
- Architecture:
    - `ClientHandler` / `ServerHandler` for managing socket events
    - `TaskManager` for handling incoming and outgoing messages
    - `ThreadPool` (planned) for background task execution
- Non-blocking sockets using `select()`
- Basic message receive/send queues per client
- Windows Sockets (WinSock) support

---


