

namespace cp {
    
    template <typename T>
    inline T min(T first, T second) {
        return ((first < second) ? first : second);
    }

    template <typename T>
    inline T max(T first, T second) {
        return ((first > second) ? first : second);
    }
}