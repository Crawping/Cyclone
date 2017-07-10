#include "Geometry/Entity3D.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/ITexture.h"
#include "Math/Math.h"
#include "Resources/RenderLayer3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** UTILITIES **/
        const RenderLayer3D::GeometryData& RenderLayer3D::IndexOf(const Resource<IGeometric>& geometry) const
        {
            return _mapping(_geometry.IndexOf(geometry.ID()));
        }
        void RenderLayer3D::Insert(const Resource<IRenderable>& entity)
        {
            RenderLayer::Insert(entity);

            const auto& entity3D = Resource<IRenderable>(entity);
            if (!entity3D.IsNull())
                Insert(entity3D->Model()->Geometry());
        }
        void RenderLayer3D::Insert(const Resource<IGeometric>& geometry)
        {
            if (geometry.IsNull() || Contains(geometry)) { return; }

            uint gID = geometry.ID();
            _geometry.Insert(gID, geometry);
            _vertices.Append(geometry->Indices());
            _vertices.Append(geometry->Vertices());

            uint gIDX = _geometry.IndexOf(gID);
            _mapping.Insert(gIDX, GeometryData{ geometry->IndexCount(), 0U, geometry->PointCount(), 0U });
            Invalidate(gIDX, _geometry.Count());
        }
        void RenderLayer3D::Update()
        {
            RenderLayer::Update();
            if (_updateRange(1) <= _updateRange(0)) { return; }

            for (uint a = _updateRange(0); a < _updateRange(1); a++)
                UpdateGeometryData(a);

            _vertices.Update();
            _updateRange = { _geometry.Count(), 0 };
        }
        void RenderLayer3D::Update(const Resource<IGeometric>& geometry)
        {
            if (!Contains(geometry)) { return; }
            Invalidate(geometry);
        }



        /** PRIVATE UTILITIES **/
        bool RenderLayer3D::Contains(const Resource<IGeometric>& geometry)  const
        {
            return _geometry.Contains(geometry.ID());
        }
        void RenderLayer3D::Invalidate(const Resource<IGeometric>& geometry)
        {
            uint gIDX = _geometry.IndexOf(geometry.ID());
            auto& oldData = _mapping(gIDX);

            bool sizeChanged =
                oldData.IndicesCount != geometry->IndexCount() ||
                oldData.VertexCount != geometry->PointCount();

            if (sizeChanged)    { Invalidate(gIDX, _geometry.Count()); }
            else                { Invalidate(gIDX); }
        }
        void RenderLayer3D::Invalidate(uint index)
        {
            Invalidate(index, index + 1);
        }
        void RenderLayer3D::Invalidate(uint idxA, uint idxB)
        {
            _updateRange = 
            {
                Math::Clamp( Math::Min(_updateRange(0), idxA), 0U, _geometry.Count() ),
                Math::Clamp( Math::Max(_updateRange(1), idxB), 0U, _geometry.Count() ),
            };
        }
        void RenderLayer3D::UpdateGeometryData(uint index)
        {
            const auto& geometry = _geometry(index);
            auto& data = _mapping(index);
            data.IndicesCount = geometry->IndexCount();
            data.VertexCount = geometry->PointCount();

            if (index > 0)
            {
                const auto& ltData = _mapping(index - 1);
                data.IndicesIndex = ltData.IndicesIndex + ltData.IndicesCount;
                data.VertexIndex = ltData.VertexIndex + ltData.VertexCount;
            }
            else
            {
                data.IndicesIndex = 0;
                data.VertexIndex = 0;
            }

            _vertices.Set(data.IndicesIndex, geometry->Indices());
            _vertices.Set(data.VertexIndex, geometry->Vertices());
        }

    }
}