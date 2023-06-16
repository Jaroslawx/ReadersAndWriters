#ifndef READERSANDWRITERS_SECOND_SOLUTION_H
#define READERSANDWRITERS_SECOND_SOLUTION_H

namespace second_solution {
    std::atomic<unsigned int> writing_or_waiting(0); // The number of writers waiting for access to the reading room or writing (max one at the moment).

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
        while (true) {
            pthread_mutex_lock(&reader_lock);
            pthread_mutex_lock(&reader_mutex);

            if (reading == 0) {
                pthread_mutex_lock(&writer_lock);
            }
            ++reading;
            int readTime = portable::randomNumber();
            rr_statement(portable::Action::READER_ENTER, readTime);
            portable::print_status();

            pthread_mutex_unlock(&reader_mutex);
            pthread_mutex_unlock(&reader_lock);

            sleep(readTime);

            pthread_mutex_lock(&reader_mutex);
            --reading;
            rr_statement(portable::Action::READER_LEFT);
            portable::print_status();

            if (reading == 0) {
                pthread_mutex_unlock(&writer_lock);
            }
            pthread_mutex_unlock(&reader_mutex);

            sleep(portable::randomNumber());
        }
    }

    void *writer(void *arg) {
        while (true) {
            pthread_mutex_lock(&writer_mutex);
            ++writing_or_waiting;

            if (writing_or_waiting == 1) {
                pthread_mutex_lock(&reader_lock);
            }
            pthread_mutex_unlock(&writer_mutex);

            pthread_mutex_lock(&writer_lock);
            ++writing;
            int writeTime = portable::randomNumber();
            rr_statement(portable::Action::WRITER_ENTER, writeTime);
            portable::print_status();

            sleep(writeTime);

            --writing;
            rr_statement(portable::Action::WRITER_LEFT);
            portable::print_status();

            pthread_mutex_unlock(&writer_lock);

            pthread_mutex_lock(&writer_mutex);
            --writing_or_waiting;

            if (writing_or_waiting == 0) {
                pthread_mutex_unlock(&reader_lock);
            }
            pthread_mutex_unlock(&writer_mutex);

            sleep(portable::randomNumber());
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
