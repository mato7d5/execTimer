#include <iostream>
#include <unistd.h>
#include "exec_timer.h"

using namespace std;

void func() {
    met::ExecTimerAuto eta("func", "func()");
    sleep(6);
}

int main() {
    met::ExecTimer e("main_output");

    e.start("sleep(1)");
    sleep(1);
    e.stop("sleep(1)");

    e.start("func()");
    func();
    e.stop("func()");
    e.print();

    return 0;
}

