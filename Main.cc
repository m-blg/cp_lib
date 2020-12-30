
using u8 unsigned int;
using u16 unsigned int;
using u32 unsigned int;
using u64 unsigned int;

using i32 signed int;

template <typename T, u32 t_count>
struct SBuffer {
    T r_buffer[t_count];

    inline T Size() {
        return t_count;
    }
};

template <typename T, u32 t_count>
struct SArray {
    T r_buffer[t_count];
    u32 r_len = 0;

    T Size() {
        return t_count;
    }

    void Push(T& item) {
        r_buffer[r_len] = item;
        r_len++;
    }

    T Pop() {
        r_len--;
        return r_buffer[r_len];
    }

    void Add(T& item, u32 index) {
        T* p_target = r_buffer + index;
        for (T* p = r_buffer + r_len; p > p_target; p--) {
            *p = *(p - 1);
        }
       *p_target = item;
       r_len++;
    }

    void Remove(u32 index) {
        r_len--;
        T* p_end = r_buffer + r_len;
        for (T* p = r_buffer + index; p < p_end; p++) {
            *p = *(p + 1);
        }
    }

    T& operator[](u32 index) {
        return r_buffer[index];
    }
};

// SArray<i32, 5> arr;

template <typename T, u32 t_count>
struct SArray {
    T r_buffer[t_count];
    u32 r_len = 0;

    T Size() {
        return t_count;
    }
}

namespace SArray {
    void Push(SArray a, T& item) {
        r_buffer[r_len] = item;
        r_len++;
    }

    T Pop() {
        r_len--;
        return r_buffer[r_len];
    }

    void Add(T& item, u32 index) {
        T* p_target = r_buffer + index;
        for (T* p = r_buffer + r_len; p > p_target; p--) {
            *p = *(p - 1);
        }
       *p_target = item;
       r_len++;
    }

    void Remove(u32 index) {
        r_len--;
        T* p_end = r_buffer + r_len;
        for (T* p = r_buffer + index; p < p_end; p++) {
            *p = *(p + 1);
        }
    }
}
