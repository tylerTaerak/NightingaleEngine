#pragma once

#include <cstddef>
#include <mutex>

namespace Nightingale::Utils {
    template<typename T>
        class RwLock;

    /**
     * @class ReadLockGuard
     *
     * This class is returned by
     * a RwLock when something wants to read the value held in the lock.
     *
     * This is an RAII method of safely
     * keeping track of readers and writers
     * of a RwLock.
     */
    template<typename T>
        class ReadLockGuard {
            public:
                /**
                 * @brief ctor
                 *
                 * @param RwLock<T> &lock - lock that this lockguard came from
                 * @param T &data - data held in the lock, now available for reading
                 */
                ReadLockGuard(RwLock<T> &lock, T *data);

                /**
                 * @brief dtor
                 */
                ~ReadLockGuard();

                ReadLockGuard(const ReadLockGuard&) = delete;

                /**
                 * @brief get_data
                 *
                 * @returns T& - reference to the data held by the RwLock, now available
                 * for reading
                 */
                T *get_data() const;
            private:
                RwLock<T> &m_lock;
                T *m_data;
        };

    /**
     * @class WriteLockGuard
     *
     * This class is returned by
     * a RwLock when something wants
     * to modify the data held in the lock.
     *
     * This is an RAII method of safely
     * keeping track of readers and writers
     * of a RwLock.
     */
    template<typename T>
        class WriteLockGuard {
            public:
                /**
                 * @brief ctor
                 *
                 * @param RwLock<T> &lock - lock that this lockguard came from
                 * @param T &data - data held in the lock, now available for writing
                 */
                WriteLockGuard(RwLock<T> &lock, T *data);

                /**
                 * @brief dtor
                 */
                ~WriteLockGuard();

                WriteLockGuard(const WriteLockGuard&) = delete;

                /**
                 * @brief get_data
                 *
                 * @returns T& - reference to the data held by the RwLock, now available
                 * for writing
                 */
                T *get_data();
            private:
                RwLock<T> &m_lock;
                T *m_data;
        };

    /**
     * @class RwLock
     *
     * This class holds data in a threadsafe manner.
     * It allows for multiple readers to access its data
     * simultaneously, but requires locking out everything
     * when something writes to the data. It uses a pair
     * of mutexes and a reader count to handle this.
     */
    template<typename T>
        class RwLock {
            public:
                /**
                 * @brief ctor
                 *
                 * creates a heap-allocated object of the desired type
                 */
                RwLock()
                    : m_data(new T) {}
                /**
                 * @brief ctor
                 *
                 * @param T &data - data held threadsafe by this lock
                 */
                RwLock(T *data)
                    : m_data(data) {}

                /**
                 * @brief dtor
                 *
                 * deallocates the heap memory of the contained data
                 */
                ~RwLock() {
                    delete m_data;
                }

                /**
                 * @brief read
                 *
                 * @returns ReadLockGuard<T> - read lockguard holding the data avaiable for reading
                 */
                ReadLockGuard<T> read();

                /**
                 * @brief write
                 *
                 * @returns WriteLockGuard<T> - write lockguard holding the data available for writing
                 */
                WriteLockGuard<T> write();

                template<typename C> friend class ReadLockGuard;
                template<typename C> friend class WriteLockGuard;
            private:
                RwLock(const RwLock &other) = delete;
                RwLock(RwLock &&other) = delete;
                RwLock &operator = (RwLock &&other) = delete;
                RwLock &operator = (const RwLock &other) = delete;

                std::mutex m_readMutex;
                size_t m_readerCount;
                std::mutex m_writeMutex;

                T *m_data;
        };

    template<typename T>
        ReadLockGuard<T> RwLock<T>::read() {
            return ReadLockGuard<T>(*this, m_data);
        }

    template<typename T>
        WriteLockGuard<T> RwLock<T>::write() {
            return WriteLockGuard<T>(*this, m_data);
        }

    template<typename T>
        ReadLockGuard<T>::ReadLockGuard(RwLock<T> &lock, T *data)
        : m_lock(lock), m_data(data) {
            m_lock.m_readMutex.lock();
            if (++m_lock.m_readerCount == 1) {
                m_lock.m_writeMutex.lock();
            }
            m_lock.m_readMutex.unlock();
        }

    template<typename T>
        ReadLockGuard<T>::~ReadLockGuard() {
            m_lock.m_readMutex.lock();
            if (--m_lock.m_readerCount == 0) {
                m_lock.m_writeMutex.unlock();
            }
            m_lock.m_readMutex.unlock();
        }

    template<typename T>
        T *ReadLockGuard<T>::get_data() const {
            return m_data;
        }

    template<typename T>
        WriteLockGuard<T>::WriteLockGuard(RwLock<T> &lock, T *data) 
        : m_lock(lock), m_data(data) {
            m_lock.m_writeMutex.lock();
        }

    template<typename T>
        WriteLockGuard<T>::~WriteLockGuard() {
            m_lock.m_writeMutex.unlock();
        }

    template <typename T>
        T *WriteLockGuard<T>::get_data() {
            return m_data;
        }
}
