
#if !defined(BYTE_COMPRESS_H_)
#define BYTE_COMPRESS_H_

#include <stdint.h>


#if defined(__cplusplus)
extern "C"
{
#endif

/// Compress an array of bytes.
/// Assumptions:
/// 1) incoming bytes will only have values between 0x0 and 0x7F
/// 2) byte values are likely repeated sequencially
///
/// Simple compression scheme:
/// A single byte will be placed into the output, unencoded. 
/// Multiple bytes: Encode byte count ORed with 0x80, followed by 
/// the byte value
///
/// Note that a byte value exceeding 0x7F in the input stream will
/// cause the function to return prematurely.
/// 
/// @param data_ptr IN Pointer to data to be compressed
///                 OUT Pointer to compressed data
/// @param data_size Size of the input data
/// @return Compressed data size if successful.  Otherwise, the
/// negative (offset + 1) at which an error occurred.
int byte_compress(uint8_t* data_ptr, int data_size);

#if defined(__cplusplus)
}
#endif

#endif // !defined(BYTE_COMPRESS_H_)

