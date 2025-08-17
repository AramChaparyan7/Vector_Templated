#include <iostream>
#include "../includes/Vector.hpp"

int main() {
    Vector<int> v = {1, 5, 6, 9};
    Vector<char> cv(4, 'a');
    Vector<char> cv2(9, 'b');
    swap(cv, cv2);
    cv.push_back('e');
    for(int i = 0; i < cv.size(); ++i) {
        std::cout << cv[i];
    }
    cv.clear();
    return 0;
}