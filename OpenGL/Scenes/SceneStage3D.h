/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "GraphicsSettings.h"
#include "TypeDefinitions.h"
#include "Collections/List.h"
#include "Interfaces/IScene.h"
#include "Scenes/RenderStage3D.h"
#include "Scenes/Scene3D.h"
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {
        struct BufferIndices;



        class SceneStage3D : public virtual ISceneStage
        {
            public:

                /** PROPERTIES **/
                OpenGLAPI virtual List<const IRenderStage&> Stages()    const override;

                const string& Name()                                    const override { return _name; }
                bool NeedsUpdate()                                      const override { return _needsUpdate; }
                const GraphicsSettings& Settings()                      const override { return Stage.Settings(); }

                SceneStage3D& Name(const string& value)                 { _name = value; return *this; }
                SceneStage3D& Settings(const GraphicsSettings& value)   
                {
                    IndexedStage.Settings(value);
                    Stage.Settings(value);
                    return *this;
                }



                /** CONSTRUCTOR **/
                OpenGLAPI SceneStage3D(const string& name = "");
                virtual ~SceneStage3D() { }



                /** UTILITIES **/
                OpenGLAPI void Add(const BufferIndices& indices);
                OpenGLAPI bool Contains(const BufferIndices& indices) const;
                OpenGLAPI void Remove(const BufferIndices& indices);
                OpenGLAPI void Update() override;

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                bool                _needsUpdate;
                string              _name;



                /** COLLECTIONS **/
                std::set<const BufferIndices*>      EntityIndices;
                RenderStage3D<IndexedDrawCommand>   IndexedStage;
                RenderStage3D<DrawCommand>          Stage;
        };
    }
}
