//https://leetcode.com/problems/print-foobar-alternately/

class FooBar {
private:
    int n;
    typedef enum Turn 
    {
        TurnFoo = 0,
        TurnBar
    } Turn;
    Turn turn;
    std::mutex print_mutex;
    std::condition_variable cv;


public:
    FooBar(int n) {
        this->n = n;
        this->turn = TurnFoo; //print Foo first
    }

    void printByTurn(function<void()> print_func, Turn myTurn, Turn nextTurn)
    {
        {
            std::unique_lock lk(print_mutex);
            cv.wait(lk, [this, &myTurn]{return this->turn == myTurn;});
        }
        print_func();
        {
            std::unique_lock lk(print_mutex);
            this->turn = nextTurn;
            cv.notify_all();
        }
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
        	printByTurn(printFoo, TurnFoo, TurnBar);
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            printByTurn(printBar, TurnBar, TurnFoo);
        }
    }
};