                     Model Checking and System Verification
                               CMI, Jan-Apr 2017

                       CUDD: CU Decision Diagram Package

* Compiling CUDD package
    1. Extract `cudd-3.0.0.tar.gz`.
        tar -xzf cudd-3.0.0.tar.gz

    2. Enter the extracted directory.
        cd cudd-3.0.0

    3. Get ready for compilation
        ./configure --enable-shared --enable-obj --enable-dddmp

    4. Compile
        make

    5. Test if everything okay (optional)
        make check


* Compiling CUDD code
    1. Edit given `Makefile` such that `CUDD_ROOT` is set to correct value.

    2. Add CUDD library path to `LD_LIBRARY_PATH`.
        # change `CUDD_ROOT` to correct value
        export LD_LIBRARY_PATH=CUDD_ROOT/cudd/.libs:$LD_LIBRARY_PATH

    2. If the filename is `foo.c`, run `make foo`. It will build the executable.

    3. To visualize the `dot` file, GraphViz must be installed.
       To create a PDF of the graph, run
        dot -Tpdf -O DOT_FILE
