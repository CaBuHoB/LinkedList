#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>
#include <memory>

template<typename T>
class LinkedList {
private:

    struct Node {
        T value;
        std::unique_ptr<Node> next = nullptr;
        Node *prev = nullptr;
    };

    std::unique_ptr<Node> head = nullptr;
    Node *end = nullptr;
    size_t size = 0;

public:
    LinkedList () = default;

    LinkedList (LinkedList &obj) {
        size = obj.size;
        for (int i = 0; i < size; i++)
            push_back (obj[i]);
    }

    LinkedList (std::initializer_list<T> &list) {
        for (const auto &&i : list)
            this->push_back (i);
    }

    ~LinkedList () = default;


    size_t get_size () const {
        return size;
    }

    bool is_empty () const {
        return size == 0;
    }


    T &operator[] (size_t index) {
        if (index >= size || index < 0)
            throw std::out_of_range ("Error! Out of list! operator[]");

        Node *search = head.get ();
        for (size_t i = 0; i < index; i++)
            search = search->next.get ();

        return search->value;
    }

    const T &operator[] (size_t index) const {
        if (index >= size || index < 0)
            throw std::out_of_range ("Error! Out of list! operator[]");

        Node *search = head.get ();
        for (size_t i = 0; i < index; i++)
            search = search->next.get ();

        return search->value;
    }


    T &get_front () {
        if (size == 0)
            throw std::out_of_range ("Error! Out of list! Get_front");

        return head->value;
    }

    const T &get_front () const {
        if (size == 0)
            throw std::out_of_range ("Error! Out of list! Get_front");

        return head->value;
    }


    void push_front (const T &val) {
        if (size == 0) {
            head = std::unique_ptr<Node> (new Node ({ val, nullptr, nullptr }));
            end = head.get ();
        } else {
            std::unique_ptr<Node> newHead (new Node ({ val, std::move (head), nullptr }));
            head = std::move (newHead);
            head->next->prev = newHead.get ();

        }
        size++;
    }

    void pop_front () {
        if (size == 0)
            return;//throw std::out_of_range ("The list is empty!");

        if (size == 1) {
            head.reset ();
            end = nullptr;
            head = nullptr;
        } else {
            std::unique_ptr<Node> oldHead = std::move (head);
            head = std::move (oldHead->next);
            head->prev = nullptr;
        }
        size--;
    }


    void push_back (const T &val) {
        if (size == 0) {
            head = std::unique_ptr<Node> (new Node { val, nullptr, nullptr });
            end = head.get ();
        } else {
            std::unique_ptr<Node> newEnd (new Node { val, nullptr, end });
            end->next = std::move (newEnd);
            end = end->next.get ();
        }
        size++;
    }

    void pop_back () {
        if (size == 0)
            return;//throw std::out_of_range ("The list is empty!";

        if (size == 1) {
            head.reset ();
            end = nullptr;
            head = nullptr;
        } else {
            end = end->prev;
            end->next = nullptr;
        }
        size--;
    }


    void insert (size_t pos, const T &val) {
        if (pos >= size || pos < 0)
            throw std::out_of_range ("Error! Out of list! Insert");

        if (pos == 0) {
            push_front (val);
            return;
        }

        Node *before = head.get ();
        for (size_t i = 1; i < pos; i++)
            before = before->next.get ();

        std::unique_ptr<Node> newValue (new Node ({ val, std::move (before->next), before }));/////////////
        before->next = std::move (newValue);
        before->next->next->prev = newValue.get ();

        size++;
    }

    void erase (size_t pos) {
        if (pos >= size || pos < 0)
            throw std::out_of_range ("Error! Out of list! Erase");

        if (pos == 0) {
            pop_front ();
            return;
        }
        if (pos == size - 1) {
            pop_back ();
            return;
        }

        Node *before = head.get ();
        for (size_t i = 1; i < pos; i++)
            before = before->next.get ();

        before->next->next->prev = before;
        before->next = std::move (before->next->next);

        size--;
    }
};

#endif // !_LINKED_LIST_
