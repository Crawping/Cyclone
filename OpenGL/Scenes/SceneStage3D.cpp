#include "Scenes/SceneStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        List<const IRenderStage&> SceneStage3D::Stages() const
        {
            return List<const IRenderStage&>();
            //return
            //{ 
            //    IndexedStage, 
            //    RenderStage,
            //};
        }



        /** CONSTRUCTOR **/
        SceneStage3D::SceneStage3D(const string& name) :
            _isVisible(true),
            _needsUpdate(false),
            _name(name)
        {

        }



        /** UTILITIES **/
        void SceneStage3D::Add(const BufferIndices& indices)
        {
            if (Contains(indices)) { return; }
            EntityIndices.Insert(&indices);
            _needsUpdate = true;
        }
        bool SceneStage3D::Contains(const BufferIndices& indices) const
        {
            return EntityIndices.Contains(&indices);
        }
        void SceneStage3D::Remove(const BufferIndices& indices)
        {
            if (!Contains(indices)) { return; }
            EntityIndices.Remove(&indices);
            _needsUpdate = true;
        }
        void SceneStage3D::Update()
        {
            if (!NeedsUpdate()) { return; }

            IndexedStage.ClearCommands();
            Stage.ClearCommands();

            for (const BufferIndices* ids : EntityIndices)
                if (ids->IndicesCount)
                    IndexedStage.Add(IndexedDrawCommand(ids->IndicesCount, 1, ids->IndicesIndex, ids->VertexIndex, ids->EntityIndex));
                else
                    Stage.Add(DrawCommand(ids->VertexCount, 1, 0, ids->VertexIndex, ids->EntityIndex));

            IndexedStage.Update();
            Stage.Update();

            _needsUpdate = false;
        }

    }
}