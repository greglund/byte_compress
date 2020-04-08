Testing
############

A number of tests were performed to ensure the solution encoded input to compressed data well.  Additionally, a decompress function was written to ensure original data could be restored back to the uncompressed state from the encoded data.

The testing is done using the Ceedling test framework.  The basic test premises are:

1. Ensure the assignment data is compressible and decompressible
2. Ensure that boundary conditions are tested:

   - No input data
   - Single input data item
   - No consecutive equal data values
   - Long series of consectutive values, with a length greater than 0x7F
   - Invalid input values

Results
-------

The output from running ceedling test suite over the unit tests is as follows:

::

   Test 'test_bytecompress.c'
   --------------------------
   Generating runner for test_bytecompress.c...
   Compiling test_bytecompress_runner.c...
   Compiling test_bytecompress.c...
   Compiling unity.c...
   Compiling byte_compress.c...
   Compiling byte_decompress.c...
   Compiling cmock.c...
   Linking test_bytecompress.out...
   Running test_bytecompress.out...

   -----------
   TEST OUTPUT
   -----------
   [test_bytecompress.c]
     - "New size: 16"

   --------------------
   OVERALL TEST SUMMARY
   --------------------
   TESTED:  9
   PASSED:  9
   FAILED:  0
   IGNORED: 0


SOURCE
------

test_bytecompress.c
___________________

.. literalinclude:: test_bytecompress.c
   :linenos:
   :language: c

byte_decompress API
___________________

.. doxygenfunction:: byte_decompress


byte_decompress.c
___________________


.. literalinclude:: byte_decompress.c
   :linenos:
   :language: c
