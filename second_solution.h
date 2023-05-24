#ifndef READERSANDWRITERS_SECOND_SOLUTION_H
#define READERSANDWRITERS_SECOND_SOLUTION_H

namespace second_solution {
    unsigned int writing_or_waiting = 0; // The number of writers waiting for access to the reading room or writing (max one at the moment).

    pthread_mutex_t readerMutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
    pthread_mutex_t writerMutex; // A binary semaphore that provides access to the input or output section to only one writer at a time.

    pthread_mutex_t readerLock; // A binary semaphore that blocks access to the reading room for all readers or grants only one at a time.
    pthread_mutex_t writerLock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

    void display_info() {
        string info = "Second solution\n"
                      "Description:\n"
                      "    The solution with the possibility of readers starvation.\n";
        cout << info << endl;
    }

    void* reader(void *arg) {
        srand(time(NULL));
        while(true) {

        }
    }

    void* writer(void *arg) {
        srand(time(NULL));
        while(true) {

        }
    }

    void run() {
        display_info();

        pthread_mutex_init(&readerMutex, NULL);
        pthread_mutex_init(&writerMutex, NULL);
        pthread_mutex_init(&readerLock, NULL);
        pthread_mutex_init(&writerLock, NULL);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

        unsigned int i;
    }
}

#endif
