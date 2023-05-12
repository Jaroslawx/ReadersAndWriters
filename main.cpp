#include <iostream>
#include <unistd.h>
#include <pthread.h>

volatile unsigned int readersCount, writersCount; // number of all readers and writers
volatile unsigned int reading, writing; // number of readers, writers actually in reading room

#define CHOICE 1 // choice of solution

#define printStatus() \
std::cout << "ReaderQ: %i WriterQ: %i [in: R: %i W: %i]\n ", readersCount, writersCount, reading, writing;

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

int main(int argc, char **argv) {
    cout << "Test" << endl;
    return 0;
}
