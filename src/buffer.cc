

#pragma once

#include "mbgldef.h"
#include "memory.cc"
#include "basic.cc"
#include <string.h>
#include <cassert>


namespace cp {

template <typename T>
void resize(T* *buffer, u32 *cap, u32 new_cap) {
    *buffer = m_ralloc(*buffer, new_cap);
    *cap = new_cap;
}

template <typename T>
void scan(T* buffer, u32 len, const char* item_fmt) {
    T* p = buffer;
    T* ep = buffer + len;
    for (; p < ep; p++) {
        scanf(item_fmt, p);
    }
}

template <typename T>
void print_fmt(T* buffer, u32 len, const char* item_fmt) {
    T* endp = buffer + len;
    for (T* p = buffer; p < endp; p++) {
        printf(item_fmt, *p);
    }
}

template <typename T>
void print(T* buffer, u32 len) {
    T* endp = buffer + len;
    T* p = buffer;
    for (; p < endp - 1; p++) {
        print(*p); printf(" ");
    }
    print(*p);
}

template <typename t_first>
void cpy_values(void* buffer, t_first first_arg) {
    *(t_first*)buffer = first_arg;
}

template <typename t_first, typename... Args>
void cpy_values(void* buffer, t_first first_arg, Args... args) {
    *(t_first*)buffer = first_arg;
    cpy_values((u8*)buffer + sizeof(t_first), args...);
}

template<typename T, typename... Args>
struct Memory_Layout {};


template <u32 index, typename t_first>
constexpr auto& get_value(Memory_Layout<t_first> *buffer) {
    if constexpr(index != 0) {
        assert(("Index out of bounds", false));
    }
    return *(t_first*)buffer;
}

template <u32 index, typename t_first, typename... Args>
constexpr auto& get_value(Memory_Layout<t_first, Args...> *buffer) {
    if constexpr(index == 0) {
        return *(t_first*)buffer;
    } else 
        return get_value<index-1>((Memory_Layout<Args...>*)(u8*)buffer + sizeof(t_first));
}

template <typename T, typename... Ts>
struct Tuple {
    T first;
    Tuple<Ts...> next;

    template <u32 index>
    constexpr auto& get() {
        return get_value<index>((Memory_Layout<T, Ts...>*)this);
    }
};

template <typename T>
struct Tuple<T> {
    T first;
};


template <typename T>
struct Buffer_Iterator {
    T* ptr;

    T* operator->();
    operator bool();

