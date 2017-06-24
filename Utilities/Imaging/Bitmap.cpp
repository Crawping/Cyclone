#include "Utilities.h"
#include "Imaging/Bitmap.h"
#include "Imaging/Color4.h"

#include <cstring>
#include <sstream>



namespace Cyclone
{
    namespace Utilities
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        Bitmap::Bitmap(const Vector3& size)
        {
            Reallocate(size);
        }



        /** UTILITIES **/
        void Bitmap::Fill(const Color4& color)
        {
            _pixels.Fill(color);
        }
        string Bitmap::Report() const
        {
            std::stringstream msg;
            msg << "Bitmap Pixel Values:\n\n";

            uint area = Width() * Height();
            for (uint a = 0; a < Height(); a++)
                for (uint b = 0; b < Width(); b++)
                    for (uint c = 0; c < Depth(); c++)
                        msg << "\t(" << a << ", " << b << "," << c << "): " << 
                            _pixels( (c * area) + sub2ind(Height(), Width(), a, b) ).ToString() << "\n";

            msg << "\n";
            return msg.str();
        }



        /** PROTECTED UTILITIES **/
        void Bitmap::Reallocate(const Vector3& size)
        {
            _size = size;
            uint npixels = Width() * Height() * Depth();
            _pixels = Vector<Color4>(npixels);
        }



        /** OPERATORS **/
        Color4& Bitmap::operator ()(uint index)                     { return _pixels(index); }
        const Color4& Bitmap::operator ()(uint index)               const { return _pixels(index); }
        Color4& Bitmap::operator ()(uint a, uint b, uint c)
        {
            int idx = (c * Height() * Width()) + sub2ind(Height(), Width(), a, b);
            return _pixels(idx);
        }
        const Color4& Bitmap::operator ()(uint a, uint b, uint c)   const
        {
            int idx = (c * Height() * Width()) + sub2ind(Height(), Width(), a, b);
            return _pixels(idx);
        }

    }
}
