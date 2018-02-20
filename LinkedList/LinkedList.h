#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <iostream>
#include <memory>

template<typename T>
class LinkedList {
private:

    struct Node {
        T value;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> end;
    size_t size;

public:
    LinkedList () {
        head = nullptr;
        end = nullptr;
        size = 0;
    }

    LinkedList (LinkedList &&obj) {
        size = obj.size;
        for (int i = 0; i < size; i++)
            push_back (forward (obj[i]));
    }

    LinkedList (std::initializer_list<T> list) {
        head = nullptr;
        end = nullptr;
        size = 0;
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

        std::shared_ptr<Node> search = head;
        for (size_t i = 0; i < index; i++)
            search = search->next;

        return search->value;
    }

    const T &operator[] (size_t index) const {
        if (index >= size || index < 0)
            throw std::out_of_range ("Error! Out of list! operator[]");

        std::shared_ptr<Node> search = head;
        for (size_t i = 0; i < index; i++)
            search = search->next;

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


    void push_front (T &&val) {
        if (size == 0) {
            head = std::shared_ptr<Node> (new Node ({ forward (val), nullptr, nullptr }));
            end = head;
        } else {
            std::shared_ptr<Node> newHead (new Node ({ forward (val), head, nullptr }));
            head->prev = newHead;
            head = newHead;
        }
        size++;
    }

    void pop_front () {
        if (size == 0)
            return;//throw std::out_of_range ("The list is empty!");

        if (size == 1) {
            head.reset ();
            end = head = nullptr;
        } else {
            std::shared_ptr<Node> oldHead = head;
            head = head->next;
            head->prev = nullptr;
        }
        size--;
    }


    void push_back (T &&val) {
        if (size == 0) {
            head = std::shared_ptr<Node> (new Node { forward (val), nullptr, nullptr });
            end = head;
        } else {
            std::shared_ptr<Node> newEnd (new Node { forward (val), nullptr, end });
            end->next = newEnd;
            end = newEnd;
        }
        size++;
    }

    void pop_back () {
        if (size == 0)
            return;//throw std::out_of_range ("The list is empty!";

        if (size == 1) {
            head.reset ();
            end.reset ();
            end = head = nullptr;
        } else {
            std::shared_ptr<Node> oldEnd = end;
            end = end->prev;
            end->next = nullptr;
        }
        size--;
    }


    void insert (size_t pos, T &&val) {
        if (pos >= size || pos < 0)
            throw std::out_of_range ("Error! Out of list! Insert");

        if (pos == 0) {
            push_front (forward (val));
            return;
        }

        std::shared_ptr<Node> before = head;
        for (size_t i = 1; i < pos; i++)
            before = before->next;
        std::shared_ptr<Node> after = before->next;

        std::shared_ptr<Node> newValue (new Node ({ forward (val), after, before }));
        before->next = newValue;
        after->prev = newValue;

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

        std::shared_ptr<Node> before = head;
        for (size_t i = 1; i < pos; i++)
            before = before->next;
        std::shared_ptr<Node> forDelete = before->next;

        before->next->next->prev = before;
        before->next = before->next->next;

        size = size - 1;
    }

private:
    T &&forward (typename std::remove_reference<T>::type &t) noexcept {
        return static_cast<T &&>(t);
    }
};

#endif // !_LINKED_LIST_