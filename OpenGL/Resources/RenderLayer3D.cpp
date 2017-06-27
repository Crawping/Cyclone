#include "Geometry/Entity3D.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/ITexture.h"
#include "Resources/RenderLayer3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** UTILITIES **/
        void RenderLayer3D::Insert(const Resource<IRenderable>& entity)
        {
            RenderLayer::Insert(entity);

            const Resource<Entity3D>& entity3D = entity;
            if (!entity3D.IsNull())
                Insert(entity3D->Model()->Geometry());
        }
        void RenderLayer3D::Insert(const Resource<IGeometric>& geometry)
        {
            if (geometry.IsNull() || Contains(geometry)) { return; }
            uint gID = geometry.ID();
            _keys.Insert(gID, BufferIndices());
            _mapping.Insert(gID, _geometry.Count());
            _geometry.Append(geometry);
            Invalidate(gID);
        }
        void RenderLayer3D::Update()
        {
            RenderLayer::Update();

            for (uint a = _invalidRange(0); a < _invalidRange(1); a++)
                UpdateGeometryData(_geometry(a));
            
            _invalidRange = { _geometry.Count(), 0 };
            _vertices.Update();
        }
        void RenderLayer3D::Update(const Resource<IGeometric>& geometry)
        {
            if (!Contains(geometry)) { return; }
            uint idxG = _mapping[geometry.ID()];
            auto& keys = _keys(idxG);

            bool sameSize =
                (geometry->IndexCount() == keys.IndicesCount) &&
                (geometry->PointCount() == keys.VertexCount);

            if (sameSize)   { Invalidate(geometry.ID()); }
            else            { InvalidateAll(geometry.ID()); }
        }



        /** PRIVATE UTILITIES **/
        bool RenderLayer3D::Contains(const Resource<IGeometric>& geometry)  const
        {
            return _mapping.Contains(geometry.ID());
        }
        void RenderLayer3D::Invalidate(uint geometry)
        {
            uint index = _mapping[geometry];
            _invalidRange = 
            { 
                Math::Min(_invalidRange(0), index), 
                Math::Max(_invalidRange(1), index + 1),
            };
        }
        void RenderLayer3D::InvalidateAll(uint geometry)
        {
            uint index = _mapping[geometry];
            _invalidRange =
            {
                Math::Min(_invalidRange(0), index),
                _geometry.Count(),
            };
        }
        void RenderLayer3D::UpdateGeometryData(const Resource<IGeometric>& geometry)
        {
            uint idxData = _mapping[geometry.ID()];
            BufferIndices& data = _keys(idxData);

            data.IndicesCount = geometry->IndexCount();
            data.VertexCount = geometry->PointCount();

            if (idxData > 0)
            {
                const auto& ltData = _keys(idxData - 1);
                data.IndicesIndex = ltData.IndicesIndex + ltData.IndicesCount;
                data.VertexIndex = ltData.VertexIndex + ltData.VertexCount;
            }
            else
            {
                data.IndicesIndex = 0;
                data.VertexIndex = 0;
            }

            if (data.IndicesCount)
                _vertices.Set(data.IndicesIndex, geometry->Indices());

            if (data.VertexCount)
                _vertices.Set(data.VertexIndex, geometry->Vertices());
        }

    }
}