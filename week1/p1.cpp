//https://leetcode.com/problems/print-in-order/

class Foo {
public:

    enum Turn
    {
        FirstTurn = 0,
        SecondTurn,
        ThirdTurn
    };

    int currentTurn;
    std::mutex print_mutex;
    std::condition_variable cv;
    
    Foo() {
        currentTurn = FirstTurn;
    }

    void printByTurn(function<void()> print_func, enum Turn turn)
    {
        {
            std::unique_lock lk(print_mutex);
            cv.wait(lk, [&turn, this](){ return turn == this->currentTurn; });
            //unique_lock dtor releases ownership
        }
        print_func();
        {
            std::unique_lock lk(print_mutex);
            ++currentTurn;
            cv.notify_all();
        }
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printByTurn(printFirst, FirstTurn);
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        printByTurn(printSecond, SecondTurn);
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        printByTurn(printThird, ThirdTurn);
    }
};