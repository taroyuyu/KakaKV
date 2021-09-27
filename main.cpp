#include "test/src/NodeImplTest.h"
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
    global_stream_lock.lock();
    std::cout << "Thread " << counter << " Start.\n";
    global_stream_lock.unlock();
    boost::system::error_code ec;
    try {
        iosvc->run(ec);
    }
    catch(...){
       std::cout<<"补货到"<<std::endl;
    }
//    }
    if (ec) {
        global_stream_lock.lock();
        std::cout << "Message: " << ec << ".\n";
        global_stream_lock.unlock();
    }
    global_stream_lock.lock();
    std::cout << "Thread " << counter << " End.\n";
    global_stream_lock.unlock();
}

void ThrowAnException(boost::shared_ptr<boost::asio::io_service>
                      iosvc) {
    global_stream_lock.lock();
    std::cout << "Throw Exception\n";
    global_stream_lock.unlock();
    iosvc->post(boost::bind(&ThrowAnException, iosvc));
    throw (std::runtime_error("The Exception !!!"));
}

int main(void) {
    boost::shared_ptr<boost::asio::io_service> io_svc(
            new boost::asio::io_service
    );
    boost::shared_ptr<boost::asio::io_service::work> worker(
            new boost::asio::io_service::work(*io_svc)
    );
    global_stream_lock.lock();
    std::cout << "The program will exit once all work has finished.\n";
    global_stream_lock.unlock();
    boost::thread_group threads;
    for (int i = 1; i <= 5; i++)
        threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
    io_svc->post(boost::bind(&ThrowAnException, io_svc));
    threads.join_all();
    return 0;
}
//boost::mutex global_stream_lock;
//
//void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
//    global_stream_lock.lock();
//    std::cout << "Thread " << counter << " Start.\n";
//    global_stream_lock.unlock();
//    try {
//        iosvc->run();
//        global_stream_lock.lock();
//        std::cout << "Thread " << counter << " End.\n";
//        global_stream_lock.unlock();
//    }
//    catch (std::exception &ex) {
//        global_stream_lock.lock();
//        std::cout << "Message: " << ex.what() << ".\n";
//        global_stream_lock.unlock();
//    }
//}
//
//void ThrowAnException(boost::shared_ptr<boost::asio::io_service>
//                      iosvc) {
//    global_stream_lock.lock();
//    std::cout << "Throw Exception\n";
//    global_stream_lock.unlock();
//    iosvc->post(boost::bind(&ThrowAnException, iosvc));
//    throw (std::runtime_error("The Exception !!!"));
//}
//
//int main(void) {
//    boost::shared_ptr<boost::asio::io_service> io_svc(
//            new boost::asio::io_service
//    );
//    boost::shared_ptr<boost::asio::io_service::work> worker(
//            new boost::asio::io_service::work(*io_svc)
//    );
//    global_stream_lock.lock();
//    std::cout << "The program will exit once all work has finished.\n";
//    global_stream_lock.unlock();
//    boost::thread_group threads;
//    for (int i = 1; i <= 8; i++)
//        threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc));
//    threads.join_all();
//    return 0;
//}
//
//void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
//    global_stream_lock.lock();
//    std::cout << "Thread " << counter << " Start.\n";
//    global_stream_lock.unlock();
//    try {
//        iosvc->run();
//        global_stream_lock.lock();
//        std::cout << "Thread " << counter << " End.\n";
//        global_stream_lock.unlock();
//    }
//    catch (std::exception &ex) {
//        global_stream_lock.lock();
//        std::cout << "Message: " << ex.what() << ".\n";
//        global_stream_lock.unlock();
//    }
//}
//
//void ThrowAnException(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
//    global_stream_lock.lock();
//    std::cout << "Throw Exception " << counter << "\n";
//    global_stream_lock.unlock();
//    throw (std::runtime_error("The Exception !!!"));
//}
//
//int main(void) {
//    boost::shared_ptr<boost::asio::io_service> io_svc(
//            new boost::asio::io_service
//    );
//    boost::shared_ptr<boost::asio::io_service::work> worker(
//            new boost::asio::io_service::work(*io_svc)
//    );
//    global_stream_lock.lock();
//    std::cout << "The program will exit once all work has finished.\n";
//    global_stream_lock.unlock();
//    boost::thread_group threads;
//    for (int i = 1; i <= 6; i++)
//        threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc, 1));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc, 2));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc, 3));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc, 4));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc, 5));
//    threads.join_all();
//    return 0;
//}

