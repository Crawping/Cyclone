#include "GL/OpenGL.h"
#include "Pipelines/RenderStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        template<typename T> RenderStage3D<T>::RenderStage3D()
        {
            RenderStage::Append({ Commands, 0 });
        }



        /** UTILITIES **/
        template<typename T> void RenderStage3D<T>::Append(const T& command)    { Commands.Add(command); }
        template<typename T> void RenderStage3D<T>::ClearBuffers()
        {
            RenderStage::ClearBuffers();
            RenderStage::Append(BufferBinding { Commands, 0 });
        }
        template<typename T> void RenderStage3D<T>::ClearCommands()             { Commands.Clear(); }
        template<typename T> void RenderStage3D<T>::Update()                    { Commands.Update(); }



        /** RENDERING METHODS **/
        template<> void RenderStage3D<DrawCommand>::Render() const
        {
            if (Commands.IsEmpty()) { return; }
            glMultiDrawArraysIndirect(Topology(), 0, Commands.Count(), 0);
        }
        template<> void RenderStage3D<IndexedDrawCommand>::Render() const
        {
            if (Commands.IsEmpty()) { return; }
            glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, Commands.Count(), 0);
        }



        /** EXPLICIT TEMPLATE INSTANTIATIONS **/
        template struct RenderStage3D<DrawCommand>;
        template struct RenderStage3D<IndexedDrawCommand>;

    }
}