    typedef T type;
};

template <typename T>
using buff_iter = Buffer_Iterator<T>;

template <typename T>
void next(buff_iter<T> *it, u32 step=1) {
    it->ptr += step;
}
template <typename T>
void prev(buff_iter<T> *it, u32 step=1) {
    it->ptr -= step;
}

template <typename T>
T* Buffer_Iterator<T>::operator->() {return this->ptr;}
template <typename T>
Buffer_Iterator<T>::operator bool() {return (this->ptr != null);}
template <typename T>
T& operator*(const buff_iter<T>& it) {return *it.ptr;}
template <typename T>
void operator++(buff_iter<T>& it) {next(&it);}
template <typename T>
void operator++(buff_iter<T>& it, int) {next(&it);}
template <typename T>
void operator--(buff_iter<T>& it) {prev(&it);}
template <typename T>
void operator--(buff_iter<T>& it, int) {prev(&it);}
template <typename T>
buff_iter<T> operator+(buff_iter<T> it, u32 step) {next(&it, step); return it;}
template <typename T>
buff_iter<T> operator-(buff_iter<T> it, u32 step) {prev(&it, step); return it;}
template <typename T>
void operator+=(buff_iter<T>& it, u32 step) {next(&it, step);}
template <typename T>
void operator-=(buff_iter<T>& it, u32 step) {prev(&it, step);}
template <typename T>
bool operator!=(const buff_iter<T>& f, const buff_iter<T>& s) {return f.ptr != s.ptr;}
template <typename T>
bool operator==(const buff_iter<T>& f, const buff_iter<T>& s) {return f.ptr == s.ptr;}


template <typename t_buff> 
auto sum(t_buff buffer){
    typename t_buff::type total = {};
    for (auto it = begin(&buffer); it != end(&buffer); it++) {
        total += *it;
    }
    return total;
}

// generic stuff

template <typename T, template <typename> class t_buff>
inline u32 cap(t_buff<T> buffer) { return buffer->cap; }
template <typename T, template <typename> class t_buff>
inline u32 len(t_buff<T> buffer) { return buffer->cap; }
template <typename T, template <typename> class t_buff>
inline u32 size(t_buff<T> buffer) { return sizeof(T) * buffer->cap; }
template <typename T, template <typename> class t_buff>
inline T* beginp(t_buff<T> buffer) { return buffer->buffer; }
template <typename T, template <typename> class t_buff>
inline T* endp(t_buff<T> buffer) { return buffer->buffer + buffer->cap; }

template <class t1, class t2>
void copy(t1 dst_buff, t2 src_buff) { 
    assert(cap(dst_buff) >= cap(src_buff));
    memcpy(beginp(dst_buff), beginp(src_buff), sizeof(typename t2::type) * cap(src_buff));
}
template <typename T, template<typename> class t_buff>
buff_iter<T> begin(t_buff<T> *self) {
    return {beginp(*self)};
}
template <typename T, template<typename> class t_buff>
buff_iter<T> end(t_buff<T> *self) {
    return {beginp(self) + cap(self)};
}

template <class T, class iterable_t>
bool is_elem(T item, iterable_t list) {
    for (auto it = begin(list); it != end(list); it++) {
        if (item == *it)
            return true;
    }
    return false;
}

template <class list_t>
bool is_empty(list_t list) {
    return (len(list) == 0);
}

template <class func_t, class t1_t>
void apply(func_t f, t1_t list) {
    for (auto it = begin(list); it != end(list); it++) {
        f(it.ptr);
    }
}

template <class func_t, class t1, class t2>
t1 foldl(func_t f, t1 acc, t2 list) {
    for (auto it = begin(list); it != end(list); it++) {
        acc = f(acc, &*it);
    }
    return acc;
}

template <class func_t, class t1, class t2>
t1 foldr(func_t f, t1 acc, t2 list) {
    if (len(list) == 0)
        return acc;
    return f(&head(list), foldr(f, acc, tail(list)));
}




// Static Buffer

// wrapper arround T[t_cap], t_cap - buffer capa in items
template <typename T, u32 t_cap>
struct Static_Buffer {
    T buffer[t_cap];

    T& operator[](u32 index) {
        assert(("Index out of range", index < t_cap));
        return buffer[index];
    }

