#include <iostream>
#include <memory>

class LinkedListIndexError : public std::exception {
    std::string msg;
public:
    LinkedListIndexError(std::string mess) : msg{mess}
        {}
    virtual ~LinkedListIndexError(){}
    const char* what() const noexcept override { return msg.c_str(); }
};

template <typename T>
class Object {
    T data;
    std::shared_ptr<Object<T>> next{nullptr};
    std::shared_ptr<Object<T>> prev{nullptr};
public:
    Object(T d) : data{d}, next{nullptr}, prev{nullptr}
        {}
    Object(T d, std::shared_ptr<Object<T>> n) : data{d}, next{n}
        {}
    T& get_data()  { return data; }
    std::shared_ptr<Object<T>>& get_next() { return next; }
    std::shared_ptr<Object<T>>& get_prev() { return prev; }
};

template <typename T>
class LinkedList {
    std::shared_ptr<Object<T>> head{nullptr};
    std::shared_ptr<Object<T>> tail{nullptr};
    int count{0};
public:
    void push_front(T elem)
    {
        if (head == nullptr) {
            std::shared_ptr<Object<T>> obj {std::make_shared<Object<T>>(elem)};
            head = obj;
            tail = obj;
            count++;
            return;
        }
        std::shared_ptr<Object<T>> obj {std::make_shared<Object<T>>(elem)};
        obj->get_next() = head;
        head->get_prev() = obj;
        head = obj; 
        count++;
        return;      
    }
    void push_back(T elem)
    {
        if (tail != nullptr) {
            std::shared_ptr<Object<T>> obj {std::make_shared<Object<T>>(elem)};
            tail->get_next() = obj;
            obj->get_prev() = tail;
            tail = obj;
            count++;
            return;
        }
        std::shared_ptr<Object<T>> obj {std::make_shared<Object<T>>(elem)};
        head = obj;
        tail = obj;
        count++;
        return;
    }

    void pop_front()
    {
        if (head == nullptr) return;

        head = head->get_next();
        head->get_prev() = nullptr;
        count--;
        if (head == nullptr) tail = nullptr;

        return;
    }
    void pop_back()
    {
        if (tail == nullptr) return;

        std::shared_ptr<Object<T>> p = head;
        if (head == tail) {
            tail = nullptr;
            head = nullptr;
            count--;
            return;
        }

        while (true) {
            if (p->get_next() == tail) {
                tail = p;
                tail->get_next() = nullptr;
                break;
            }
            p = p->get_next();
        }
        count--;
        return;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= count)
            throw LinkedListIndexError("Invalid element index.");

        std::shared_ptr<Object<T>> p = head;
        for(int i = 0; i < index; i++) {
            p = p->get_next(); 
        }
        return p->get_data();
    }
    void remove(int index)
    {
        if (index < 0 || index >= count)
            throw LinkedListIndexError("Invalid element index.");
            
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == count-1) {
            pop_back();
            return;
        }

        std::shared_ptr<Object<T>> p = head;
        std::shared_ptr<Object<T>> p2 = head;
        int i = 0;
        while(true) {
            if (i == index) {
                p2 = p->get_prev();
                p2->get_next() = p->get_next();
                p->get_next()->get_prev() = p2;
                break;
            }
            p = p->get_next();
            i++;
        }
        count--;
        return;
    }

    void insert(int index, T elem)
    {
        if (index < 0 || index > count)
            throw LinkedListIndexError("Invalid element index.");

        if (index == 0) {
            push_front(elem);
            return;
        }
        if (index == count) {
            push_back(elem);
            return;
        }
        std::shared_ptr<Object<T>> obj {std::make_shared<Object<T>>(elem)};

        std::shared_ptr<Object<T>> p = head;
        std::shared_ptr<Object<T>> p2 = head;
        for(int i = 0; i < index; i++) {
            p = p->get_next(); // текущий 
            p2 = p->get_prev(); // предыдущий
        }
        p2->get_next() = obj;
        obj->get_next() = p;
        obj->get_prev() = p2;
        p->get_prev() = obj;
        count++;
        
        return;


    }

    std::shared_ptr<Object<T>>& get_head() { return head; }
    std::shared_ptr<Object<T>>& get_tail() { return tail; }
};

int main()
{
    LinkedList<int> lst6;
lst6.push_back(1);
lst6.push_back(2);
lst6.push_back(3);
lst6.push_back(4);
lst6.remove(1);  // удаляем 2
lst6.insert(2, 5);


std::shared_ptr< Object<int> > ptr_lst_u = lst6.get_head();
while(ptr_lst_u) {
    int a = ptr_lst_u->get_data();
    std::cout << a << " ";
    ptr_lst_u = ptr_lst_u->get_next();
}
    return 0;
}