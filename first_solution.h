#ifndef READERSANDWRITERS_FIRST_SOLUTION_H
#define READERSANDWRITERS_FIRST_SOLUTION_H

pthread_mutex_t readerMutex;
pthread_mutex_t writersLock;

namespace first_solution {
    void display_usage () {
        string usage = "Solution description:\n"
                       "    The solution with the possibility of writers starvation.\n";
        cout << usage << endl;
    }

    void* reader(void* arg) {

        // TODO add reading action

        return NULL;
    }

    void* writer(void* arg) {

        // TODO add writing action

        return NULL;
    }

    // TODO ask is it our main for first solution? | Need put here main action?
    void run() {
        cout << "First solution" << endl;

        pthread_mutex_init(&readerMutex, nullptr);
        pthread_mutex_init(&writersLock, nullptr);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

    }
}

#endif
