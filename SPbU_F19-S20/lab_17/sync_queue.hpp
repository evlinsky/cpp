#pragma once

#include <cstddef>
#include <optional>

namespace lab_17 {
    /**
     * Exception thrown when queue is shut down.
     * Any operation that was waiting inside the queue or would modify it after shutdown is aborted with this exception.
     */
    class queue_is_shutdown;

    /**
     * Synchronised queue for inter.
     * @tparam T stored type.
     */
    template<typename T>
    class sync_queue {
    public:
        /**
         * Construct queue with given maximum queue size (unlimited by default).
         * @param max_size maximum queue size.
         */
        explicit sync_queue(std::size_t max_size = /* maximum possible value */);
        /**
         * Move construction.
         */
        sync_queue(sync_queue &&) noexcept;
        /**
         * Move assignment.
         */
        sync_queue &operator =(sync_queue &&) noexcept;
        /**
         * Destruction.
         */
        ~sync_queue() noexcept;

        /**
         * Copy construction is forbidden.
         */
        sync_queue(sync_queue const &) = delete;
        /**
         * Copy assignment is forbidden.
         */
        sync_queue &operator =(sync_queue const &) = delete;

        /**
         * Push value into the queue, wait if needed.
         * If queue was already shutdown or is shutdown during waiting, exception is thrown.
         * @param value value to be pushed (todo: references?)
         */
        void push(T /* ??? */ value);
        /**
         * Push value into the queue only if there is space for it.
         * If queue was shutdown, operation is not performed.
         * @param x value to be pushed (todo: references?)
         * @return was operation successful or not.
         */
        bool try_push(T /* ??? */ x);

        /**
         * Pop value from the queue, wait if needed.
         * If queue was already shutdown or is shutdown during waiting, exception is thrown.
         * @return popped value.
         */
        T pop();
        /**
         * Pop value from the queue only if there is one.
         * If queue was shutdown, operation is not performed
         * @return optional popped value.
         */
        std::optional<T> try_pop();

        /**
         * Current size of queue.
         * @return size.
         */
        std::size_t size() const noexcept;

        /**
         * Shutdown queue.
         * After queue is shutdown, nothing can be pushed or popped,
         * and all waiting operations are aborted.
         */
        void shutdown();
        /**
         * Check if queue is shutdown.
         * @return is queue shutdown.
         */
        bool is_shutdown() const noexcept;

    private:
        /*
         * Implementation is left out.
         */
    };
}
