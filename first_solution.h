#ifndef READERSANDWRITERS_FIRST_SOLUTION_H
#define READERSANDWRITERS_FIRST_SOLUTION_H

// TODO ask is it good thinking process? good way to solve the problem?
pthread_mutex_t readerMutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
pthread_mutex_t writersLock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

namespace first_solution {
    void display_usage() {
        string usage = "Solution description:\n"
                       "    The solution with the possibility of writers starvation.\n";
        cout << usage << endl;
    }

    void *reader(void *arg) {

        // TODO add reading action

        return NULL;
    }

    void *writer(void *arg) {

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
