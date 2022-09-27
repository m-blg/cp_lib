
#include "array.cc"

namespace cp {

template <typename T>
struct String {
    T* sptr;
    T* dptr;
    u32 slen;
    u32 dlen;
};

using str = String<char>;


// iterator
template <typename T>
struct String_Iterator {
    T* ptr;
    u32 len;
    String<T> *str_ref;

    T* operator->();
};

template <typename T>
using str_iter = String_Iterator<T>;

template <typename T>
T* String_Iterator<T>::operator->() {
    return this->ptr;
}


template <typename T>
T& operator*(const str_iter<T>& it) {
    return *it.ptr;
}

template <typename T>
void next(str_iter<T> *it) {
    if (it->len != it->str_ref->slen) {
        it->ptr++;
    } else {
        it->ptr = it->str_ref->dptr;
    }
    it->len++;
}

template <typename T>
void prev(str_iter<T> *it) {
    if (it->len != it->str_ref->slen) {
        it->ptr--;
    } else {
        it->ptr = it->str_ref->sptr;
    }
    it->len--;
}

template <typename T>
void operator++(str_iter<T>& it) {
    next(&it);
}
template <typename T>
void operator++(str_iter<T>& it, int) {
    next(&it);
}

template <typename T>
void operator--(str_iter<T>& it) {
    prev(&it);
}

template <typename T>
void operator--(str_iter<T>& it, int) {
    prev(&it);
}

template <typename T>
bool operator!=(const str_iter<T>& f, const str_iter<T>& s) {
    return f.ptr != s.ptr;
}

template <typename T>
u32 len(String<T> *self) {
    return self->slen + self->dlen;
}

template <typename T>
str_iter<T> begin(String<T> *self) {
    return {self->sptr, 1, self};
}
template <typename T>
str_iter<T> end(String<T> *self) {
    return {self->dptr + self->dlen, len(self) + 1, self};
}

template <typename T>
void copy(T* out_dst, String<T> src, u32 len) {
    assert(len <= len(&src));

    memcpy(out_dst, src.sptr, sizeof(T) * src.slen);
}


template <typename T>
bool operator==(String<T> f, String<T> s)  {
    if (len(&f) != len(&s)) {
        return false;
    } else {
        auto it_f = begin(&f);
        auto it_s = begin(&s);
        for (; it_f != end(&f); it_f++, it_s++) {
            if (*it_f != *it_s) return false;
        }
        return true;
    }
}

template <typename T>
bool operator!=(String<T> f, String<T> s)  {
    if (len(&f) != len(&s)) {
        return true;
    } else {
        auto it_f = begin(&f);
        auto it_s = begin(&s);
        for (; it_f != end(&f); it_f++, it_s++) {
            if (*it_f != *it_s) return true;
        }
        return false;
    }
}

template <typename T, u32 t_static_cap>
struct String_Buffer {
    T sbuffer[t_static_cap];
    T* dbuffer;
    u32 cap;
    u32 len;
};


template <typename T, u32 t_static_cap>
void init(String_Buffer<T, t_static_cap> *self, u32 init_cap=0) {
    if (init_cap <= t_static_cap) {
        self->dbuffer = null;
        self->cap = t_static_cap;
    } else {
        self->dbuffer = m_alloc<T>(init_cap - t_static_cap);
        self->cap = init_cap;
    }
    self->len = 0;
}


template <typename T, u32 t_static_cap>
void init(String_Buffer<T, t_static_cap> *self, const T* c_str) {
    u32 init_cap = strlen(c_str);
    if (init_cap <= t_static_cap) {
        self->dbuffer = null;
        self->cap = t_static_cap;
    } else {
        self->dbuffer = m_alloc<T>(init_cap - t_static_cap);
        self->cap = init_cap;
    }
    self->len = init_cap;
}

template <typename T, u32 t_static_cap>
void shut(String_Buffer<T, t_static_cap> *self) {
    if (self->dbuffer != null)
        free(self->dbuffer);
    self->dbuffer = null;
    self->cap = 0;
    self->len = 0;
}

template <typename T, u32 t_static_cap>
void assign(String_Buffer<T, t_static_cap> *self, str s) {
    if (len(&s) <= t_static_cap) {
        if (self->dbuffer != null) {
            free(self->dbuffer);
        }
        self->cap = t_static_cap;
        self->len &= len(&s);
        memcpy(self->sbuffer, beginp(&s), sizeof(T) * len(&s));
    } else {
        if (len(&s) > self->cap) {
            self->dbuffer = m_ralloc(self->dbuffer, len(&s) - t_static_cap);
            self->cap = t_static_cap;
        }
        self->len &= len(&s);
        memcpy(self->sbuffer, beginp(&s), sizeof(T) * t_static_cap);
        memcpy(self->dbuffer, beginp(&s), sizeof(T) * len(&s) - t_static_cap);
    }
}


template <typename T, u32 t_static_cap>
void assign(String_Buffer<T, t_static_cap> *self, String_Buffer<T, t_static_cap> *other) {
    if (self->dbuffer != null) {
        free(self->dbuffer);
    }
    self->cap = other->cap;
    self->len = other->len;

    memcpy(self->sbuffer, other->sbuffer, sizeof(T) * t_static_cap);
    if (other->dbuffer != null) {
        self->dbuffer = m_alloc<T>(other->cap - t_static_cap);
        memcpy(self->dbuffer, other->dbuffer, sizeof(T) * other->len - t_static_cap);
    }
}

//template <typename T, u32 t_static_cap>
//void append() {}


template <typename T, u32 t_static_cap>
void cat(String_Buffer<T, t_static_cap> *out_sb, dbuff<str> tokens) {
    u32 total_len = 0;
    for (auto it = begin(&tokens); it != end(&tokens); it++) {
        total_len += len(it.ptr);
    }
    if (out_sb->cap < total_len) {
        if (out_sb->dbuffer != null)
            free(out_sb->dbuffer);
        out_sb->dbuffer = m_alloc<T>(total_len - t_static_cap);
        out_sb->cap = total_len;
    }
    out_sb->len = 0;
    // append
    for (auto it = begin(&tokens); it != end(&tokens); it++) {
        if (out_sb->len + len(it.ptr) <= t_static_cap) {
            memcpy(out_sb->sbuffer, it->buffer, sizeof(T) * len(it.ptr));
        } else {
            if (out_sb->len < t_static_cap) {
                u32 sbuff_part_len = (t_static_cap - out_sb->len);
                memcpy(out_sb->sbuffer, it->buffer, sizeof(T) * sbuff_part_len);
                memcpy(out_sb->dbuffer, it->buffer + sbuff_part_len, sizeof(T) * (len(it.ptr) - sbuff_part_len));
            } else {
                memcpy(out_sb->dbuffer, it->buffer, sizeof(T) * len(it.ptr));
            }
        }
        out_sb->len += len(it.ptr);
    }
}


template <typename T, u32 t_static_cap>
void split(dbuff<str> *out_tokens, String_Buffer<T, t_static_cap> *sb, str delim) {
    str token = { beginp(sb), 0 };
    for (auto it = begin(sb); it != end(sb); it++) {
        if (*it == delim) {
            push(out_tokens, *it);
            token.buffer += token.cap;
            token.cap = 0;
            continue;
        }
        token.cap++;
    }
}


using strb = String_Buffer<char, 32>;


using dstr = Dynamic_Array<char>;

void init(dstr *self, const char* c_str) {
    u32 init_cap = strlen(c_str);
    self->buffer = (char*)c_str;
    self->cap = init_cap;
    self->len = init_cap;
}

dstr *cat(dstr *first, dstr *second) {
    append(first, second);
    return first;
}

template <u32 append_str_count>
dstr *cat(dstr *first, sbuff<dstr, append_str_count> others) {
    for (auto it = begin(&others); it < end(others); it++) 
        append(first, it);
    return first;
}

//alloc
template <u32 append_str_count>
dstr join(sbuff<dstr, append_str_count> strings) {
    dstr first; init(&first);
    for (auto it = begin(&strings); it < end(strings); it++) 
        append(first, it);
    return first;
}

}


