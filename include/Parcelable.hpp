/**
  * @brief  Parcelable interface for serialization
  *
  * @file   Parcelable.hpp
  *
  */

#ifndef CLUSTERER_BACKEND_PARCELABLE_HPP
#define CLUSTERER_BACKEND_PARCELABLE_HPP

// standard headers
#include <string.h>
#include <string>

/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace backend
* @brief The namespace backend is the namespace for all backend components of the
* project.
*/
namespace backend
{

class ParcelEncoder;
class ParcelDecoder;

/**
 * @class Parcelable
 * @brief an interface for serializable classes
 */
class Parcelable
{
    public:
        /**
         * @brief get size of the current parcelable structure
         * @return the size of current parcelable structure
         */
        virtual const size_t getParcelableSize() = 0;
        /**
         * @brief deciding which fields to encode
         * @param encoder the encoder which will store the serialized fields
         */
        virtual void writeToParcel(ParcelEncoder* encoder) const = 0;
        /**
         * @brief read a parcelable structure back from its serialization
         * @param decoder the decoder which will decode the serialized fields
         */
        virtual void readFromParcel(ParcelDecoder* decoder) = 0;

        virtual ~Parcelable();
};

class ParcelAllocator
{
    public:
        ParcelAllocator();

        /**
         * @brief reserve space
         * @param parcelable the parcelable we want to reserve
         */
        void reserve(const Parcelable& parcelable);
        /**
         * @brief reserve space
         * @param str the string for which we want to reserve space
         */
        void reserve(const std::string& str);
        /**
         * @brief get the current size reserved by this allocator
         * @return the current reserved size
         */
        size_t getSize() const;

    private:
        size_t _size;
};

/**
 * @class ParcelEncoder
 * @brief class capable of serializing Parcelable objects
 */
class ParcelEncoder
{
    public:
        /**
         * @brief construct a ParcelEncoder backed by an allocator
         * @param allocator the backing allocator for the new ParcelEncoder
         */
        explicit ParcelEncoder(const ParcelAllocator& allocator);

        /**
         * @brief destructor to free up internal buffers
         */
        ~ParcelEncoder();

        /**
         * @brief encode an arbitrary Parcelable using the Parcelable interface
         * @param parcelable the Parcelable to encode
         */
        void encode(const Parcelable& parcelable);
        /**
         * @brief encode an STL string
         * @param str the string to encode
         */
        void encode(const std::string& str);

        /**
         * @brief obtain a pointer to the serialized data
         * @return pointer to the serialized data
         */
        const char* getData() const;
        /**
         * @brief get size of the serialized data until now
         * @return number of bytes of data serialized
         */
        size_t getSize() const;

    private:
        size_t _size;
        char* _data;
        char* _curr;

        ParcelEncoder(const ParcelEncoder&);
        const ParcelEncoder& operator=(const ParcelEncoder&);
};

/**
 * @class ParcelDecoder
 * @brief class capable of restoring serialized objects
 */
class ParcelDecoder
{
    public:
        /**
         * @brief create a decoder from serialized data
         * @param data a pointer to the serialized data
         * @param the number of bytes of serialized data
         */
        ParcelDecoder(const char* data, size_t size);

        /**
         * @brief decode and store into parcelable
         * @param parcelable Parcelable to store the decoding
         */
        void decode(Parcelable* parcelable);
        /**
         * @brief store serialized data into a STL string
         * @param str string to store the serialized data
         */
        void decode(std::string* str);

    private:
        size_t mSize;
        const char* mData;
        const char* mCurr;
};

}
}

/**
* @namespace clb
* @brief The namespace clb is a namespace alias for the namespace clusterer::backend.
*/
namespace clb = clusterer::backend;

#endif
