
#include <stdint.h>
#include <stdio.h>
#include <string.h>


//-- unity: unit test framework
#include "unity.h"
 
//-- module being tested
#include "byte_compress.h" 
 

// Sample data for compression
static const uint8_t test_data_ptr[] = { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
 0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };

// Expected output after encoding
static const uint8_t test_data_expected[] = { 0x03, 0x74, 0x83, 0x04, 0x82, 0x35, 0x84, 0x64, 0x85, 0x00, 0x56, 0x45, 0x83, 0x56, 0x83, 0x09 };

// Data where subsequent bytes are not equal; therefore
// no compression is expected and it should remain
// unchanged in the output
static const uint8_t test_data_no_compression[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Upon compressing an input array with 128 of the same value "0x35" 
// we expect the count be encoded at its maximum and then continue encoding normally again.
static const uint8_t test_data_overflow_count_expected[] = {0xFF, 0x35, 0x35};


void test_byte_compress(void)
{
   int new_size;
   uint8_t data_ptr[sizeof(test_data_ptr)];

   memcpy(data_ptr, test_data_ptr, sizeof(data_ptr));
   new_size = byte_compress(data_ptr, sizeof(data_ptr));
   printf("New size: %i\r\n", new_size);
   TEST_ASSERT_EQUAL((int) sizeof(test_data_expected), new_size);
   TEST_ASSERT_EQUAL_UINT8_ARRAY(test_data_expected, data_ptr, sizeof(test_data_expected));
}

void test_byte_compress_no_compression(void)
{
   int new_size;
   uint8_t data_ptr[sizeof(test_data_no_compression)];

   memcpy(data_ptr, test_data_no_compression, sizeof(data_ptr));
   new_size = byte_compress(data_ptr, sizeof(data_ptr));
   TEST_ASSERT_EQUAL((int) sizeof(test_data_no_compression), new_size);
   TEST_ASSERT_EQUAL_UINT8_ARRAY(test_data_no_compression, data_ptr, sizeof(test_data_no_compression));
}

void test_byte_compress_count_overflow(void)
{
   int new_size;
   uint8_t data_ptr[128];

   memset(data_ptr, 0x35, sizeof(data_ptr));
   new_size = byte_compress(data_ptr, sizeof(data_ptr));
   TEST_ASSERT_EQUAL((int) sizeof(test_data_overflow_count_expected), new_size);
   TEST_ASSERT_EQUAL_UINT8_ARRAY(test_data_overflow_count_expected, data_ptr, sizeof(test_data_overflow_count_expected));
}

void test_byte_decompress(void)
{
   int new_size;
   uint8_t data_out[sizeof(test_data_ptr)];

   new_size = byte_decompress(test_data_expected, sizeof(test_data_expected), data_out, sizeof(data_out));
   TEST_ASSERT_EQUAL((int) sizeof(test_data_ptr), new_size);
   TEST_ASSERT_EQUAL_UINT8_ARRAY(test_data_ptr, data_out, sizeof(test_data_ptr));
}

void test_byte_decompress_count_max(void)
{
   int new_size;
   uint8_t data_expected[128];
   uint8_t data_out[128];

   memset(data_expected, 0x35, sizeof(data_expected));
   memset(data_out, 0, sizeof(data_out));
   new_size = byte_decompress(test_data_overflow_count_expected, sizeof(test_data_overflow_count_expected), data_out, sizeof(data_out));
   TEST_ASSERT_EQUAL((int) sizeof(data_expected), new_size);
   TEST_ASSERT_EQUAL_UINT8_ARRAY(data_expected, data_out, sizeof(data_expected));
}

