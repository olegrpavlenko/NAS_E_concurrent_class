//https://leetcode.com/problems/print-in-order/

class Foo {

    int currentTurn;

    public Foo() {
        currentTurn = 0;
    }

    public void cond_print(Runnable printer, int turn) throws InterruptedException
    {
        synchronized (this)
        {
            while(currentTurn != turn)
            {
                wait();
            }
        } 
        printer.run();
        synchronized (this)
        {
            ++currentTurn;
            notifyAll();
        }
    }

    public void first(Runnable printFirst) throws InterruptedException {
        // printFirst.run() outputs "first". Do not change or remove this line.
        cond_print(printFirst, 0);
    }

    public void second(Runnable printSecond) throws InterruptedException {
        // printSecond.run() outputs "second". Do not change or remove this line.
        cond_print(printSecond, 1);
    }

    public void third(Runnable printThird) throws InterruptedException {
        // printThird.run() outputs "third". Do not change or remove this line.
        cond_print(printThird, 2);
    }
}