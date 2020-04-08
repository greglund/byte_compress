
#include "byte_compress.h"

#include <stdint.h>


int byte_compress(uint8_t* data_ptr, int data_size)
{
   uint8_t* out = data_ptr;
   uint8_t val = 0xFF;
   int count = 0;
   int size = 0;

   while (data_size--)
   {
      if (*data_ptr >= 0x80)
         return -(size + 1);

      if ((*data_ptr != val) || (count == 0x7F))
      {
         if (val != 0xFF)
         {
            if (count > 1)
            {
               *out++ = 0x80 | count;
               size++;
            }

            *out++ = val;
            size++;
            count = 0;
         }

         val = *data_ptr;
      }

      count++;
      data_ptr++;
   }

   if (val != 0xFF)
   {
      if (count > 1)
      {
         *out++ = 0x80 | count;
         size++;
      }

      *out = val;
      size++;
   }

   return size;
}

int byte_decompress(const uint8_t* data_ptr, int data_size, uint8_t* out, int output_size_max)
{
   int size = 0;
   int count = 0;
   int i;

   while (data_size--)
   {
      if ((*data_ptr & 0x80) && (data_size != 0))
      {
         count = *data_ptr & 0x7f;
         data_ptr++;
         data_size--;
      }
      else
      {
         count = 1;
      }

      for (i = 0; i < count; i++)
      {
         if (size < output_size_max)
            *out++ = *data_ptr;

         size++;
      }

      data_ptr++;
   }

   return size;
}

