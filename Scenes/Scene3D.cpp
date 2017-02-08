#include "Scene3D.h"
#include "Execution/Shorthand.h"



namespace Cyclone
{
    namespace Scenes
    {

        using namespace Shorthand;

        #define propdef(object, name) object.Insert( VirtualProperty(_memory.Insert(name)) )
        //#define cond


        Scene3D::Scene3D() { }

        bool Scene3D::Contains(uint entity) const
        {
            
            return false;
        }
        uint Scene3D::Insert(const IRenderable& entity)
        {
            return 0;
        }
        void Scene3D::Remove(uint entity)
        {
            //_memory.DeleteObject()
        }
        void Scene3D::Update()
        {

        }

        void Scene3D::Set(uint entity, uint property)
        {

        }
        void Scene3D::Set(const string& entity, const string& property)
        {

        }


        void Scene3D::CreateEntityClass()
        {
            VirtualClass entity( _memory.Insert("Entity3D") );
            propdef(entity, "Components");
            propdef(entity, "Geometry");
            propdef(entity, "IsVisible");
            propdef(entity, "Material");
            propdef(entity, "Transforms");

            _memory.Insert(entity);
        }



    }
}