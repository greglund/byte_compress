
#include "byte_compress.h"

#include <stdint.h>


#define BYTE_COMPRESS_OUT \
   if (count > 1) \
   { \
      *out++ = 0x80 | count; \
      size++; \
   } \
   \
   *out++ = val; \
   size++;

int byte_compress(uint8_t* data_ptr, int data_size)
{
   uint8_t* out;
   int index;
   int size;
   int count;
   uint8_t val;

   if (data_size == 0)
      return 0;

   if (*data_ptr & 0x80)
      return -1;  // Invalid value in 1st item

   out = data_ptr;
   val = *data_ptr++;
   size = 0;
   index = 1;
   count = 1;

   while (--data_size)
   {
      if (*data_ptr & 0x80)
      {
         BYTE_COMPRESS_OUT
         return -(index + 1); // Invalid value in nth item
      }

      if ((*data_ptr != val) ||
            (count == 0x7F)) // Ensure the count does not overflow
      {
         // Output the count and value, begin counting again.
         BYTE_COMPRESS_OUT
         count = 0;
         val = *data_ptr;
      }

      data_ptr++;
      index++;
      count++;
   }

   BYTE_COMPRESS_OUT
   return size;
}

