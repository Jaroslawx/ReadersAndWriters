#ifndef READERSANDWRITERS_SECOND_SOLUTION_H
#define READERSANDWRITERS_SECOND_SOLUTION_H

namespace second_solution {
    unsigned int writing_or_waiting = 0; // The number of writers waiting for access to the reading room or writing (max one at the moment).

    pthread_mutex_t reader_mutex; // A binary semaphore that provides access to the input or output section to only one reader at a time.
    pthread_mutex_t writer_mutex; // A binary semaphore that provides access to the input or output section to only one writer at a time.

    pthread_mutex_t reader_lock; // A binary semaphore that blocks access to the reading room for all readers or grants only one at a time.
    pthread_mutex_t writer_lock; // A binary semaphore that blocks access to the reading room for all writers or grants only one at a time.

    void display_info() {
        string info = "Second solution\n"
                      "Description:\n"
                      "    The solution with the possibility of readers starvation.\n";
        cout << info << endl;
    }

    void *reader(void *arg) {
        srand(time(NULL));
        while (true) {
            pthread_mutex_lock(
                    &reader_lock); // The reader waits, when no writer is in the reading room and no writer is waiting for access to the reading room.
            pthread_mutex_lock(
                    &reader_mutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.

            if (reading == 0) { // If this is first reader entering reading room after writer
                pthread_mutex_lock(
                        &writer_lock); // If there is writer in the reading room, the reader stops, other ways blocks other readers access it.
            }
            ++reading;

            print_status();

            pthread_mutex_unlock(&reader_mutex); // The reader releases the enter section to other readers.
            pthread_mutex_unlock(&reader_lock); // The reader enters the reading room.

            usleep(random_time()); // The reader reads.

            pthread_mutex_lock(
                    &reader_mutex); // The reader waits for another reader to release the enter section, or blocks other readers access it.
            --reading;

            if (reading == 0) {
                pthread_mutex_unlock(
                        &writer_lock); // If there is no readers in the reading room, the reader releases the reading room for all writers.
            }
            pthread_mutex_unlock(&reader_mutex); // The reader releases the enter section to other readers.

            usleep(random_time()); // The reader stands in the queue.
        }
    }

    void *writer(void *arg) {
        srand(time(NULL));
        while (true) {
            pthread_mutex_lock(
                    &writer_mutex); // The writer waits for another writer to release the enter section, or blocks other writers access it.
            ++writing_or_waiting;

            if (writing_or_waiting == 1) {
                pthread_mutex_lock(&reader_lock); // Blocks readers access to reading room.
            }
            pthread_mutex_unlock(&writer_mutex); // The writer releases the enter section to other writers.

            pthread_mutex_lock(
                    &writer_lock); // The writer enters the reading room or being blocked by other writer or readers.
            ++writing;
            print_status();

            usleep(random_time()); // The writer writes.

            --writing;
            pthread_mutex_unlock(&writer_lock); // The writer releases the reading room.

            pthread_mutex_lock(
                    &writer_mutex); // The writer waits for another writer to release the enter section, or blocks other writers access it.
            --writing_or_waiting;

            if (writing_or_waiting == 0) {
                pthread_mutex_unlock(
                        &reader_lock); // If there is no writers waiting for access to the reading room or writing, the writer releases the reading room for all readers.
            }
            pthread_mutex_unlock(&writer_mutex); // The writer releases the enter section to other writers.

            usleep(random_time()); // The writer stands in the queue.
        }
    }

    void run() {
        display_info();

        pthread_mutex_init(&reader_mutex, NULL);
        pthread_mutex_init(&writer_mutex, NULL);
        pthread_mutex_init(&reader_lock, NULL);
        pthread_mutex_init(&writer_lock, NULL);

        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

        unsigned int i;
        for (i = 0; i < readers_count; ++i) {
            pthread_create(&readers[i], NULL, reader, NULL); // Create readers threads.
        }
        sleep(2); // Wait 2 seconds before creating readers threads to delay the time when they take over the reading room.

        for (i = 0; i < writers_count; ++i) {
            pthread_create(&writers[i], NULL, writer, NULL); // Create writers threads.
        }

        for (i = 0; i < readers_count; ++i) {
            pthread_join(readers[i], NULL); // Wait for readers threads end.
        }
        for (i = 0; i < writers_count; ++i) {
            pthread_join(writers[i], NULL); // Wait for writers threads end.
        }
    }
}

#endif
