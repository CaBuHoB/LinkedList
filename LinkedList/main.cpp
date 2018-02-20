#include "LinkedList.h"

#include <random>
#include <ctime>

int main () {
    std::mt19937 gen (time (0));
    LinkedList<int> myLinkedList;

    try {
        for (int i = 0; i < 10; i++)
            myLinkedList.push_back (reinterpret_cast<int &&>(i));
        /*for (int i = 0; i < 9; i++)
            myLinkedList.pop_back ();*/

        for (int i = 0; i < 10; i++)
            myLinkedList.push_back (reinterpret_cast<int &&>(i));

        for (int i = 0; i < 10; i++)
            myLinkedList.insert (gen () % myLinkedList.get_size (), gen () % 40 + 11);

        myLinkedList.erase (8);

        for (size_t i = 0; i < myLinkedList.get_size (); i++)
            std::cout << myLinkedList[i] << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what () << std::endl;
    }

    return 0;
}