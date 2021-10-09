#include <umt/umt.hpp>
#include <string>
#include <thread>

class MSG {
private:
    int id;
    std::string msg;

public:
    MSG() = default;
    MSG(int _id, std::string _img): id(_id), msg(std::move(_img)) {};
    void print() {
        std::cout << "[LOGINFO] id = " << id << ", data = " << msg << '.' << std::endl;
    }
};

struct foo {
    std::string name;
    double value;
};

void Publisher_A() {
    /* This is an example of multithread communication, 
     * and Pulisher A's collaborator lives in c++.
     *
     * This is very commonly used in the process of writing algorithms.
     */

    umt::Publisher<MSG> pub("link_A");  // If you want to create a publisher, the most 
                                        // basic form is umt::Publisher<classtype> pub(<id>);
                                        // where classtype indicates the data type and 
                                        // id uniquely determines this connection.
                                        // Caution: A connection can only have one publisher (recommended), 
                                        // but there can be multiple subscribers.
                                        // Note: <classtype> can be any simple type (basic data type 
                                        // and some other data types), or a custom class composed of them.

    int cnt = 0;
    while(true) {
        pub.push(MSG(cnt++, "Hey, bro!"));

        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // It is recommended to delay in this way.
    }
}

void Subscriber_A() {
    /* This is an example of multithread communication, 
     * and Subscriber A's collaborator lives in c++.
     */

    umt::Subscriber<MSG> sub("link_A", 1);  // If you want to create a subscriber, the most basic form 
                                            // is umt::Subscriber<classtype> pub(<id>[, <length>]) where
                                            // length specifies the length of the communication queue, which
                                            // can be specified or not specified. If it is not specified, no 
                                            // data will be discarded by default.

    MSG msg;
    // Caution: When the publisher has not been created, the subscriber will report an error when trying to read the data, 
    // so it needs to be placed in the try statement block.
    while (true) {
        try {
            msg = sub.pop();  // TODO: no error, return false instead
            std::cout << "Link A: ";
            msg.print();
        } catch(...) {
            std::cout << "[WARNING] pub_A not ready." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}

void background_run_taskA() {
    /*
     * Use multithreading to bring up our function, so create a background function
     */
    
    std::thread(Publisher_A).detach();  // use std::thread(<func>).detach() to start a thread running <func>
    std::thread(Subscriber_A).detach();
}

void Publisher_C() {
    /*
     * This is an example of cross-c++-python communication, and 
     * publisher C's collaborator lives in python.
     * 
     * This usually happens in the process of debugging, we write the debug function in python 
     * without changing the C++ code and need to recompile.
     */

    umt::Publisher<MSG> pub("link_C");

    int cnt = 0;
    while(true) {
        pub.push(MSG(cnt++, "Hey, ladybro!"));

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void background_run_pubC() {
    std::thread(Publisher_C).detach();
}

void Subscriber_D() {
    /*
     * This is an example of cross-c++-python communication, and 
     * subscriber D's collaborator lives in python.
     * 
     * In fact, this is rarely used, but if your application scenario requires this, 
     * we also provide examples.
     */

    umt::Subscriber<MSG> sub("link_D", 1);
    MSG msg;
    while(true) {
        try {
            msg = sub.pop_for(1000);  // pop_for specifies a timeout period, after which an exception will be thrown. 
                                      // Unit ms
            std::cout << "Link D: ";
            msg.print();
        } catch(...) {
            std::cout << "[WARNING] pub_D not ready." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}

void background_run_subD() {
    std::thread(Subscriber_D).detach();
}

// TODO: automatic export
UMT_EXPORT_MESSAGE_ALIAS(MSG, MSG, c){
    /*
     * UMT_EXPORT_MESSAGE_ALIAS (<name>, <type>, <var>) where 
     * <name> indicates that the Library name in python is `MESSAGE_LIBS<name>`,
     * <type> indicates the type of data it will export,
     * <var> indicates its reference in this function.
     *
     * Use c.def_readwrite() or c.def_readonly() to register member variables.
     * Use c.def() to register member functions.
     * Use the symbol '&' to take their address.
     * Note: The situation of construction and destructor is special.
     */

    c.def(pybind11::init<>());
    c.def(pybind11::init<int, std::string>());
    c.def("print", &MSG::print);
}

UMT_EXPORT_MESSAGE_ALIAS_WITHOUT_TYPE_EXPORT(int, int, c);

UMT_EXPORT_OBJMANAGER_ALIAS(foo, foo, c) {
    c.def(pybind11::init<>());
    c.def(pybind11::init<std::string, double>());
    c.def_readwrite("name", &foo::name);
    c.def_readwrite("value", &foo::value);
}

PYBIND11_EMBEDDED_MODULE(Workers, m) {
    /*
     * Export as a python module
     * Format: PYBIND11_EMBEDDED_MODULE(<module>, <var>), where
     * <module> indicates its library name in python, and 
     * <var> indicates its reference in this function.
     */

    namespace py = pybind11;
    m.def("background_run_taskA", background_run_taskA);  // In order to define the module function, simply use 
                                                          // <var>.def("<name>", <func>) where <name> indicates function name in python and
                                                          // <func> indicates its name in c++
    m.def("background_run_pubC", background_run_pubC);
    m.def("background_run_subD", background_run_subD);
}