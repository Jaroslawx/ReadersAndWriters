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
                       " readers_count writers_count solution_choice"
                       "\n"
                       "Description:\n" //TODO extend description
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
    int parse_parameters(int argc, char *argv[]) {
        int temp;
        while ((temp = getopt(argc, argv, "R W C")) != -1) {
            switch (temp) {
                case 'R':
                    if (sscanf(optarg, "%u", &readers_count) < 1)
                        return -1;
                    break;
                case 'W':
                    if (sscanf(optarg, "%u", &writers_count) < 1)
                        return -2;
                    break;
                case 'C':
                    if (sscanf(optarg, "%u", &choice) < 1)
                        return -3;
                    break;
                default:
                    cout << "Invalid arguments!\n" << endl;
                    break;
            }
        }

        return 0;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3){
        cout << " Not enough arguments!\n" << endl;
        return -1;
    }

    parse::parse_parameters(argc, argv);

    return 0;
}
