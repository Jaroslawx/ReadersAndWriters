#ifndef READERSANDWRITERS_FIRST_SOLUTION_H
#define READERSANDWRITERS_FIRST_SOLUTION_H

pthread_mutex_t readerMutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
pthread_mutex_t writersLock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

namespace first_solution {
    void display_usage() {
        string usage = "Solution description:\n"
                       "    The solution with the possibility of writers starvation.\n";
        cout << usage << endl;
    }

    void *reader(void *arg) {

        srand(time(NULL));
        while (true) {
            pthread_mutex_lock(&readerMutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            if (reading == 0) { // If this is first reader entering reading room after writer
                pthread_mutex_lock(&writersLock); // The reader blocks access to the reading room for all writers.
            }
            reading++; // The reader enters the reading room.
            printStatus();
            pthread_mutex_unlock(&readerMutex); // The reader releases the enter section to other readers.

            usleep(randomTime()); // The reader reads for a random time.

            pthread_mutex_lock(&readerMutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            reading--; // The reader leaves the reading room.

            if (reading == 0) { // If this is last reader leaving reading room
                pthread_mutex_unlock(&writersLock); // The reader releases the reading room for all writers.
            }
            pthread_mutex_unlock(&readerMutex); // The reader releases the enter section to other readers.

            usleep(randomTime()); // The reader stands in the queue for a random time.
        }

        return NULL;
    }

    void *writer(void *arg) {

        //TODO add writer action

        return NULL;
    }

    //TODO ask is it our main for first solution? | Need put here main action?
    void run() {
        cout << "First solution" << endl;

        pthread_mutex_init(&readerMutex, nullptr);
        pthread_mutex_init(&writersLock, nullptr);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

    }
}

#endif
