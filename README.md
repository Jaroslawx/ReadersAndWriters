# Readers and Writers Problem

## Description

Readers and Writers is a C++ program that addresses the classic synchronization problem of readers and writers accessing a shared resource (in this case, a reading room). The program provides three different solutions to this problem, each tackling issues such as starvation of readers or writers.

## Usage

```shell
./readers_writers readers_count writers_count solution_choice
```

## Parameters
<li>readers_count: Number of concurrent readers allowed.</li><li>
writers_count: Number of concurrent writers allowed.</li><li>
solution_choice: Choose between three different solutions to the problem (1, 2, or 3).</li>

## Solutions
<ol><li>
Starvation of Writers: Allows starvation of readers.</li><li>
Starvation of Readers: Allows starvation of writers.</li><li>
No Starvation: Eliminates starvation by fairly scheduling readers and writers.</li>
</ol>

## Example
```shell
./readers_writers -R:10 -W:3 -S:1
```
This example runs the program with 10 readers (-R:10), 3 writers (-W:3), and uses the first solution (-S:1).

## Implementation Details
The project is implemented in C++ and uses synchronization primitives such as mutexes and semaphores to manage concurrent access to the shared resource.

## Requirements
<li>C++ compiler that supports C++11 or later.</li><li>
POSIX threads (pthreads) for synchronization primitives.</li>

## Installation

### 1. Clone the repository:
```shell
git clone https://github.com/Jaroslawx/ReadersAndWriters
cd ReadersAndWriters
```

### 2. Build the application
```shell
mkdir build
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```

### 3. Run the application
```shell
./readers_writers -R:10 -W:3 -S:1
```

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/Jaroslawx/ReadersAndWriters/blob/master/LICENSE) file for details.
