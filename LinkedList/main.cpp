#include "LinkedList.h"

#include <random>
#include <ctime>

int main () {
    std::mt19937 gen (time (0));
    LinkedList<int> myLinkedList;

    try {
        for (int i = 0; i < 10; i++)
            myLinkedList.push_back (i);

        for (int i = 0; i < 9; i++)
            myLinkedList.pop_back ();

        for (int i = 0; i < 10; i++)
            myLinkedList.push_back (i);

        std::uniform_int_distribution unfFirst(10, 50);
        int size = myLinkedList.get_size () - 1;
        std::uniform_int_distribution unfSecond(0, size);
        for (int i = 0; i < 10; i++)
            myLinkedList.insert (unfSecond(gen), unfFirst(gen));

        myLinkedList.erase (8);

        for (size_t i = 0; i < myLinkedList.get_size (); i++)
            std::cout << myLinkedList[i] << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << ex.what () << std::endl;
    }

    return 0;
}