    typedef T type;
    typedef buff_iter<T> iter;
};

template <typename T, u32 t_cap>
using sbuff = Static_Buffer<T, t_cap>;

template <u32 t_cap>
using sbuffu = Static_Buffer<u32, t_cap>;
template <u32 t_cap>
using sbuffi = Static_Buffer<i32, t_cap>;
template <u32 t_cap>
using sbufff = Static_Buffer<f32, t_cap>;
template <u32 t_cap>
using sbuffd = Static_Buffer<f64, t_cap>;
template <u32 t_cap>
using sbuffb = Static_Buffer<bool, t_cap>;

template <typename T, u32 t_cap>
inline u32 cap(sbuff<T, t_cap> &self) { return t_cap; }
template <typename T, u32 t_cap>
inline u32 len(sbuff<T, t_cap> &self) { return t_cap; }
template <typename T, u32 t_cap>
inline u32 size(sbuff<T, t_cap> &self) { return sizeof(T) * t_cap; }
template <typename T, u32 t_cap>
inline T* beginp(sbuff<T, t_cap> &self) { return self.buffer; }
template <typename T, u32 t_cap>
inline T* endp(sbuff<T, t_cap> &self) { return self.buffer + t_cap; }
template <typename T, u32 t_cap>
inline buff_iter<T> begin(sbuff<T, t_cap> &self) { return {self.buffer}; }
template <typename T, u32 t_cap>
inline buff_iter<T> end(sbuff<T, t_cap> &self) { return {self.buffer + t_cap}; }
template <typename T, u32 t_cap>
inline T& head(sbuff<T, t_cap> &self) {
    assert(cap(self) > 0);
    return *self.buffer;
}
template <typename T, u32 t_cap>
inline sbuff<T, t_cap-1> tail(sbuff<T, t_cap> &self) {
    assert(cap(self) > 0);
    return {self.buffer + 1};
}

template <typename T, u32 t_cap>
void clear(sbuff<T, t_cap> *self, i32 value=0) {
    memset(self->buffer, value, t_cap);
}

template <typename T, u32 t_cap>
void print_fmt(Static_Buffer<T, t_cap> self, const char* item_fmt) {
    print(self->buffer, t_cap, item_fmt);
}

template <typename... Ts>
struct Arg_Count {
    constexpr static u32 count();
};

template <typename T, typename... Ts>
struct Arg_Count<T, Ts...> {
    constexpr static u32 count() {
        return Arg_Count<Ts...>::count() + 1;
    }
};

template <typename T>
struct Arg_Count<T> {
    constexpr static u32 count() {
        return 1;
    }
};

template <typename T, typename... Ts>
auto pack(T first, Ts... rest) {
    return sbuff<T, Arg_Count<T, Ts...>::count()> {first, rest...};
}


// Dynamic Buffer

template <typename T>
struct Dynamic_Buffer {
    T* buffer;
    u32 cap; // in items

    T& operator[](u32 index) {
        assert(("Index out of range", index < cap));
        return buffer[index];
    }

    typedef T type;
    typedef buff_iter<T> iter;
};

template <typename T>
using dbuff = Dynamic_Buffer<T>;

using dbuffu = Dynamic_Buffer<u32>;
using dbuffi = Dynamic_Buffer<i32>;
using dbufff = Dynamic_Buffer<f32>;
using dbuffd = Dynamic_Buffer<f64>;
using dbuffb = Dynamic_Buffer<bool>;



template <typename T>
void init(dbuff<T> *self, u32 init_cap) { 
    self->buffer = m_alloc<T>(init_cap); 
    self->cap = init_cap; 
}
template <typename T>
void shut(dbuff<T> *self) { 
    free(self->buffer); 
    *self = {}; 
}


template <typename T>
inline u32 cap(dbuff<T> self) { return self.cap; }
template <typename T>
inline u32 len(dbuff<T> self) { return self.cap; }
template <typename T>
inline u32 size(dbuff<T> self) { return sizeof(T) * self.cap; }
template <typename T>
inline T* beginp(dbuff<T> self) { return self.buffer; }
template <typename T>
inline T* endp(dbuff<T> self) { return self.buffer + self.cap; }
template <typename T>
inline buff_iter<T> begin(dbuff<T> self) { return {self.buffer}; }
template <typename T>
inline buff_iter<T> end(dbuff<T> self) { return {self.buffer + self.cap}; }

template <typename T>
inline T& head(dbuff<T> self) {
    assert(cap(self) > 0);
    return *self.buffer;
}
template <typename T>
inline dbuff<T> tail(dbuff<T> self) {
    assert(cap(self) > 0);
    return {self.buffer + 1, self.cap - 1};
}
template <typename T>
inline dbuff<T> take(u32 count, dbuff<T> self) {
    return {self.buffer, min(count, cap(self))};
}
template <typename T>
inline dbuff<T> drop(u32 count, dbuff<T> self) {
    u32 shift = min(count, cap(self));
    return {self.buffer + shift, cap(self) - shift};
}

template <typename T, u32 t_cap>
Dynamic_Buffer<T> to_dbuff(sbuff<T, t_cap> self) {
    return { self.buffer, t_cap };
}

template <class T>
dbuff<T> copy(dbuff<T> b) {
    dbuff<T> nb = {
        m_alloc<T>(cap(b)),
        cap(b)
    };

    memcpy(nb.buffer, b.buffer, size(b));

    return nb;
}



// methods
template <typename T>
void clear(dbuff<T> *self, i32 value=0) {
    memset(self->buffer, value, self->cap);
}

template <typename T>
void resize(Dynamic_Buffer<T> *self, u32 new_cap) {
    resize(&self->buffer, &self->cap, new_cap);
}

template <typename T>
T sum(Dynamic_Buffer<T> self) {
    T out_sum = 0;
    T* endp = self.buffer + self.cap;
    for (T* p = self.buffer; p < endp; p++) {
        out_sum += *p;
    }
    return out_sum;
}

template <typename T>
T sum_lmd(dbuff<T> buffer, T& (*access_lmd)(T*)) {
    T out_sum = 0;
    T* endp = end(&buffer);
    for (T* p = begin(&buffer); p < endp; p++) {
        out_sum += access_lmd(p);
    }
    return out_sum;
}


template <typename T>
void print_fmt(dbuff<T> self, const char* item_fmt) {
    print(self.buffer, self.cap, item_fmt);
}

template <typename T>
void print(dbuff<T> self) {
    for (auto it = begin(&self); it != end(&self); it++) {
        print(*it);
    }
}






template <typename T, u32 t_dim_count>
struct Dynamic_Buffer_N {
    T* buffer;
    u32 caps[t_dim_count];

