/* CHANGELOG
 * Written by Josh Grooms on 20161222
 */

#pragma once
#include "Scenes/SceneStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class StageGroup3D
        {
            public:

                /** PROPERTIES **/
                OpenGLAPI List<IRenderStage&> Stages() const;

                const string& Name()                    const { return _name; }
                const GraphicsSettings& Settings()      const { _settings; }

                OpenGLAPI StageGroup3D& Name(const string& value);
                OpenGLAPI StageGroup3D& Settings(const GraphicsSettings& value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI StageGroup3D(const string& name = "");
                OpenGLAPI virtual ~StageGroup3D() { }


                
                /** UTILITIES **/
                OpenGLAPI void Add(VertexTopologies topology, const BufferIndices& indices);
                OpenGLAPI void Remove(VertexTopologies topology, const BufferIndices& indices);
                OpenGLAPI void Update();

            private:

                bool                _isVisible;
                string              _name;
                GraphicsSettings    _settings;

                BST<VertexTopologies, SceneStage3D*>   _stages;

        };
    }
}
