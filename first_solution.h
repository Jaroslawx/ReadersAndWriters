#ifndef READERSANDWRITERS_FIRST_SOLUTION_H
#define READERSANDWRITERS_FIRST_SOLUTION_H

namespace first_solution {
    pthread_mutex_t readerMutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
    pthread_mutex_t writerLock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

    void display_info() {
        string info = "First solution\n"
                      "Description:\n"
                      "    The solution with the possibility of writers starvation.\n";
        cout << info << endl;
    }

    void *reader(void *arg) {

        srand(time(NULL));
        while (true) {
            pthread_mutex_lock(&readerMutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            if (reading == 0) { // If this is first reader entering reading room after writer
                pthread_mutex_lock(&writerLock); // The reader blocks access to the reading room for all writers.
            }
            ++reading; // The reader enters the reading room.
            printStatus();
            pthread_mutex_unlock(&readerMutex); // The reader releases the enter section to other readers.

            usleep(randomTime()); // The reader reads for a random time.

            pthread_mutex_lock(&readerMutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            --reading; // The reader leaves the reading room.

            if (reading == 0) { // If this is last reader leaving reading room
                pthread_mutex_unlock(&writerLock); // The reader releases the reading room for all writers.
            }
            pthread_mutex_unlock(&readerMutex); // The reader releases the enter section to other readers.

            usleep(randomTime()); // The reader stands in the queue.
        }

    }

    void *writer(void *arg) {

        srand(time(NULL));
        while (true) {
            pthread_mutex_lock(&writerLock); // The writer enters the reading room or is detained if there are readers or another writer in it.
            ++writing; // The writer enters the reading room.
            printStatus();

            usleep(randomTime()); // The writer writes for a random time.

            --writing; // The writer leaves the reading room.
            pthread_mutex_unlock(&writerLock); // The writer leaves the reading room.

            usleep(randomTime()); // The writer stands in the queue.
        }

    }

    void run() {
        display_info();

        pthread_mutex_init(&readerMutex, nullptr);
        pthread_mutex_init(&writerLock, nullptr);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

        unsigned int i;
        for (i = 0; i < readers_count; ++i) {
            pthread_create(&readers[i], nullptr, reader, nullptr); // Create readers threads.
        }
        sleep(2); // Wait 2 seconds before creating readers threads to delay the time when they take over the reading room.

        for (i = 0; i < writers_count; ++i) {
            pthread_create(&writers[i], nullptr, writer, nullptr); // Create writers threads.
        }

        for (i = 0; i < readers_count; ++i) {
            pthread_join(readers[i], nullptr); // Wait for readers threads end.
        }
        for (i = 0; i < writers_count; ++i) {
            pthread_join(writers[i], nullptr); // Wait for writers threads end.
        }

    }
}

#endif
