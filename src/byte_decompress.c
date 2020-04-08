
#include "byte_decompress.h"


int byte_decompress(const char* data_ptr, int data_size, char* out, int output_size_max)
{
   int size = 0, count = 0, i;

   while (data_size--) {
      if ((*data_ptr & 0x80) && (data_size != 0)) {
         count = (unsigned char) *data_ptr & 0x7F;
         data_ptr++;
         data_size--;
      } else {
         count = 1;
      }

      for (i = 0; i < count; i++) {
         if (size < output_size_max)
            *out++ = *data_ptr;

         size++;
      }

      data_ptr++;
   }

   return size;
}

