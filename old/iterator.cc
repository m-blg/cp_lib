// iterator
template <typename T>
struct Iterator {
    T* ptr;

    T* operator->();    
    auto& operator*();
    void operator++();
    void operator++(int);
    void operator--();
    void operator--(int);
    Iterator operator+(u32 step);
    Iterator operator-(u32 step);
    void operator+=(u32 step);
    void operator-=(u32 step);
    bool operator!=(const Iterator& other);
    bool operator==(const Iterator& other);

};

template <typename T>
T* Iterator<T>::operator->() {
    return this->ptr;
}
template <typename T>
auto& Iterator<T>::operator*() {
    return *this->ptr;
}

template <typename T>
void Iterator<T>::operator++() {
    next(this);
}
template <typename T>
void Iterator<T>::operator++(int) {
    next(this);
}
template <typename T>
void Iterator<T>::operator--() {
    prev(this);
}
template <typename T>
void Iterator<T>::operator--(int) {
    prev(this);
}

template <typename T>
Iterator<T> Iterator<T>::operator+(u32 step) {
    Iterator<T> it = *this;
    next(&it, step);
    return it;
}
template <typename T>
Iterator<T> Iterator<T>::operator-(u32 step) {
    Iterator<T> it = *this;
    prev(&it, step);
    return it; 
}

template <typename T>
void Iterator<T>::operator+=(u32 step) {
    next(this, step);
}
template <typename T>
void Iterator<T>::operator-=(u32 step) {
    prev(this, step);
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
    return this->ptr != other.ptr;
}
template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) {
    return this->ptr == other.ptr;
}



// iterator
template <typename t_iter>
void operator++(t_iter& it) {
    next(&it);
}
template <typename t_iter>
void operator++(t_iter& it, int) {
    next(&it);
}
template <typename t_iter>
void operator--(t_iter& it) {
    prev(&it);
}
template <typename t_iter>
void operator--(t_iter& it, int) {
    prev(&it);
}

template <typename t_iter>
t_iter operator+(t_iter it, u32 step) {
    next(&it, step);
    return it;
}
template <typename t_iter>
t_iter operator-(t_iter it, u32 step) {
    prev(&it, step);
    return it; 
}

template <typename t_iter>
void operator+=(t_iter& it, u32 step) {
    next(&it, step);
}
template <typename t_iter>
void operator-=(t_iter& it, u32 step) {
    prev(&it, step);
}

template <typename t_iter>
bool operator!=(const t_iter& f, const t_iter& s) {
    return f.ptr != s.ptr;
}
template <typename t_iter>
bool operator==(const t_iter& f, const t_iter& s) {
    return f.ptr == s.ptr;
}