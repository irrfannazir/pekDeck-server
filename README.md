## pekServer: Server and Client program


```sh
_____________           _____________           _____________
|           |           |           |           |           |
|           |           |           |           |           |
|           |---------> | ServerLib | --------->|   Server  |
|   nlib    |           |           |           |           |
|           |           |           |           |           |
-------------           -------------           -------------
      |                 _____________           _____________
      |                 |           |           |           |
      |                 | ClientLib | --------->|  Client   |
      -------------->   |           |           |           |
                        |           |           |           |
                        -------------           -------------

```

A single-threaded TCP server that handles thousands of concurrent clients, processes requests via a thread pool, and supports runtime extension through dynamically loaded plugins.

It just blocked when recieved. No non‑blocking event loop (like epoll/kqueue) is used.
