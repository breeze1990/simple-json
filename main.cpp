#include <iostream>
#include "json.h"

int main() {
    json::Object o;
    o["k"] = 1;
    o["k2"] = json::Null();
    o["k3"] = "hello";
    std::cout << o << std::endl;

    json::Array arr2 = {1, "val"};
    arr2.append(2);
    arr2.append("val2");
    std::cout << arr2 << std::endl;

    json::Object obj;
    obj["k1"] = o;
    obj["k2"] = arr2;
    std::cout << obj << std::endl;
    return 0;
}
