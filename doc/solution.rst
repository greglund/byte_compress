The Solution
############

Since it is assumed that the in type of data to be compressed, it is common to have the same value repeated in the series, a simple encoding scheme can be used to note the byte occurrence count followed by the byte value. Additionally, since it is assumed that all data can be represented in the range 0x0 to 0x7F, the count byte can be encoded by ORing the count with 0x80.  Finally, if a byte value only occurs once consecutively, it is unnecessary and actually significantly inefficient to require a preceding count byte in the output--In the worst case where there are no consecutive equal byte values in the input, the output would double in size.

With the chosen simple encoding scheme, the worst case scenario is that the output data will be identical to the input data if there are no consecutive equal byte values.  Conversely, a single value repeated many times will be significantly compressed.

A handful of other details have been considered in this solution:

- The maximum number of consecutive equal byte values that can be encoded is 0x7F.  If there are more, they will need to be encoded in subsequent output.
- If a value > 0x7F is found in the input, the encoding will stop with an error code explained in the API

Conclusion
----------

The compression encoding scheme is able to successfully compress data with consecutively occurring equal bytes.  The sample data given was compressed from 24 bytes to 16 bytes.

The byte_compress function is implemented in C.  Here is the API:

API
---

.. doxygenfunction:: byte_compress


SOURCE
------

byte_compress.c
_______________

.. literalinclude:: byte_compress.c
   :linenos:
   :language: c



