//
// Created by Junjie Wang on 2/26/23.
//

#ifndef TUTORIAL_JSON_H
#define TUTORIAL_JSON_H

#include <vector>
#include <utility>
#include <ostream>
#include <variant>
#include <unordered_map>
#include <string>

namespace json {
    class Object;

    class Array;

    using Null = std::monostate;
    using Int = int;
    using String = std::string;
    using Data = std::variant<Int, String, Null, Array, Object>;

    class Array {
    public:
        Array() = default;

        Array(std::initializer_list<Data> l) : data_(l) {}

        Array &append(const Data &el) {
            data_.emplace_back(el);
            return *this;
        }

        template<typename Stream>
        friend Stream &operator<<(Stream &os, const Array &arr);

    private:
        std::vector<Data> data_;
    };

    class Object {
    public:
        Data &operator[](const std::string &key) {
            return data_[key];
        }

        const Data &operator[](const std::string &key) const {
            return data_.at(key);
        }

        template<typename Stream>
        friend Stream &operator<<(Stream &os, const Object &object);

    private:
        std::unordered_map<std::string, Data> data_;
    };

    template<typename Stream>
    Stream &operator<<(Stream &os, const Null &null) {
        os << "null";
        return os;
    }

    template<typename Stream>
    Stream &operator<<(Stream &os, const Data &el) {
        std::visit([&](auto &val) {
            os << val;
        }, el);
        return os;
    }

    template<typename Stream>
    Stream &operator<<(Stream &os, const Object &object) {
        os << "object{";
        int idx = 0;
        for (const auto&[k, v]: object.data_) {
            if (idx > 0) {
                os << ",";
            }
            os << k << ":" << v;
            idx++;
        }
        os << "}";
        return os;
    }

    template<typename Stream>
    Stream &operator<<(Stream &os, const Array &arr) {
        os << "array[";
        int idx = 0;
        for (const auto &el: arr.data_) {
            if (idx > 0) {
                os << ",";
            }
            os << el;
            idx++;
        }
        os << "]";
        return os;
    }
}
#endif //TUTORIAL_JSON_H
