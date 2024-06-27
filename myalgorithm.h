#pragma once
#define NON_HEAP_SORT
#include<cmath>
namespace mystl {//命名空间:基础算法模板
    template<typename T>
    struct myless {
        constexpr bool operator()(const T& a, const T& b) const {
            return a < b;
        }
    };
    template<typename T>
    struct mygreater {
        constexpr bool operator()(const T& a, const T& b) const {
            return a > b;
        }
    };

    template<typename S>
    constexpr S mymax(const S& a, const S& b) {
        return a > b ? a : b;
    }
    template<typename S>
    constexpr S mymin(const S& a, const S& b) {
        return a > b ? b : a;
    }
    template<typename S>
    constexpr S medium(const S& a, const S& b, const S& c) {
        return (a < b && b < c) ? b : (b < a && a < c) ? a : c;
    }
    template<typename S, typename Compare>
    constexpr S medium(const S& a, const S& b, const S& c, Compare comp) {
        return (comp(a, b) && comp(b, c)) ? b : (comp(b, a) && comp(a, c)) ? a : c;
    }
    template<typename T>
    struct __compare {
        T max, min;
    };

    template<typename InputIt, typename Compare>
    auto maxmin(InputIt first, InputIt last, Compare comp) {
        auto temp = *first;
        __compare<decltype(temp)> cmp = { *first, *first };
        for (InputIt it = first; it != last; it++) {
            if (comp(*it, cmp.max)) cmp.max = *it;
            if (comp(*it, cmp.min)) cmp.min = *it;
        }
        return cmp;
    }
    template<typename InputIt>
    auto maxmin(InputIt first, InputIt last) {
        auto temp = *first;
        __compare<decltype(temp)> cmp = { *first, *first };
        for (InputIt it = first; it != last; it++) {
            if (*it > cmp.max) cmp.max = *it;
            if (*it < cmp.min) cmp.min = *it;
        }
        return cmp;
    }
}


namespace mystl{//命名空间:哈希算法
    template <typename T>
    inline size_t hashfunc(const T& value) {
        size_t hashnum = 0;
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            hashnum = (257 * (hashnum + bytes[i])) >> 3;
        }

        return hashnum;
    }
    template<>
    inline size_t hashfunc<std::string>(const std::string& value) {
        size_t hashnum = 0;
        for (size_t i = 0; i < value.size(); ++i) {
            hashnum = (257 * (hashnum + value[i])) >> 3;
        }
        return hashnum;
    }
    template<>
    inline size_t hashfunc<const char*>(const char* const& value) {
        size_t hashnum = 0;
        for (size_t i = 0; i < strlen(value); ++i) {
            hashnum = (257 * (hashnum + value[i])) >> 3;
        }
        return hashnum;
    }
    template<class T>
    struct myhash {
        size_t operator()(const T& value) const {
            return hashfunc(value);
        }
    };
    template <typename T>
    inline void hash_combine(size_t& seed, const T& value) {
        seed ^= myhash<T>{}(value)+1145141919810ull + (seed << 6) + (seed >> 2);
    }

    // 使用折叠表达式计算多个元素的混合哈希值
    template <typename... Args>
    inline size_t mixed_hash(const Args&... args) {
        size_t seed = 0;
        (hash_combine(seed, args), ...);  // 折叠表达式，结合所有元素的哈希值
        return seed;
    }
}


namespace mystl {//命名空间:排序算法

    template<typename T, typename Compare>
    class sortmethod {
    private:
        using ll = long long; using cllref = const ll&;

        struct mynumpair { ll first{}, second{}; };

