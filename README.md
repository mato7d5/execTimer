#ExecTimer

**ExecTimer** is simple utility class for measurement time of code execution. Time is measured in microseconds.
Usage is very simple. Just include header file exec_timer.h into your source code file.

exec_timer.h defines two classes (in *met* namespace):
    * ExecTimer
    * ExecTimerAuto

## ExecTimer
Usage is very easy. Declare variable of type *ExecTimer*. Constructor takes one string paramater which defines the name of
output file. Start of measurement time is done by calling of *start* method with one string parameter for naming section.
At the end of section call *stop* method with same string parameter as start method was.
Results are saved by calling *print* method.

Sample:
```
met::ExecTimer et("results");
et.start("section1");
...
...
...
et.stop("section1");
et.print();
```

## ExecTimerAuto
Same, usage is very easy. It measures execution time from place where variable of this type was declared to the end of the block.
Constructor takes two string parameters. First one is name of output file and second one name of block/section.

Sample:
```
void foo() {
    met::ExecTimer("foo", "foo");
    ...
    ...
}
```
