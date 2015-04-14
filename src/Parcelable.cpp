#include <string.h>
#include <string>
#include "../include/Parcelable.hpp"

namespace clusterer
{
namespace backend
{

Parcelable::~Parcelable()
{

}

ParcelAllocator::ParcelAllocator()
{

}

void ParcelAllocator::reserve(const Parcelable& parcelable)
{

}

void ParcelAllocator::reserve(const std::string& str)
{

}

size_t ParcelAllocator::getSize() const
{
    return _size;
}


ParcelEncoder::ParcelEncoder(const ParcelAllocator& allocator)
{

}

ParcelEncoder::~ParcelEncoder()
{

}


void ParcelEncoder::encode(const Parcelable& parcelable)
{

}


void ParcelEncoder::encode(const std::string& str)
{

}


const char* ParcelEncoder::getData() const
{
    return _data;
}


size_t ParcelEncoder::getSize() const
{
    return _size;
}

ParcelEncoder::ParcelEncoder(const ParcelEncoder&)
{

}

const ParcelEncoder& ParcelEncoder::operator=(const ParcelEncoder& x)
{
    return *this;
}


ParcelDecoder::ParcelDecoder(const char* data, size_t size)
{

}

void ParcelDecoder::decode(Parcelable* parcelable)
{

}


void ParcelDecoder::decode(std::string* str)
{

}

}
}
