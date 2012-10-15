Running C++ Tests
=================

The project in the `tests` subfolder contains a testsuite
using google test. To run it, simply execute the `dnd_tests`
executable. Here's how that looks on Windows:


    D:\Develop\dynamicndarray\build\tests\RelWithDebInfo>dnd_tests.exe
    Running main() from gtest_main.cc
    [==========] Running 83 tests from 23 test cases.
    [----------] Global test environment set-up.
    [----------] 1 test from CodeGenCache
    [ RUN      ] CodeGenCache.UnaryCaching
    [       OK ] CodeGenCache.UnaryCaching (0 ms)
    [----------] 1 test from CodeGenCache (1 ms total)

    [----------] 2 tests from UnaryKernelAdapter
    [ RUN      ] UnaryKernelAdapter.BasicOperations

    <snip>

    [       OK ] UnaryKernel.Specialization (0 ms)
    [----------] 1 test from UnaryKernel (0 ms total)

    [----------] Global test environment tear-down
    [==========] 83 tests from 23 test cases ran. (287 ms total)
    [  PASSED  ] 83 tests.

If you want to see what options there are for running tests,
run `dnd_tests --help`. One useful ability is to filter tests
with a white or black list.

    D:\Develop\dynamicndarray\build\tests\RelWithDebInfo>dnd_tests.exe --gtest_filter=DType.*
    Running main() from gtest_main.cc
    Note: Google Test filter = DType.*
    [==========] Running 2 tests from 1 test case.
    [----------] Global test environment set-up.
    [----------] 2 tests from DType
    [ RUN      ] DType.BasicConstructor
    [       OK ] DType.BasicConstructor (0 ms)
    [ RUN      ] DType.SingleCompare
    [       OK ] DType.SingleCompare (1 ms)
    [----------] 2 tests from DType (2 ms total)

    [----------] Global test environment tear-down
    [==========] 2 tests from 1 test case ran. (6 ms total)
    [  PASSED  ] 2 tests.

One useful option is to disable googletest's catching of exceptions,
with the option `--gtest_catch_exceptions=0`. This allows your debugger
to handle it.

To generate Jenkins-compatible XML output, use `dnd_tests --gtest_output=xml:dnd_tests.xml`.

Running Python Tests
====================

The Python tests are written using Python's built in unittest module,
and can either be run by executing the scripts or with nose. To run
a test script directly, simply execute the test .py file:

    D:\Develop\dynamicndarray>python python\pydnd\tests\test_dtype.py
    ........
    ----------------------------------------------------------------------
    Ran 8 tests in 0.006s

    OK

To use nose, execute the following:

    D:\Develop\dnd\dynamicndarray>nosetests python\pydnd\tests
    ........................
    ----------------------------------------------------------------------
    Ran 24 tests in 0.119s

    OK

To generate Jenkins-compatible XML output, use
`nosetests --with-xunit --xunit-file=pydnd_tests.xml python/pydnd/tests`.