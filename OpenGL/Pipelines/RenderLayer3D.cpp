#include "Geometry/Entity3D.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/ITexture.h"
#include "Pipelines/RenderLayer3D.h"



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
            _data.Insert(geometry.ID(), GeometryData());
            _geometry.Insert(geometry.ID(), geometry);
            _geometryUpdates.Append(geometry);
        }
        void RenderLayer3D::Update()
        {
            RenderLayer::Update();

            auto counts = GatherCounts();
            for (uint a = 0; a < _geometryUpdates.Count(); a++)
            {
                auto& geometry = _geometryUpdates(a);
                GeometryData& data = _data[geometry.ID()];
                uint idxG = _data.IndexOf(geometry.ID());
                
                data.IndicesCount = geometry->IndexCount();
                data.IndicesIndex = counts(idxG).X;
                data.VertexCount = geometry->PointCount();
                data.VertexIndex = counts(idxG).Y;

                if (data.IndicesCount)
                    _indices.Set(data.IndicesIndex, geometry->Indices());
                
                auto& mapping = geometry->Mapping();
                auto& normals = geometry->Normals();
                auto& points = geometry->Points();

                for (uint a = 0; a < points.Count(); a++)
                    _vertices.Append(Vertex(points(a), normals(a), (Vector2)mapping(a)));
            }
            
            _geometryUpdates.Clear();
            _indices.Update();
            _vertices.Update();
        }
        void RenderLayer3D::Update(const Resource<IGeometric>& geometry)
        {
            if (!Contains(geometry)) { return; }
            _geometryUpdates.Append(geometry);

            auto& oldGeometry = _data[geometry.ID()];
            if (oldGeometry.IndicesCount && oldGeometry.IndicesCount != geometry->Count())
                for (uint a = _geometry.IndexOf(geometry.ID()) + 1; a < _geometry.Count(); a++)
                    _geometryUpdates.Append(_geometry(a));
        }



        /** PRIVATE UTILITIES **/
        bool RenderLayer3D::Contains(const Resource<IGeometric>& geometry)  const
        {
            return _geometry.Contains(geometry.ID());
        }
        Vector<Vector2> RenderLayer3D::GatherCounts()                       const
        {
            Vector<Vector2> counts(_geometry.Count() + 1);

            counts(0) = Vector2::Zero;
            for (uint a = 0; a < _geometry.Count(); a++)
                counts(a + 1) = Vector2(counts(a).X + _geometry(a)->IndexCount(), counts(a).Y + _geometry(a)->PointCount());

            return counts;
        }
        void RenderLayer3D::UpdateGeometryData(const Resource<IGeometric>& geometry)
        {
            auto& data = _data[geometry.ID()];

            auto& indices = geometry->Indices();
            auto& mapping = geometry->Mapping();
            auto& normals = geometry->Normals();
            auto& points = geometry->Points();

            data.IndicesCount = indices.Count();
            data.IndicesIndex = _indices.Count();
            data.VertexCount = points.Count();
            data.VertexIndex = _vertices.Count();

            _indices.Append(indices);
            for (uint a = 0; a < points.Count(); a++)
                _vertices.Append(Vertex(points(a), normals(a), (Vector2)mapping(a)));
        }
    }
}