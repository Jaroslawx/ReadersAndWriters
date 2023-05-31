#include <iostream>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>

unsigned int readers_count, writers_count; // number of all readers and writers
unsigned int reading, writing; // number of readers, writers actually in reading room
int choice = 1; // choice of solution //TODO: remove, put to int main()

#define print_status() \
std::cout << "ReaderQ: %i WriterQ: %i [in: R: %i W: %i]\n ", readers_count - reading, writers_count - writing, reading, writing;

#define random_time() (rand() % 100) // random time between 0 and 100

using namespace std;

#include "first_solution.h"
#include "second_solution.h"
#include "third_solution.h"

namespace common {
    void display_usage(int readers, int writers) {
        string usage = "Usage: "
                       " readers_count writers_count solution_choice"
                       "\n"
                       "Description:\n"
                       "    Readers and Writers is a program that aims to solve the problem of readers and writers using a certain reading room. In this reading room there can be any number of readers at the same time, one writer or none. There are three different solutions to this problem: the first allows for starvation of writers, the second allows for starvation of readers, and the third eliminates starvation.\n"
                       "\n"
                       "Options:\n"
                       "  1, 2 or 3 choose between available solutions\n"
                       "\n"
                       "Example usage:\n"
                       "R:10 W:3 S:1\n";
        cout << usage << endl;
    }

    bool string_contain(const string &text, const string &contains) {
        if (text.find(contains, 0) != string::npos) {
            return true;
        }
        return false;
    }

    // announcing if someone enter or leave to reading room, TODO: need?
    void rr_statement() {
        cout << "announcement" << endl;
    }
}

namespace parse {
    void parse_parameter(const string &arg) {
        if (common::string_contain(arg, "R:")) {
            try {
                string readers_str = arg.substr(arg.find(':') + 1);
                readers_count = stoi(readers_str);

            } catch (exception &e) {
                cerr << "Failed to parse readers parameter " << arg << " due to: " << e.what() << endl;
                exit(-1);
            }
        } else if (common::string_contain(arg, "W:")) {
            try {
                string writers_str = arg.substr(arg.find(':') + 1);
                writers_count = stoi(writers_str);

            } catch (exception &e) {
                cerr << "Failed to parse writers parameter " << arg << " due to: " << e.what() << endl;
                exit(-2);
            }
        } else if (common::string_contain(arg, "S:")) {
            try {
                string solution_str = arg.substr(arg.find(':') + 1);
                choice = stoi(solution_str);

            } catch (exception &e) {
                cerr << "Failed to parse solution parameter " << arg << " due to: " << e.what() << endl;
                exit(-3);
            }
        } else {
            cerr << "Unknown parameter " << arg << endl;
            exit(-4);
        }
    }

    // readers and writers reset
    void rw_reset() {
        reading = 0;
        writing = 0;
    }

}

namespace run {
    void start_solution(int choice) {
        switch (choice) {
            case 1:
                first_solution::run();
                break;
            case 2:
                second_solution::run();
                break;
            case 3:
                third_solution::run();
                break;
            default:
                cout << "Invalid choice!\n" << endl;
                break;
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        cout << " Not enough arguments!\n" << endl;
        return -1;
    }

    vector<string> args;
    for (int i = 1; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    for (const auto &item: args) {
        parse::parse_parameter(item);
    }

    parse::rw_reset();

    //TODO there shouldn't be a global variable here
    run::start_solution(choice);

    return 0;
}
