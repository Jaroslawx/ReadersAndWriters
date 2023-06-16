#ifndef READERSANDWRITERS_THIRD_SOLUTION_H
#define READERSANDWRITERS_THIRD_SOLUTION_H

namespace third_solution {
    std::atomic<unsigned int> waiting_readers(0); // The number of readers waiting in the queue to the reading room.
    std::atomic<unsigned int> waiting_writers(0); // The number of writers waiting in the queue to the reading room.

    pthread_mutex_t mutex; // A binary semaphore that allows only one thread to access variables through a monitor procedure at a time.
    pthread_cond_t can_read; // A conditional variable that readers wait on until they can read
    pthread_cond_t can_write; // A condition variable that writers wait on until they can write.

    void display_info() {
        string info = "Third solution\n"
                      "Description:\n"
                      "    The solution excluding starvation.\n";
        cout << info << endl;
    }

    void start_reading() {
        pthread_mutex_lock(&mutex);

        if (waiting_writers > 0 || writing > 0) {
            ++waiting_readers;
            pthread_cond_wait(&can_read, &mutex);
        } else {
            ++reading;
            int readTime = portable::randomNumber();
            portable::rr_statement(portable::Action::READER_ENTER, readTime);
            portable::print_status();
        }

        pthread_mutex_unlock(&mutex);
    }

    void stop_reading() {
        pthread_mutex_lock(&mutex);

        --reading;
        portable::rr_statement(portable::Action::READER_LEFT);
        portable::print_status();

        if (reading == 0) {
            pthread_cond_signal(&can_write);
        }

        pthread_mutex_unlock(&mutex);
    }

    void start_writing() {
        pthread_mutex_lock(&mutex);

        if (reading > 0 || writing > 0) {
            ++waiting_writers;
            pthread_cond_wait(&can_write, &mutex);
            --waiting_writers;
        }

        writing = 1;
        int writeTime = portable::randomNumber();
        portable::rr_statement(portable::Action::WRITER_ENTER, writeTime);
        portable::print_status();

        pthread_mutex_unlock(&mutex);
    }

    void stop_writing() {
        pthread_mutex_lock(&mutex);

        writing = 0;

        if (waiting_writers == 0) {
            pthread_cond_signal(&can_write);
        } else {
            pthread_cond_broadcast(&can_read);
            reading += waiting_readers;
            waiting_readers = 0;
            portable::rr_statement(portable::Action::WRITER_LEFT);
            portable::print_status();
        }

        pthread_mutex_unlock(&mutex);
    }

    void *reader(void *arg) {
        while (true) {
            start_reading();
            sleep(portable::randomNumber());
            stop_reading();
            sleep(portable::randomNumber());
        }
    }

    void *writer(void *arg) {
        while (true) {
            start_writing();
            sleep(portable::randomNumber());
            stop_writing();
            sleep(portable::randomNumber());
        }
    }

    void run() {
        display_info();

        pthread_mutex_init(&mutex, NULL); // Initialize semaphore.

        // Initialize conditional variable.
        pthread_cond_init(&can_read, NULL);
        pthread_cond_init(&can_write, NULL);
        pthread_t readers[readers_count];
        pthread_t writers[writers_count];

        unsigned int i;
        for (i = 0; i < writers_count; ++i) { // Create writers threads.
            pthread_create(&writers[i], NULL, writer, NULL);
        }
        for (i = 0; i < readers_count; ++i) { // Create readers threads.
            pthread_create(&readers[i], NULL, reader, NULL);
        }
        for (i = 0; i < writers_count; ++i) { // Wait for writers threads to end.
            pthread_join(writers[i], NULL);
        }
        for (i = 0; i < readers_count; ++i) { // Wait for readers threads to end.
            pthread_join(readers[i], NULL);
        }

    }
}

#endif