//boost::mutex global_stream_lock;
//
//void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
//    global_stream_lock.lock();
//    std::cout << "Thread " << counter << " Start.\n";
//    global_stream_lock.unlock();
//    while (true) {
////        try {
//            boost::system::error_code ec;
//            iosvc->run(ec);
//            if(ec) {
//            global_stream_lock.lock();
//            std::cout << "Error Message: " << ec << ".\n";
//            global_stream_lock.unlock();
//        }
////        break;
////    } catch(std::exception & ex)
////    {
////        global_stream_lock.lock();
////        std::cout << "Exception Message: " << ex.what() << ".\n";
////        global_stream_lock.unlock();
////    }
//}
//
//global_stream_lock.
//
//lock();
//
//std::cout << "Thread " << counter << " End.\n";
//global_stream_lock.
//
//unlock();
//
//}
//
//void ThrowAnException(boost::shared_ptr<boost::asio::io_service> iosvc) {
//    global_stream_lock.lock();
//    std::cout << "Throw Exception\n";
//    global_stream_lock.unlock();
////    iosvc->post(boost::bind(&ThrowAnException, iosvc));
//    throw (std::runtime_error("The Exception !!!"));
//}
//
//int main(void) {
//    boost::shared_ptr<boost::asio::io_service> io_svc(new boost::asio::io_service);
//    boost::shared_ptr<boost::asio::io_service::work> worker(new boost::asio::io_service::work(*io_svc));
//    global_stream_lock.lock();
//    std::cout << "The program will exit once all work has finished.\n";
//    global_stream_lock.unlock();
//    boost::thread_group threads;
//    for (int i = 1; i <= 5; i++)
//        threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
//    io_svc->post(boost::bind(&ThrowAnException, io_svc));
//    threads.join_all();
//    return 0;
//}

//boost::mutex global_stream_lock;
//
//void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter) {
//    global_stream_lock.lock();
//    std::cout << counter << ".\n";
//    global_stream_lock.unlock();
//    iosvc->run();
//    global_stream_lock.lock();
//    std::cout << "End.\n";
//    global_stream_lock.unlock();
//}
//
//size_t fac(size_t n) {
//    if (n <= 1) {
//        return n;
//    }
//    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
//    return n * fac(n - 1);
//}
//
//void CalculateFactorial(size_t n) {
//    global_stream_lock.lock();
//    std::cout << "Calculating " << n << "! factorial" << std::endl;
//    global_stream_lock.unlock();
//    size_t f = fac(n);
//    global_stream_lock.lock();
//    std::cout << n << "! = " << f << std::endl;
//    global_stream_lock.unlock();
//}
//
//int main(void) {
//    boost::shared_ptr<boost::asio::io_service> io_svc(new boost::asio::io_service);
//    boost::shared_ptr<boost::asio::io_service::work> worker(new boost::asio::io_service::work(*io_svc));
//    global_stream_lock.lock();
//    std::cout << "The program will exit once all work has finished." << std::endl;
//    global_stream_lock.unlock();
//    boost::thread_group threads;
//    for (int i = 1; i <= 5; i++)
//        threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
//    io_svc->post(boost::bind(CalculateFactorial, 5));
//    io_svc->post(boost::bind(CalculateFactorial, 6));
//    io_svc->post(boost::bind(CalculateFactorial, 7));
//    worker.reset();
//    threads.join_all();
//    return 0;
//}



//void Print1() {
//    for (int i = 0; i < 5; i++) {
//        boost::this_thread::sleep_for(boost::chrono::
//                                      milliseconds{500});
//        std::cout << "[Print1] Line: " << i << '\n';
//    }
//}
//
//void Print2() {
//    for (int i = 0; i < 5; i++) {
//        boost::this_thread::sleep_for(boost::chrono::
//                                      milliseconds{5000});
//        std::cout << "[Print2] Line: " << i << '\n';
//    }
//}
//
//#include <boost/asio.hpp>
//#include <iostream>
//
//void TimerHandler(const boost::system::error_code &ec) {
//    if (ec) {
////        global_stream_lock.lock();
//        std::cout << "Error Message: " << ec << ".\n";
////        global_stream_lock.unlock();
//    } else {
////        global_stream_lock.lock();
//        std::cout << "You see this line because you have waited for 10 seconds.\n";
//        std::cout << "Now press ENTER to exit.\n";
////        global_stream_lock.unlock();
//    }
//}
//
//int main(void) {
//    boost::asio::io_service io_svc;
////    boost::asio::io_service::work worker(io_svc);
//
//    boost::asio::deadline_timer timer(io_svc);
//    timer.expires_from_now(boost::posix_time::seconds(1));
//    timer.async_wait(TimerHandler);
//
//    boost::asio::deadline_timer timer2(io_svc);
//    timer2.expires_from_now(boost::posix_time::seconds(3));
//    timer2.async_wait(TimerHandler);
//
////    boost::thread::sleep();
//    sleep(1);
//    auto ret = io_svc.run();
//    std::cout << ret << std::endl;
//    std::cout << "We will see this line in console window." << std::endl;
//    return 0;
//}
//
//int main1() {
//    boost::thread_group threads;
//    threads.create_thread(Print1);
//    threads.create_thread(Print2);
//    threads.join_all();
//
//
////    kakakv::test::NodeImplTest test;
////    test.testStart();
//    return 0;
//}
