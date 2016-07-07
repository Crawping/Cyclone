/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "GraphicsBuffer.h"



template<typename T>
class UniformBuffer : public GraphicsBuffer<T>
{

    public:

        /** CONSTRUCTOR & DESTRUCTOR **/
        UniformBuffer() : GraphicsBuffer<T>(BufferTypes::Uniform) { }
        ~UniformBuffer() { }

};

