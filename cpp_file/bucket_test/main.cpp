#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> um = {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
    };

    std::cout << "Total elements: " << um.size() << "\n";
    std::cout << "Bucket count: " << um.bucket_count() << "\n";
    std::cout << "Load factor: " << um.load_factor() << "\n";
    std::cout << "Max load factor: " << um.max_load_factor() << "\n";

    // 遍历所有桶
    for (size_t i = 0; i < um.bucket_count(); ++i) {
        std::cout << "Bucket #" << i << " has " << um.bucket_size(i) << " element(s).\n";
    }

    // 查看某个 key 的 bucket
    int key_1 = 3;
    std::cout << "Key_1 " << key_1 << " is in bucket: " << um.bucket(key_1) << "\n";
    int key_2 = 5;
    std::cout << "Key_2 " << key_2 << " is in bucket: " << um.bucket(key_2) << "\n";
    return 0;
}