#ifndef READERSANDWRITERS_THIRD_SOLUTION_H
#define READERSANDWRITERS_THIRD_SOLUTION_H

namespace third_solution {

    unsigned int waiting_readers = 0; // The number of readers waiting in the queue to the reading room.
    unsigned int waiting_writers = 0; // The number of writers waiting in the queue to the reading room.

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
        pthread_mutex_lock(&mutex); // The reader occupies the mutex or waits for it to be released.

        if (waiting_writers > 0 || writing > 0) { // If any writer waits or writes.
            ++waiting_readers;
            pthread_cond_wait(&can_read, &mutex); // The reader releases the mutex and starts waiting until can read.
            // The reader stops waiting and occupies the mutex again.
        } else { // If there is no writer waiting or writing.
            ++reading;
            rr_statement(0);
            print_status()
        }
        pthread_mutex_unlock(&mutex); // The reader releases mutex.
    }

    void stop_reading() {
        pthread_mutex_lock(&mutex); // The reader occupies the mutex or waits for it to be released.

        --reading;
        rr_statement(1);
        print_status();

        if (reading == 0) { // If no reader reads.
            pthread_cond_signal(&can_write); // Awake one writer or do nothing if no writer waits.
        }
        pthread_mutex_unlock(&mutex); // The reader releases mutex.
    }

    void start_writing() {
        pthread_mutex_lock(&mutex); // The writer occupies the mutex or waits for it to be released.

        if (reading > 0 || writing > 0) { // If any reader reads or writer writes.
            ++waiting_writers;
            pthread_cond_wait(&can_write, &mutex); // The writer releases the mutex and starts waiting until can write.
            // The writer stops waiting and occupies the mutex again.
            --waiting_writers;
        }
        writing = 1;
        rr_statement(2);
        print_status();
        pthread_mutex_unlock(&mutex); // The writer releases mutex.
    }

    void stop_writing() {
        pthread_mutex_lock(&mutex); // The writer occupies the mutex or waits for it to be released.
        writing = 0;

        if (waiting_writers == 0) { // If no writer waits.
            pthread_cond_signal(&can_write); // Awake one writer if any writer waits.
        } else { // If any reader waits.
            pthread_cond_broadcast(&can_read); // Awake all readers waiting in the queue.
            reading += waiting_readers; // Add all readers from the queue to the reading room.
            waiting_readers = 0; // Clear the queue.
            rr_statement(3);
            print_status()
        }
        pthread_mutex_unlock(&mutex); // The writer releases mutex.
    }

    void *reader(void *arg) {
        srand(time(NULL));
        while (true) {
            start_reading(); // Reader waits or start reading.
            usleep(randomNumber()); // Reader reads.
            stop_reading(); // Reader stops reading.
            usleep(randomNumber()); // Reader lines up in the queue.
        }
    }

    void *writer(void *arg) {
        srand(time(NULL));
        while (true) {
            start_writing(); // Writer waits or start writing.
            usleep(randomNumber()); // Writer writes.
            stop_writing(); // Writer stops writing.
            usleep(randomNumber()); // Writer lines up in the queue.
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
