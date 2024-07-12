//https://leetcode.com/problems/print-foobar-alternately/

class FooBar {
    private int n;
    private enum Turn {TurnFoo, TurnBar}
    Turn turn;

    public FooBar(int n) {
        this.n = n;
        this.turn = Turn.TurnFoo; //print Foo first
    }

    private void printByTurn(Runnable printer, Turn myTurn, Turn nextTurn) throws InterruptedException
    {
        synchronized (this)
        {
            if(this.turn != myTurn)
            {
                wait();
            }
        }    
        printer.run();
        synchronized (this)
        {
            this.turn = nextTurn;
            notifyAll();
        }    
        
    }

    public void foo(Runnable printFoo) throws InterruptedException {
        
        for (int i = 0; i < n; i++) {
            printByTurn(printFoo, Turn.TurnFoo, Turn.TurnBar);
        }
    }

    public void bar(Runnable printBar) throws InterruptedException {
        
        for (int i = 0; i < n; i++) {
            printByTurn(printBar, Turn.TurnBar, Turn.TurnFoo);
        }
    }
}