## pekServer: Server and Client program


```sh
_____________           _____________           _____________
|           |           |           |           |           |
|           |           |           |           |           |
|  Network  |---------> | ServerLib | --------->|   Server  |
|  Handling |           |           |           |           |
|           |           |           |           |           |
-------------           -------------           -------------
      |                 _____________           _____________
      |                 |           |           |           |
      |                 | ClientLib | --------->|  Client   |
      -------------->   |           |           |           |
                        |           |           |           |
                        -------------           -------------

```

Network Handling (neth.h)
It includes functions for initialization, network cleanup, create and closing socket with basic system headers for the network.


A single-threaded TCP server that handles thousands of concurrent clients, processes requests via a thread pool, and supports runtime extension through dynamically loaded plugins.

It just blocked when recieved. No non‑blocking event loop (like epoll/kqueue) is used.
