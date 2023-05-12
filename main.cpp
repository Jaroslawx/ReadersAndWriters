#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <ctime>

unsigned int readers_count, writers_count; // number of all readers and writers
unsigned int reading, writing; // number of readers, writers actually in reading room
int choice = 1; // choice of solution

#define printStatus() \
std::cout << "ReaderQ: %i WriterQ: %i [in: R: %i W: %i]\n ", readers_count, writers_count, reading, writing;

//Needed?
//#define randomTime() (rand() % 1000;) // random time between 0 and 1000

using namespace std;

#include "first_solution.h"
#include "second_solution.h"
#include "third_solution.h"

namespace common {
    void display_usage (int readers, int writers) {
        string usage = "Usage: "
                       " readersCount writersCount solution_choice"
                       "\n"
                       "Description:\n"
                       "    ReadersAndWriters is a program that simulates the Readers and Writers problem.\n"
                       "\n"
                       "Options:\n"
                       "  1 or 2 or 3 choose between available solutions\n"
                       "\n"
                       "Example usage:\n"
                       "10 3 2\n";
        cout << usage << endl;
    }

}

namespace parse {

}

int main(int argc, char *argv[]) {

    if (argc < 3){
        return -1;
    }

    int readers_count = atoi(argv[1]);
    int writers_count = atoi(argv[2]);
    int choice = atoi(argv[3]);

    return 0;
}
