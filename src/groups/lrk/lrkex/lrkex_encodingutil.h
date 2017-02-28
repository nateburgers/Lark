// lrkex_encodingutil.h                                               -*-C++-*-
#ifndef INCLUDED_LRKEX_ENCODINGUTIL
#define INCLUDED_LRKEX_ENCODINGUTIL

//@PURPOSE:
//
//@TYPES:
//
//@SEE_ALSO:
//
//@DESCRIPTION:
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

#ifndef INCLUDED_LRKP_BYTE
#include <lrkp_byte.h>
#endif

#ifndef INCLUDED_LRKP_CHARACTER
#include <lrkp_character.h>
#endif

#ifndef INCLUDED_LRKP_INTEGER
#include <lrkp_integer.h>
#endif

#ifndef INCLUDED_LRKP_NATURAL
#include <lrkp_natural.h>
#endif

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif


namespace LarkCompiler {
namespace lrkex {

enum BufferMode {
    e_READ,
    e_WRITE,

    k_NUM_ENUMERATORS,
};

struct Buffer {
    // TODO(nate): should be protocolized, ie, should also have a 'TestBuffer'
    //             class.

    BufferMode     d_mode;
    lrkp::Byte    *d_bufferBegin_p;
    lrkp::Byte    *d_bufferEnd_p;
    lrkp::Byte    *d_bufferPosition_p;
    // d_allocator_p

    lrkp::Size read(lrkp::Byte *byte);

    lrkp::Size read(lrkp::Byte  bytes[],
                    lrkp::Size  numBytes);

    void write(lrkp::Byte byte);

    void write(const lrkp::Byte bytes[],
               lrkp::Size       numBytes);

    void setMode(BufferMode mode);

    BufferMode mode() const;

    lrkp::Size size() const;
};

struct EncodingUtil {

                                  // Bridging

    template <typename VALUE_TYPE>
    static lrkp::Boolean bridge (Buffer     *buffer,
                                 VALUE_TYPE *value);

    static lrkp::Boolean bridge (Buffer        *buffer,
                                 lrkp::Boolean *value);

                                  // Encoding

    template <typename VALUE_TYPE>
    static void encode(Buffer       *buffer,
                       VALUE_TYPE&&  value);

    static void encode(Buffer        *buffer,
                       lrkp::Boolean  boolean);

    static void encode(Buffer        *buffer,
                       lrkp::Integer  integer);

                                  // Decoding

    template <typename VALUE_TYPE>
    static lrkp::Boolean decode(VALUE_TYPE *output,
                                Buffer     *buffer);

    static lrkp::Boolean decode(lrkp::Boolean *output,
                                Buffer        *buffer);

    static lrkp::Boolean decode(lrkp::Integer *output,
                                Buffer        *buffer);

};

struct Encoder {

    Buffer        *d_buffer_p;
    lrkp::Boolean  d_valid;

    Encoder(Buffer *buffer)
        : d_buffer_p(buffer)
        , d_valid(true)
    {
    }

    lrkp::Boolean isValid() const
    {
        return d_valid;
    }

    template <typename DATA_MEMBER_TYPE>
    void bridge(DATA_MEMBER_TYPE& data)
    {
        if (d_valid) {
            d_valid = EncodingUtil::bridge(d_buffer_p, &data);
        }
    }

    template <typename    FIRST_DATA_MEMBER_TYPE,
              typename... OTHER_DATA_MEMBER_TYPES>
    void bridge(FIRST_DATA_MEMBER_TYPE&     firstData,
                OTHER_DATA_MEMBER_TYPES&... otherData)
    {
        bridge(firstData);
        bridge(otherData...);
    }
};

struct Point {

    void bridge(Encoder *encoder)
    {
        encoder->bridge(d_x, d_y);
    }

    lrkp::Boolean d_x;
    lrkp::Boolean d_y;
};


// LOCAL FUNCTIONS
template <typename FUNDAMENTAL_TYPE>
static lrkp::Boolean bridgeFundamental (Buffer           *buffer,
                                        FUNDAMENTAL_TYPE *value)
{
    static_assert(2 == BufferMode::k_NUM_ENUMERATORS);
    switch (buffer->mode()) {
        case BufferMode::e_READ: {
            return EncodingUtil::decode(value, buffer);
        } break;
        case BufferMode::e_WRITE: {
            EncodingUtil::encode(buffer, *value);
            return true;
        } break;
        default: {
            // TODO(nate): assert that this is not possible.
            return false;
        } break;
    }
}

                                  // Bridging

template <typename VALUE_TYPE>
lrkp::Boolean EncodingUtil::bridge (Buffer     *buffer,
                                    VALUE_TYPE *value)
{
    // TODO(nate): statically assert that it has this bridging concept;

    Encoder encoder(buffer);
    value->bridge(&encoder);
    return encoder.isValid();
}

lrkp::Boolean EncodingUtil::bridge (Buffer        *buffer,
                                    lrkp::Boolean *value)
{
    return bridgeFundamental(buffer, value);
}

                                  // Encoding

template <typename VALUE_TYPE>
void EncodingUtil::encode(Buffer       *buffer,
                          VALUE_TYPE&&  value)
{
    bridge(buffer, &value);
    // TODO(nate): assert that the returned status is success.
}

void EncodingUtil::encode(Buffer        *buffer,
                          lrkp::Boolean  boolean)
{
    buffer->write(boolean);
}

void EncodingUtil::encode(Buffer        *buffer,
                          lrkp::Integer  integer)
{
    lrkp::Byte byte0 = (integer >>  0) & 0xFF;
    lrkp::Byte byte1 = (integer >>  8) & 0xFF;
    lrkp::Byte byte2 = (integer >> 16) & 0xFF;
    lrkp::Byte byte3 = (integer >> 24) & 0xFF;
    lrkp::Byte byte4 = (integer >> 32) & 0xFF;
    lrkp::Byte byte5 = (integer >> 40) & 0xFF;
    lrkp::Byte byte6 = (integer >> 48) & 0xFF;
    lrkp::Byte byte7 = (integer >> 56) & 0xFF;

    lrkp::Byte bytes[] = {
        byte0, byte1, byte2, byte3,
        byte4, byte5, byte6, byte7,
    };

    buffer->write(bytes, 8);
}


                                  // Decoding

template <typename VALUE_TYPE>
lrkp::Boolean EncodingUtil::decode(VALUE_TYPE *output,
                                   Buffer     *buffer)
{
    return bridge(buffer, output);
}

lrkp::Boolean EncodingUtil::decode(lrkp::Boolean *output,
                                   Buffer        *buffer)
{
    lrkp::Byte byte;
    lrkp::Size numBytesRead = buffer->read(&byte);

    if (1 != numBytesRead) {
        return false;
    }

    if (byte != 0 || byte != 1) {
        return false;
    }

    *output = byte;
    return true;
}

} // close product namespace
} // close package namespace

#endif // INCLUDED_LRKEX_ENCODINGUTIL