        static const size_t INSERTION_SORT_THRESHOLD = 16;
        ll length, max_deep, deep;
        constexpr static T medium(const T& a, const T& b, const T& c, Compare comp) {
            return comp(a, b) ? (comp(b, c) ? b : (comp(a, c) ? c : a)) : (comp(a, c) ? a : (comp(b, c) ? c : b));
        }
        void insertion_sort(T* arr, cllref low, cllref high, Compare comp) {
            for (ll i = low + 1; i <= high; i++) {
                T key = std::move(arr[i]);
                ll j = i - 1;
                // 将比key大的元素向右移动
                while (j >= low && comp(key, arr[j])) {
                    arr[j + 1] = std::move(arr[j]);
                    j--;
                }arr[j + 1] = std::move(key);
            }
        }
#ifndef NON_HEAP_SORT
        void heapify(T* arr, ll n, ll i, Compare comp) {
            for (ll l = (i << 1) + 1, r = (i << 1) + 2, largest = i; largest != i;) {
                if (l < n && comp(arr[l], arr[largest]))largest = l;
                if (r < n && comp(arr[r], arr[largest]))largest = r;
                std::swap(arr[i], arr[largest]); i = largest;
            }
        }
        void heapsort(T* arr, ll n, Compare comp) {
            for (ll i = n / 2 - 1; i >= 0; i--) {
                heapify(arr, n, i, comp);
            }

            for (ll i = n - 1; i >= 0; i--) {
                std::swap(arr[0], arr[i]);
                heapify(arr, i, 0, comp);
            }
        }
        void optimized_quicksort(T* arr, ll low, ll high, Compare comp) {
            if (low < high) {
                deep++;
                if (high - low < INSERTION_SORT_THRESHOLD) {
                    insertion_sort(arr, low, high, comp);  // 调用插入排序
                    deep--; return;
                }
                if (deep > max_deep) {
                    heapsort(arr, high - low + 1, comp);  // 调用堆排序
                    deep--; return;
                }
                T pivot = medium(arr[low], arr[(low + high) >> 1], arr[high], comp);
                ll i = low - 1;
                ll j = high + 1;
                while (true) {
                    do {
                        i++;
                    } while (comp(arr[i], pivot));

                    do {
                        j--;
                    } while (comp(pivot, arr[j]));

                    if (i >= j) {
                        break;
                    }

                    std::swap(arr[i], arr[j]);
                }

                optimized_quicksort(arr, low, j, comp);
                optimized_quicksort(arr, j + 1, high, comp);
            }
            // 改进版快速排序
            //当待排序区间的长度小于16时，使用插入排序，当递归次数大于样本量的平方根时，使用堆排序
        }
#endif   
        void iterative_quicksort(T* arr, cllref low, cllref high, Compare comp) {
            // 迭代式快速排序
            // 先将待排序区间分割成两个子区间，然后用栈维护子区间的边界，
            // 每次从栈中弹出一个子区间，迭代排序两个子区间，
            // 直到子区间的长度小于16时，使用插入排序
            ll len = max_deep, top = -1; mynumpair* numstack = new mynumpair[len];// 栈
            auto renew = [&](mynumpair*& arr, ll& len) {
                mynumpair* newarr = new mynumpair[len * 2];
                for (ll i = 0; i < len; i++)
                    newarr[i * 2] = std::move(arr[i]);
                delete[] arr; arr = newarr; len *= 2;
                };
            auto push = [&](const ll& l, const ll& r) {if (top >= len - 1)renew(numstack, len);   numstack[++top] = { l, r }; };
            push(low, high);
            while (top >= 0) {
                ll l = numstack[top].first; ll r = numstack[top].second; top--;
                if (l < r) {
                    if (r - l < INSERTION_SORT_THRESHOLD) { insertion_sort(arr, l, r, comp); continue; }
                    T pivot = medium(arr[l], arr[(l + r) >> 1], arr[r], comp); ll i = l, j = r;
                    while (i <= j) {
                        while (comp(arr[i], pivot))i++;
                        while (comp(pivot, arr[j]))j--;
                        if (i <= j)
                            std::swap(arr[i++], arr[j--]);
                    }
                    if (l < j)push(l, j); if (i < r)push(i, r);
                }
            }
            delete[] numstack;
        }

    public:
        sortmethod(cllref len = 0) : length(len), max_deep((ll)log2(len) << 1), deep(0) {}
        void iterative_sort(T* begin, T* end, Compare comp) {
            iterative_quicksort(begin, 0, length - 1, comp);
        }
        void mysort(T* begin, T* end, Compare comp) {
#ifndef NON_HEAP_SORT
            optimized_quicksort(begin, 0, length - 1, comp);
#else
            iterative_quicksort(begin, 0, length - 1, comp);
#endif
        }
    };

    template<typename T, typename Compare>
    inline void mysort(T* begin, T* end, Compare comp) {
        sortmethod<T, Compare>(end - begin).mysort(begin, end, comp);
    }

    template<typename T>
    inline void mysort(T* begin, T* end) {
        sortmethod<T, myless<T>>(end - begin).mysort(begin, end, myless<T>());
    }
}// namespace mystl



namespace mystl {//命名空间：函数对象myfunction

    template<class F1, class F2>
    inline constexpr bool is_same_type = false;

    template<class T>
    inline constexpr bool is_same_type<T, T> = true;

    template<class F>
    class myfunction;

    template<class R, class ...A>
    class myfunction<R(A...)> {
    private:
        struct Base {
            virtual ~Base() = default;
            virtual R operator()(A  ...args) const = 0;
            virtual Base* clone() const = 0;
        };
        template<class F>
        struct Derived : Base {
            F f;
            Derived(F f) : f(std::move(f)) {}
            R operator()(A... args) const override {
                return f(std::forward<A>(args)...);
            }
            Base* clone() const override {
                return new Derived(f);
            }
        };

        Base* p;

    public:
        myfunction() : p(nullptr) {}

        ~myfunction() { delete p; p = nullptr; }

        myfunction(const myfunction& other) : p(nullptr) {
            if (other.p)  p = other.p->clone();
        }

        myfunction(myfunction&& other) noexcept : p(other.p) {
            other.p = nullptr;
        }

        myfunction& operator=(const myfunction& other) {
            if (this != &other) {
                delete p;
                p = other.p ? other.p->clone() : nullptr;
            }
            return *this;
        }

        myfunction& operator=(myfunction&& other) noexcept {
            if (this != &other) {
                delete p;
                p = other.p;
                other.p = nullptr;
            }
            return *this;
        }

        template<class F, class = std::enable_if_t<std::is_invocable_r_v<R, F&, A...>>>
        myfunction(F f) : p(new Derived<F>(std::move(f))) {}

        R operator()(A... args) const {
            if (!p) throw std::logic_error("uninitialized myfunction");
            return (*p)(std::forward<A>(args)...);
        }

        explicit operator bool() const {

            return p != nullptr;
        }
    };



} // namespace mystl