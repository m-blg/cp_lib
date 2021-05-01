#pragma once

#include "buffer.cc"
#include "basic.cc"


namespace cp {



    template <typename T>
    T clamp(T value, T min_value, T max_value) {
        return max(min(value, max_value), min_value);
    }

    template <typename T>
    T lerp(f32 t, T value1, T value2) {
        return (1 - t) * value1 + t * value2;
    }
    
    template <typename T>
    T integrate(dbuff<T> range, T t1, T t2) {
        T integral = 0;
        for (auto* p = range.begin(); p != range.end(); p++) {
            integral += *p;
        }
        integral *= (t2 - t1);
        integral /= range.capacity;
        return integral;
    }

    template <typename T>
    T integrate(T (*f)(T), T t1, T t2, u32 n) {
        T dt = (t2 - t1) / n;
        T integral = 0;
        T t = t1;
        for (u32 i = 0; i < n; i++, t += dt) {
            integral += f(t);
        }
        integral *= dt;
        return integral;
    }

    template <typename T>
    dbuff<T> get_range(T t1, T t2, u32 n) {
        if (n < 2) {
            return {};
        }
        dbuff<T> out_range; 
        out_range.init(n);
        T dt = (t2 - t1) / (n - 1);
        for (u32 i = 0; i < n; i++) {
            out_range[i] = t1 + dt * i;
        }
        return out_range;
    } 

    template <typename t_domain_type, typename t_range_type>
    void get_func_range(dbuff<t_domain_type> domain, dbuff<t_range_type> out_range, t_range_type(*func)(t_domain_type)) {
        auto* pr = out_range.begin();
        for (auto* pd = domain.begin(); pd != domain.end(); pd++, pr++) {
            *pr = func(*pd);
        }
    } 


    template <typename T>
    struct Range {
        T first, last, step;
    };

    template <typename T>
    T range_len(Range<T> range) {
        return range.last - range.first;
    }
}
