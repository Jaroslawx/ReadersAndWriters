#ifndef READERSANDWRITERS_FIRST_SOLUTION_H
#define READERSANDWRITERS_FIRST_SOLUTION_H

namespace first_solution {
    pthread_mutex_t reader_mutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
    pthread_mutex_t writer_lock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

    void display_info() {
        string info = "First solution\n"
                      "Description:\n"
                      "    The solution with the possibility of writers starvation.\n";
        cout << info << endl;
    }

    void *reader(void *arg) {

        while (true) {
            pthread_mutex_lock(
                    &reader_mutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            if (reading == 0) { // If this is first reader entering reading room after writer
                pthread_mutex_lock(&writer_lock); // The reader blocks access to the reading room for all writers.
            }
            ++reading; // The reader enters the reading room.
            print_status();
            pthread_mutex_unlock(&reader_mutex); // The reader releases the enter section to other readers.

            usleep(randomNumber()); // The reader reads for a random time.

            pthread_mutex_lock(&reader_mutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            --reading; // The reader leaves the reading room.

            if (reading == 0) { // If this is last reader leaving reading room
                pthread_mutex_unlock(&writer_lock); // The reader releases the reading room for all writers.
            }
            pthread_mutex_unlock(&reader_mutex); // The reader releases the enter section to other readers.

            usleep(randomNumber()); // The reader stands in the queue.
        }

    }

    void *writer(void *arg) {

        while (true) {
            pthread_mutex_lock(
                    &writer_lock); // The writer enters the reading room or is detained if there are readers or another writer in it.
            ++writing; // The writer enters the reading room.
            print_status();

            usleep(randomNumber()); // The writer writes for a random time.

            --writing; // The writer leaves the reading room.
            pthread_mutex_unlock(&writer_lock); // The writer leaves the reading room.

            usleep(randomNumber()); // The writer stands in the queue.
        }

    }

    void run() {
        display_info();

        pthread_mutex_init(&reader_mutex, nullptr);
        pthread_mutex_init(&writer_lock, nullptr);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

        for (int i = 0; i < readers_count; ++i) {
            pthread_create(&readers[i], nullptr, reader, nullptr); // Create readers threads.
        }
        sleep(2); // Wait 2 seconds before creating readers threads to delay the time when they take over the reading room.

        for (int i = 0; i < writers_count; ++i) {
            pthread_create(&writers[i], nullptr, writer, nullptr); // Create writers threads.
        }

        for (int i = 0; i < readers_count; ++i) {
            pthread_join(readers[i], nullptr); // Wait for readers threads end.
        }
        for (int i = 0; i < writers_count; ++i) {
            pthread_join(writers[i], nullptr); // Wait for writers threads end.
        }

    }
}

#endif