    T& get(sbuffu<t_dim_count> indexes);

    typedef T type;
};

template <typename T, u32 t_dim_count>
void init(Dynamic_Buffer_N<T, t_dim_count> *self, sbuffu<t_dim_count> new_caps) {
    memcpy(self->caps, new_caps.buffer, t_dim_count * sizeof(u32));

    u32 total_cap = 1;
    for (u32 it : self->caps) {
        total_cap *= it;
    }
    self->buffer = m_alloc<T>(total_cap);
}

template <typename T, u32 t_dim_count>
void shut(Dynamic_Buffer_N<T, t_dim_count> *self) {
    free(self->buffer);
    *self = {};
}

template <typename T, u32 t_dim_count>
T& get(Dynamic_Buffer_N<T, t_dim_count> *self, sbuffu<t_dim_count> indexes) {
    u32 global_index = 0u;
    for (u32 i = 0; i < t_dim_count - 1; i++) {
        global_index += indexes[i] * self->caps[i];
    }
    global_index += indexes[t_dim_count - 1];
    return self->buffer[global_index];
}

template <typename T, u32 t_dim_count>
u32 cap(Dynamic_Buffer_N<T, t_dim_count> *buffer) {
    u32 total_cap = 1;
    for (u32 it : buffer->caps) {
        total_cap *= it;
    }
    return total_cap;
}






template <typename T>
struct Dynamic_Buffer2 {
    T* buffer;
    u32 cap_y; // rows
    u32 cap_x; // collumns


    T& get(u32 y_index, u32 x_index);
    bool sget(T* *out_p, u32 y_index, u32 x_index);

