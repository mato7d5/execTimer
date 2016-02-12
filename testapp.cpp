#include <iostream>
#include <unistd.h>
#include <string>
#include "exec_timer.h"

using namespace std;

void func() {
    met::ExecTimerAuto eta("func", "func()");
    sleep(6);
}

void func2() {
    MET_BENCHMARK_CREATE(FUNC2)
    MET_BENCHMARK_START(FUNC2, section1);

     for (int i = 0; i < 5; ++i) {
        MET_BENCHMARK_SCOPE(FUNC2, i)
        sleep(1);
    }

    MET_BENCHMARK_STOP(FUNC2, section1)
    MET_BENCHMARK_PRINT(FUNC2)
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

    func2();

    return 0;
}

