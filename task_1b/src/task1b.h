#include <iostream>
#include <stdexcept>
#include <cstring>

typedef char value_type;

class CircularBuffer {
private:
    value_type* buffer;  // Pointer to the buffer array
    int capacity_;       // Maximum capacity of the buffer
    int size_;           // Current number of elements in the buffer
    int front_;          // Index of the front element
    int back_;           // Index of the back element

public:
    // Default constructor, which creates a buffer with zero size
    CircularBuffer()
        : buffer(nullptr), capacity_(0), size_(0), front_(0), back_(0) {
        std::cout << "Circular buffer was constructed." << std::endl;
    }

    // Destructor
    ~CircularBuffer() {
        delete[] buffer;
        std::cout << "Circular buffer was deleted." << std::endl;
    }

    // Copy constructor
    CircularBuffer(const CircularBuffer& cb)
        : capacity_(cb.capacity_), size_(cb.size_), front_(cb.front_), back_(cb.back_) {
        buffer = new value_type[capacity_];
        memcpy(buffer, cb.buffer, sizeof(value_type) * capacity_);
        std::cout << "Circular buffer was copied." << std::endl;
    }

    // Constructor, which creates a buffer with the given capacity
    explicit CircularBuffer(int capacity)
        : buffer(nullptr), capacity_(capacity), size_(0), front_(0), back_(0) {
        if (capacity < 0) {
            throw std::invalid_argument("Capacity must be non-negative");
        }
        buffer = new value_type[capacity];
        memset(buffer, 0, sizeof(value_type) * capacity_);
    }

    // Constructor, which creates a buffer with the given capacity and fills it with elem
    CircularBuffer(int capacity, const value_type& elem)
        : CircularBuffer(capacity) {
        if (capacity < 0) {
            throw std::invalid_argument("Capacity must be non-negative");
        }
        for (int i = 0; i < capacity_; ++i) {
            buffer[i] = elem;
        }
        size_ = capacity_;
    }

    // Index access with boundaries check
    value_type& operator[](int i) {
        return buffer[(front_ + i) % capacity_];
    }

    const value_type& operator[](int i) const {
        return buffer[(front_ + i) % capacity_];
    }

    // Index access with bounds checking
    value_type& at(int i) {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Invalid index");
        }
        return buffer[(front_ + i) % capacity_];
    }

    const value_type& at(int i) const {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Invalid index");
        }
        return buffer[(front_ + i) % capacity_];
    }

    // Return the first element
    value_type& front() {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[front_];
    }

    const value_type& front() const {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[front_];
    }

    // Return the last element
    value_type& back() {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[(front_ + size_ - 1) % capacity_];
    }

    const value_type& back() const {
        if (empty()) {
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[(front_ + size_ - 1) % capacity_];
    }

    // Linearize buffer
    value_type* linearize() {
        if (front_ == 0) {
            return buffer;
        }
        value_type* new_buffer = new value_type[capacity_];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer[(front_ + i) % capacity_];
        }
        delete[] buffer;
        buffer = new_buffer;
        front_ = 0;
        back_ = size_ - 1;
        return &buffer[front_];
    }

    bool is_linearized() const {
        return (front_ == 0);
    }

    void rotate(int new_begin) {
        if (new_begin < 0 || new_begin >= size_) {
            throw std::out_of_range("Invalid index");
        }
        value_type* new_b = new value_type[capacity_];
        for (int i = 0; i < size_; ++i) {
            new_b[i] = buffer[(front_ + i + new_begin) % capacity_];
        }
        delete[] buffer;
        buffer = new_b;
        front_ = 0;
        back_ = size_ - 1;
    }

    // Size check
    int size() const {
        return size_;
    }

    // Empty check
    bool empty() const {
        return size_ == 0;
    }

    // Full check
    bool full() const {
        return size_ == capacity_;
    }

    int reserve() const {
        return capacity_ - size_;
    }

    int capacity() const {
        return capacity_;
    }

    void set_capacity(int new_capacity) {
        if (new_capacity < 0) {
            throw std::invalid_argument("Capacity must be non-negative");
        }
        value_type* new_buffer = new value_type[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer[(front_ + i) % capacity_];
        }
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
        front_ = 0;
        back_ = size_ - 1;
        if (size_ > new_capacity) {
            size_ = new_capacity;
        }
    }

    void resize(int new_size, const value_type& item = value_type()) {
        if (new_size < 0) {
            throw std::invalid_argument("Size must be non-negative");
        }
        if (new_size > capacity_) {
            throw std::invalid_argument("New size exceeds capacity");
        }
        if (new_size > size_) {
            for (int i = size_; i < new_size; ++i) {
                buffer[(front_ + i) % capacity_] = item;
            }
        }
        size_ = new_size;
        back_ = (front_ + size_ - 1) % capacity_;
    }

    // Assignment operator
    CircularBuffer& operator=(const CircularBuffer& cb) {
        if (this == &cb) return *this;
        delete[] buffer;

        capacity_ = cb.capacity_;
        size_ = cb.size_;
        front_ = cb.front_;
        back_ = cb.back_;
        buffer = new value_type[capacity_];
        memcpy(buffer, cb.buffer, sizeof(value_type) * capacity_);
        return *this;
    }

    // Swap the contents of two circular buffers
    void swap(CircularBuffer& cb) {
        std::swap(buffer, cb.buffer);
        std::swap(capacity_, cb.capacity_);
        std::swap(size_, cb.size_);
        std::swap(front_, cb.front_);
        std::swap(back_, cb.back_);
    }

    // Insert element at the end of the buffer
    void push_back(const value_type& item = value_type()) {
        if (full()) {
            front_ = (front_ + 1) % capacity_;
        } else {
            size_++;
        }
        buffer[back_] = item;
        back_ = (back_ + 1) % capacity_;
    }

    // Delete the last element of the buffer
    void pop_back() {
        if (empty()) throw std::out_of_range("Buffer is empty");
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
    }

    // Insert element at the beginning of the buffer
    void push_front(const value_type& item = value_type()) {
        if (full()) {
            back_ = (back_ - 1 + capacity_) % capacity_;
        } else {
            size_++;
        }
        front_ = (front_ - 1 + capacity_) % capacity_;
        buffer[front_] = item;
    }

    // Delete the first element in the buffer
    void pop_front() {
        if (empty()) throw std::out_of_range("Buffer is empty");
        front_ = (front_ + 1) % capacity_;
        size_--;
    }

    // Insert element item by index pos. Capacity doesn't change
    void insert(int pos, const value_type& item = value_type()) {
        if (pos < 0 || pos > size_) {
            throw std::out_of_range("Invalid index");
        }
        if (full()) {
            throw std::out_of_range("Buffer is full");
        }
        size_++;
        for (int i = size_ - 1; i > pos; --i) {
            buffer[(front_ + i) % capacity_] = buffer[(front_ + i - 1) % capacity_];
        }
        buffer[(front_ + pos) % capacity_] = item;
    }

    // Delete elements in [first, last)
    void erase(int first, int last) {
        if (first < 0 || first >= size_ || last < 0 || last > size_ || first >= last) {
            throw std::out_of_range("Invalid index");
        }
        size_ = size_ - (last - first);
        for (int i = first; i < size_; ++i) {
            buffer[(front_ + i) % capacity_] = buffer[(front_ + i + (last - first)) % capacity_];
        }
        back_ = (front_ + size_ - 1) % capacity_;
    }

    // Clear buffer
    void clear() {
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
};

// Compare buffers
bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
    return !(a == b);
}

