#include <iostream>
#include <atomic>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <random>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

//unsigned int readers_count, writers_count; // number of all readers and writers
unsigned int readers_count, writers_count; // number of readers and writers waiting in queue
std::atomic<int> reading = 0, writing = 0; // number of readers, writers actually in reading room
#define debug_detail true

//#define print_status() printf("ReaderQ: %i WriterQ: %i [in: R: %i W: %i]\n ", readers_count - reading, writers_count - writing, reading, writing);
//#define print_status() printf("[queue: R: %i W: %i] [in: R: %i W: %i]\n ", readers_count - reading, writers_count - writing, reading, writing);

using namespace std;

namespace watchdog {
    void perform_check() {
        //library is empty
        if (readers_count == 0 && writers_count == 0) {
            return;
        }

        //first condition - only one of them can be > 0
        if (reading > 0 && writing > 0) {
            cout << "Error: reading and writing at the same time!" << endl;
            exit(-1);
        }
    }
}

namespace portable {

    int randomNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(3, 5);
        return dis(gen);
    }

    string get_current_date_time() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        string date = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
        return date;
    }

    void print_status() {
        cout << get_current_date_time() << " [queue: R: " << readers_count - reading << " W: " << writers_count - writing
             << "] [in: R: "
             << reading << " W: " << writing << "]" << endl;
        watchdog::perform_check();

    }

    enum Action {
        READER_ENTER = 0, READER_LEFT = 1, WRITER_ENTER = 2, WRITER_LEFT = 3
    };

    void rr_statement(Action type, int time = -1) {
    #if debug_detail
        pid_t x = syscall(__NR_gettid);
        int type_int = static_cast<int>(x);
        string date = get_current_date_time();

        if (type == 0) {
            cout << date << " Reader " << type_int << " reads for " << time << " seconds" << endl;
        } else if (type == 1) {
            cout << date << " Reader " << type_int << " left reading room" << endl;
        } else if (type == 2) {
            cout << date << " Writer " << type_int << " writes for " << time << " seconds" << endl;
        } else if (type == 3) {
            cout << date << " Writer " << type_int << " left reading room" << endl;
        }
    #endif
    }
}

#include "first_solution.h"
#include "second_solution.h"
#include "third_solution.h"

namespace common {
    void display_usage() {
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
                       "-R:10 -W:3 -S:1\n";
        cout << usage << endl;
    }

    bool string_contain(const string &text, const string &contains) {
        if (text.find(contains, 0) != string::npos) {
            return true;
        }
        return false;
    }


}

namespace parse {
    void parse_parameter(const string &arg, int &choice) {
        if (common::string_contain(arg, "-R:")) {
            try {
                string readers_str = arg.substr(arg.find(':') + 1);
                readers_count = stoi(readers_str);

            } catch (exception &e) {
                cerr << "Failed to parse readers parameter " << arg << " due to: " << e.what() << endl;
                exit(-1);
            }
        } else if (common::string_contain(arg, "-W:")) {
            try {
                string writers_str = arg.substr(arg.find(':') + 1);
                writers_count = stoi(writers_str);

            } catch (exception &e) {
                cerr << "Failed to parse writers parameter " << arg << " due to: " << e.what() << endl;
                exit(-2);
            }
        } else if (common::string_contain(arg, "-S:")) {
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
    int choice = 0;

    for (int i = 0; i < 10; ++i) {
        cout << portable::randomNumber() << endl;
    }

    if (argc < 4) {
        cout << " Not enough arguments!\n" << endl;
        common::display_usage();
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        parse::parse_parameter(argv[i], choice);
    }

    parse::rw_reset();
    run::start_solution(choice);

    return 0;
}
