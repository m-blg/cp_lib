
template <typename T, typename t_first>
T& get_value(Memory_Layout<t_first> ml, void* buffer, u32 index) {
    if (index != 0) {
        assert(("Index out of bounds", false));
    }
    return *(T*)buffer;
}

template <typename T, typename t_first, typename... Args>
T& get_value(Memory_Layout<t_first, Args...> ml, void* buffer, u32 index) {
    if (index == 0) {
        return *(T*)buffer;
    }

    return get_value<T>(Memory_Layout<Args...>(), (u8*)buffer + sizeof(t_first), index-1);
}


// template <u32 index, typename T, typename... Args>
// struct _ML {
//     _ML<index - 1, Args...> next;

//     constexpr auto& _get(void* buffer) {
//         if constexpr(index == 0) {
//             return *(T*)buffer;
//         }

//         return next._get<index - 1>((u8*)buffer + sizeof(T));
//     }

// };

// template <u32 index, typename T>
// struct _ML<u32, T> {
//     constexpr auto& _get(void* buffer) {
//         if constexpr(index != 0) {
//             assert(("Index out of bounds", false));
//         }
        
//         return *(T*)buffer;
//     }
// };


// template <>
// sturct Get_Impl {

// };


template <typename T, typename... Ts>
struct Tupple {
    T first;
    Tupple<Ts...> next;
    
    template <u32 index, typename... T2s>
    constexpr static auto& get(Tupple<T2s...> *t) {
        if constexpr(index == 0) {
            return t->first;
        } else 
            return Tupple<T2s...>::get<index - 1>(&t->next);
    }

    template <u32 index>
    constexpr auto& get() {
        return get<index>(this);
    }
};

template <typename T>
struct Tupple<T> {
    T first;

    template <u32 index, typename... T2s>
    constexpr static auto& get(Tupple<T2s...> *t) {
        if constexpr(index != 0) {
            assert(("Index out of bounds", false));
        } 
        return t->first;
    }
};

template <u32 index, typename... Ts>
struct _ML_Size {};

template <u32 index, typename T, typename... Ts>
struct _ML_Size<index, T, Ts...> {
    static const u32 size = sizeof(T) + _ML_Size<index - 1, Ts...>::size;
};

template <u32 index>
struct _ML_Size<index> {
    static const u32 size = 0;
};


template <typename T, typename... Ts>
struct _ML_Size<0, T, Ts...> {
    static const u32 size = sizeof(T);
};

template <u32 index, typename T, typename... Ts>
constexpr u32 ml_size() {
    if constexpr(index == 0) {

    }
}

template <typename T, typename... Ts>
struct Arg_Pack {
   static const Arg_Pack<Ts...> next;
};

template <u32 index, typename T, typename... Ts>
auto get_arg_type(Arg_Pack<T, Ts...> pack) {
    if constexpr(index == 0) {
        return T();
    } else {
        return get_arg<index-1>(Arg_Pack<Ts...>::next);
    }
}

// template <typename... Args>
// void cpy_values(void* buffer, Args... args) {
//     cpy_values(buffer, args...);
// }