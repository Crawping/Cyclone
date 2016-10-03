#include "Bitmap.h"
#include "Color4.h"
#include "Console.h"
#include "Utilities.h"
#include "Imaging/Color4.h"

#include <cstring>
#include <sstream>



namespace Cyclone
{
    namespace Utilities
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        Bitmap::Bitmap(Bitmap&& other) :
            _size(other.Size()),
            Pixels(other.Pixels)
        {
            other.Pixels = nullptr;
        }
        Bitmap::Bitmap(const Vector2& size) :
            _size(size),
            Pixels(nullptr)
        {
            Allocate(size);
        }
        Bitmap::Bitmap(const Bitmap& other) :
            _size(other.Size()),
            Pixels(nullptr)
        {
            Allocate(Size());
            std::memcpy(Pixels, other.Pixels, Height() * Width() * sizeof(Color4));
        }
        Bitmap::~Bitmap()
        {
            if (Pixels)
                delete[] Pixels;
        }



        /** UTILITIES **/
        Bitmap& Bitmap::Allocate(const Vector2& size)
        {
            if (Pixels)
                delete[] Pixels;

            _size = size;
            Pixels = new Color4[Width() * Height()];
            return *this;
        }
        Bitmap& Bitmap::Fill(const Color4& color)
        {
            for (uint a = 0; a < Length(); a++)
                Pixels[a] = color;
            return *this;
        }
        string Bitmap::Report() const
        {
            std::stringstream msg;
            msg << "Bitmap Pixel Values:\n\n";

            for (uint a = 0; a < Height(); a++)
                for (uint b = 0; b < Width(); b++)
                    msg << "\t(" << a << ", " << b << "): " << Pixels[sub2ind(Height(), Width(), a, b)].ToString() << "\n";

            msg << "\n";
            return msg.str();
        }



        /** OPERATORS **/
        Color4& Bitmap::operator ()(uint a, uint b)
        {
            int idx = sub2ind(Height(), Width(), a, b);
            return Pixels[idx];
        }
        Bitmap& Bitmap::operator =(Bitmap& other)
        {
            _size = other._size;
            Allocate(Size());
            std::memcpy(Pixels, other.Pixels, Height() * Width() * sizeof(Color4));
            return *this;
        }
        Bitmap& Bitmap::operator =(Bitmap&& other)
        {
            std::swap(_size, other._size);
            std::swap(Pixels, other.Pixels);
            return *this;
        }

    }
}