    typedef T type;
    typedef buff_iter<T> iter;
};

template <typename T>
using dbuff2 = Dynamic_Buffer2<T>;

using dbuff2u = Dynamic_Buffer2<u32>;
using dbuff2i = Dynamic_Buffer2<i32>;
using dbuff2f = Dynamic_Buffer2<f32>;
using dbuff2d = Dynamic_Buffer2<f64>;
using dbuff2b = Dynamic_Buffer2<bool>;


template <typename T>
T& Dynamic_Buffer2<T>::get(u32 y_index, u32 x_index) {
    return buffer[cap_x * y_index + x_index];
}
template <typename T>
bool Dynamic_Buffer2<T>::sget(T* *out_p, u32 y_index, u32 x_index) {
    if (y_index < cap_y && x_index < cap_x){
        *out_p = &buffer[cap_x* y_index + x_index];
        return true;
    }
    return false;
}


template <typename T>
void init(dbuff2<T> *self, u32 init_y_cap, u32 init_x_cap) {
    self->cap_y = init_y_cap;
    self->cap_x = init_x_cap;
    self->buffer = m_alloc<T>(self->cap_y* self->cap_x);
}

template <typename T>
void init_const(dbuff2<T> *self, u32 init_y_cap, u32 init_x_cap, T value) {
    self->cap_y = init_y_cap;
    self->cap_x = init_x_cap;
    self->buffer = m_alloc<T>(self->cap_y * self->cap_x);
    T* endp = self->buffer + self->cap_y * self->cap_x;
    for (T* p = self->buffer; p < endp; p++) {
        *p = value;
    }
}

template <typename T>
void shut(dbuff2<T> *self) {
    free(self->buffer);
    *self = {};
}

template<typename T>
u32 cap_x(dbuff2<T> *self) {
    return self->cap_x;
}

template<typename T>
u32 cap_y(dbuff2<T> *self) {
    return self->cap_y;
}

template<typename T>
u32 cap(dbuff2<T> *self) {
    return self->cap_y * self->cap_x;
}

template<typename T>
T* beginp(dbuff2<T> *self) {
    return self->buffer;
}

template<typename T>
T* endp(dbuff2<T> *self) {
    return self->buffer + cap(self);
}

template<typename T>
buff_iter<T> begin(dbuff2<T> *self) {
    return {self->buffer};
}

template<typename T>
buff_iter<T> end(dbuff2<T> *self) {
    return {self->buffer + cap(self)};
}

template <typename T>
void clear(dbuff2<T> *self, i32 value=0) {
    memset(self->buffer, value, cap_total(self));
}


template<typename T>
void scan(Dynamic_Buffer2<T> *self, const char* item_fmt) {
    scan(self->buffer, self->total_capacity(), item_fmt);
}


template<typename T>
void print(Dynamic_Buffer2<T> *self, const char* item_fmt, const char* row_delim="\n") {
    u32 len = self->total_capacity();
    for (u32 i = 0; i < len; i++) {
        printf(item_fmt, self->buffer[i]);

        if ((i % self->cap_x) == self->cap_x - 1)
            printf(row_delim);
    }
}


template <typename T>
auto& _get(u32 index, void* buffer) {
    if (index != 0) {
        assert(("Index out of bounds", false));
    }
    return *(T*)buffer;
}

template <typename T, typename... Gargs>
auto& _get(u32 index, void* buffer) {
    if (index == 0) {
        return *(T*)buffer;
    }

    return _get<Gargs...>(index - 1, (u8*)buffer + sizeof(T));
}






struct Dynamic_Element_Size_Buffer {
    dbuff<u8> buffer;
    u32 stride;

    u8& operator[](u32 index) {
        return *(buffer.buffer + stride * index);
    }

    typedef u8 type;
    typedef buff_iter<u8> iter;
};

using desbuff = Dynamic_Element_Size_Buffer;


void init(desbuff *self, u32 init_cap) { init(&self->buffer, init_cap); }
void shut(desbuff *self) { shut(&self->buffer); }


inline u32 cap(desbuff *buffer) { return cap(buffer->buffer); }
inline u8* beginp(desbuff *buffer) { return beginp(buffer->buffer); }
inline u8* endp(desbuff *buffer) { return endp(buffer->buffer); }
inline buff_iter<u8> begin(desbuff *buffer) { return begin(buffer->buffer); }
inline buff_iter<u8> end(desbuff *buffer) { return end(buffer->buffer); }

//namespace mdbuffer {
//template <typename T>
//T& get_item(T* buffer, u32 dim_count, u32 dim_capacity) {

//}

//}

//template <typename T>
//struct Dynamic_Multidim_Buffer {
    //u32 dim_capacity;
    //u32 dim_count;
    //T* buffer;
//};


//template <typename T, u32 t_dim_count, u32 t_dim_capacity>
//struct Static_Multidim_Array {
    //u32 len;
    //T buffer[t_dim_capacity * t_dim_count];

    
//};



}
