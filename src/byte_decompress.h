
#if !defined(BYTE_DECOMPRESS_H_)
#define BYTE_DECOMPRESS_H_

#include <stdint.h>


#if defined(__cplusplus)
extern "C"
{
#endif

/// Decompress an array of bytes encoded as per the compression scheme
/// used for #byte_compress()
///
/// The function will only write up to #output_size_max to the #out
/// parameter.  
///
/// @param data_ptr Pointer to data to be decompressed
/// @param data_size Size of data to be decompressed
/// @param out Pointer to array to hold the output data
/// @param output_size_max Size of the array to hold the output data
/// @return The number total number of bytes that are required to fully
/// decompress the input.
int byte_decompress(const uint8_t* data_ptr, int data_size, uint8_t* out, int output_size_max);

#if defined(__cplusplus)
}
#endif

#endif // !defined(BYTE_DECOMPRESS_H_)

