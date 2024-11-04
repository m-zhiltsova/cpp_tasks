#include <iostream>
#include <stdexcept>
#include <cstring>

typedef char value_type;

class CircularBuffer {
private:
    value_type* buffer;
    int capacity_;
    int size_;
    int front_;
    int back_;

public:
    //Default constructor, which creates a buffer with zero size
    CircularBuffer() 
        : buffer(nullptr), capacity_(0), size_(0), front_(0), back_(0) {
        std::cout << "Circular buffer was constructed." << std::endl; 
    }

    // Deconstructor
    ~CircularBuffer() {
        delete[] buffer;
        std::cout << "Circular buffer was deleted." << std::endl;
    }
    
    // Copy constructor
    CircularBuffer(const CircularBuffer& cb) 
        : capacity_(cb.capacity_), size_(cb.size_), front_(cb.front_), back_(cb.back_) {
        buffer = new value_type[capacity_];
        memcpy(buffer, cb.buffer, sizeof(value_type) * capacity_);
        std::cout << "Cicular buffer was copied." << std::endl;
    }

    // Conctrucor, which creates buffer with given capacity
    explicit CircularBuffer(int capacity) 
        : buffer(new value_type[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {
        memset(buffer, 0, sizeof(value_type) * capacity_);
    }

    // Conctrucor, which creates buffer with given capacity and fulls it with elem
    CircularBuffer(int capacity, const value_type& elem) 
        : CircularBuffer(capacity) {
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

    // Index access
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
        return buffer[front_];
    };

    // Return the last element
    value_type& back() {
        return buffer[back_];
    };
    const value_type & front() const {
        return buffer[front_];
    };
    const value_type & back() const {
        return buffer[back_];
    };


    // Linearize buffer
    value_type* linearize() {
        if (front_ == 0) {
            return buffer;
        }
        value_type * new_buffer = new value_type[capacity_];
        for (int i = 0; i < size_; ++i) 
        {
            new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        front_ = 0;
        back_ = size_-1;
        return &buffer[front_];
    }

    bool is_linearized() const {
        return (front_ == 0);
    };

    void rotate(int new_begin) {
        value_type * new_b = new value_type[capacity_];
        for (int i = 0; i < size_; ++i) {
            new_b[i] = buffer[(i+new_begin)%size_];
        }
        delete[] buffer;
        buffer = new_b;
        back_ = size_-1; 
    };

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
        return capacity_-size_;
    }
    int capacity() const {
        return capacity_;
    };

    void set_capacity(int new_capacity) {
        capacity_ = new_capacity;
        if (back_ >= capacity_) {
            back_ = capacity_;
        }
        if (front_ >= capacity_) {
            front_ = 0;
        }
    }
    void resize(int new_size, const value_type & item = value_type()) {
        size_ = new_size;
        for (int i = 0; i < size_; ++i) {
            buffer[i] = item;
        }
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

    void swap(CircularBuffer & cb);

   // Insert element in the ending of buffer
    void push_back(const value_type& item = value_type()) {
        if (full())
            front_ = (front_ + 1) % capacity_;
        else
            size_++;
        buffer[back_] = item;
        back_ = (back_ + 1) % capacity_;
    }

    // Delete the last element of buffer
    void pop_back() {
        if (empty()) throw std::out_of_range("Buffer is empty");
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
    }

    // Insert element in the beginning of buffer
    void push_front(const value_type& item = value_type()) {
        if (full())
            back_ = (back_ - 1 + capacity_) % capacity_;
        else
            size_++;
        front_ = (front_ - 1 + capacity_) % capacity_;
        buffer[front_] = item;
    }

    // Delete the first element in buffer.
    void pop_front() {
        if (empty()) throw std::out_of_range("Buffer is empty");
        front_ = (front_ + 1) % capacity_;
        size_--;
    }

    // Insert element item by index pos. Capasity doesn't change
    void insert(int pos, const value_type & item = value_type()) {
        if (pos < 0 || pos > size_) {
           throw std::out_of_range("Invalid index"); 
        }
        if (full()) {
            rotate(1);
        }
        else {
            size_++;
        }
        for (int i = size_ - 1; i > pos; --i) {
            buffer[i] = buffer[i-1];
        }
        buffer[pos] = item;
    };

    // Delete elements in [first, last).
    void erase(int first, int last) {
        if (first < 0 || first >= size_) {
           throw std::out_of_range("Invalid index"); 
        }
        if (first < 0 || first >= size_) {
           throw std::out_of_range("Invalid index"); 
        }
        size_ = size_ - (last - first);
        for (int i = first; i < size_; ++i) {
            buffer[i] = buffer[i+(last-first)];
        }
        back_ = size_-1;
    };

    // Clear buffer
    void clear() {
        size_ = 0;
        front_ = 0;
    };
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
