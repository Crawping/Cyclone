#include "NVPR.h"
#include "Geometry/Entity2D.h"



namespace Cyclone
{
    namespace SVG
    {
        
        /** PROPERTIES **/
        Entity2D& Entity2D::CoverMode(CoverModes value)
        {
            _style.CoverMode = value;
            return *this;
        }
        Entity2D& Entity2D::FillMode(FillModes value)
        {
            _style.FillMode = value;
            return *this;
        }
        Entity2D& Entity2D::InitialCap(EndCaps value)
        {
            _style.InitialCap = value;
            _needsUpdate = true;
            return *this;
        }
        Entity2D& Entity2D::JoinStyle(JoinStyles value)
        {
            _style.JoinStyle = value;
            _needsUpdate = true;
            return *this;
        }
        Entity2D& Entity2D::StrokeWidth(float value)
        {
            _style.StrokeWidth = value;
            _needsUpdate = true;
            return *this;
        }
        Entity2D& Entity2D::Style(const PathStyle& value)
        {
            return
                 CoverMode(value.CoverMode)
                .FillMode(value.FillMode)
                .InitialCap(value.InitialCap)
                .JoinStyle(value.JoinStyle)
                .StrokeWidth(value.StrokeWidth)
                .TerminalCap(value.TerminalCap);
        }
        Entity2D& Entity2D::TerminalCap(EndCaps value)
        {
            _style.TerminalCap = value;
            _needsUpdate = true;
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Entity2D::Entity2D(uint count) : 
            _id(nvGenPaths(count)),
            _instanceCount(count),
            _needsUpdate(true)
        {

        }
        Entity2D::Entity2D(Entity2D&& other) :
            _id(other._id),
            _instanceCount(other._instanceCount),
            _needsUpdate(other._needsUpdate)
        {
            other._id = 0;
            other._instanceCount = 0;
            other._needsUpdate = false;
        }
        Entity2D::~Entity2D()
        {
            if (_id) { nvDeletePaths(_id, _instanceCount); }
        }



        /** UTILITIES **/
        void Entity2D::Fill() const
        {
            if (!IsVisible()) { return; }
            StencilFill();
            CoverFill();
        }
        void Entity2D::Stroke() const
        {
            if (!IsVisible()) { return; }
            StencilStroke();
            CoverStroke();
        }
        void Entity2D::Update() const
        {
            if (!_needsUpdate) { return; }
            UpdateParameters();
            _needsUpdate = false;
        }



        /** PROTECTED UTILITIES **/
        void Entity2D::CoverFill()          const
        {
            nvCoverFillPath(ID(), CoverMode());
        }
        void Entity2D::CoverStroke()        const
        {
            nvCoverStrokePath(ID(), CoverMode());
        }
        void Entity2D::StencilFill()        const
        {
            nvStencilFillPath(ID(), FillMode(), 0x1F);
        }
        void Entity2D::StencilStroke()      const
        {
            nvStencilStrokePath(ID(), 0x1, ~0);
        }
        void Entity2D::UpdateParameters()   const
        {
            nvPathParameteri(ID(), PathParameters::JoinStyle, JoinStyle());
            nvPathParameteri(ID(), PathParameters::InitialEndCap, InitialCap());
            nvPathParameterf(ID(), PathParameters::StrokeWidth, StrokeWidth());
            nvPathParameteri(ID(), PathParameters::TerminalEndCap, TerminalCap());
        }

    }
}

