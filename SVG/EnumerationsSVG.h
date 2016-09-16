/* CHANGELOG
 * Written by Josh Grooms on 20160916
 */

#pragma once
#include "Enumerator.h"

namespace
{
    using namespace Cyclone::Utilities;
}



struct PathFormats : public Enumerator
{
    enum Formats
    {
        SVG                             = 0x9070,
        PS                              = 0x9071,
    };

    constexpr PathFormats(enum Formats f = SVG) : Enumerator(f) { }
};

struct PathParameters : public Enumerator
{
    enum Parameters
    {
        ClientLength                    = 0x907F,
        CommandCount                    = 0x909D,
        ComputedLength                  = 0x90A0,
        CoordinateCount                 = 0x909E,
        DashArrayCount                  = 0x909F,
        DashCaps                        = 0x907B,
        DashOffset                      = 0x907E,
        DashOffsetReset                 = 0x90B4,
        EndCaps                         = 0x9076,
        FillCoverMode                   = 0x9082,
        FillMask                        = 0x9081,
        FillMode                        = 0x9080,
        InitialDashCap                  = 0x907C,
        InitialEndCap                   = 0x9077,
        JoinStyle                       = 0x9079,
        MiterLimit                      = 0x907A,
        StrokeCoverMode                 = 0x9083,
        StrokeMask                      = 0x9084,
        StrokeBound                     = 0x9086,
        StrokeWidth                     = 0x9075,
        TerminalDashCap                 = 0x907D,
        TerminalEndCap                  = 0x9078,
    };

    constexpr PathParameters(enum Parameters p) : Enumerator(p) { }
};

struct FillModes : public Enumerator
{
    enum Modes
    {
        CountUp                         = 0x9088,
        CountDown                       = 0x9089,
    };
};

struct CoverModes : public Enumerator
{
    enum Modes
    {
        BoundingBox                     = 0x908D,
        BoundingBoxOfBoundingBoxes      = 0x909C,
        ConvexHull                      = 0x908B,
    };
};

struct TransformTypes : public Enumerator
{
    enum Types
    {
        None                            = 0,
        TranslateX                      = 0x908E,
        TranslateY                      = 0x908F,
        Translate2D                     = 0x9090,
        Translate3D                     = 0x9091,
        Affine2D                        = 0x9092,
        Affine3D                        = 0x9094,
        TransposeAffine2D               = 0x9096,
        TransposeAffine3D               = 0x9098,
    };
};

struct CharacterEncodings : public Enumerator
{
    enum Encodings
    {
        UTF8                            = 0x909A,
        UTF16                           = 0x909B,
    };
};

struct GenerationModes : public Enumerator
{
    enum Modes
    {
        None                            = 0,
        Constant                        = 1,
        EyeLinear                       = 2,
        ObjectLinear                    = 3,
        ObjectBoundingBox               = 0x908A,
    };
};




