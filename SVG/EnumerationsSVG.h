/* CHANGELOG
 * Written by Josh Grooms on 20160916
 */

#pragma once
#include "Enumerator.h"

namespace
{
    using namespace Cyclone::Utilities;
}

struct CharacterEncodings : public Enumerator
{
    enum Encodings
    {
        UTF8                                    = 0x909A,
        UTF16                                   = 0x909B,
    };
};

struct CoverModes : public Enumerator
{
    enum Modes
    {
        BoundingBox                             = 0x908D,
        BoundingBoxOfBoundingBoxes              = 0x909C,
        ConvexHull                              = 0x908B,
    };

    constexpr CoverModes(enum Modes m = BoundingBox) : Enumerator(m) { }
};

struct FillModes : public Enumerator
{
    enum Modes
    {
        CountUp                                 = 0x9088,
        CountDown                               = 0x9089,
    };

    constexpr FillModes(enum Modes m = CountUp) : Enumerator(m) { }
};

struct FontStyles : public Enumerator
{
    enum Styles
    {
        None                                    = 0,
        Bold                                    = 0x01,
        Italic                                  = 0x02,
    };

    constexpr FontStyles(enum Styles s = None) : Enumerator(s) { }
};

struct GenerationModes : public Enumerator
{
    enum Modes
    {
        None                                    = 0,
        Constant                                = 0x8576,
        EyeLinear                               = 0x2400,
        ObjectLinear                            = 0x2401,
        ObjectBoundingBox                       = 0x908A,
    };
};

struct JoinStyles : public Enumerator
{
    enum Styles
    {
        None                                    = 0,
        Bevel                                   = 0x90A6,
        MiterRevert                             = 0x90A7,
        MiterTruncate                           = 0x90A8,
        Round                                   = 0x90A4,
    };

    constexpr JoinStyles(enum Styles s = None) : Enumerator(s) { }
};

struct PathCommands //: public Enumerator
{
    public:
        enum Commands : ubyte
        {
            Arc                                     = 0xFE,
            CircularArcCCW                          = 0xF8,
            CircularArcCW                           = 0xFA,
            CircularTangentArc                      = 0xFC,
            Close                                   = 0x00,
            ConicCurve                              = 0x1A,
            CubicCurve                              = 0x0C,

            DuplicateFirstCubicCurve                = 0xF2,
            DuplicateLastCubicCurve                 = 0xF4,

            HorizontalLine                          = 0x06,
            LargeArcCCW                             = 0x16,
            LargeArcCW                              = 0x18,
            Line                                    = 0x04,
            Move                                    = 0x02,
            QuadraticCurve                          = 0x0A,

            Rectangle                               = 0xF6,
            RelativeArc                             = 0xFF,
            RelativeConicCurve                      = 0x1B,
            RelativeCubicCurve                      = 0x0D,
            RelativeHorizontalLine                  = 0x07,
            RelativeLargeArcCCW                     = 0x17,
            RelativeLargeArcCW                      = 0x19,
            RelativeLine                            = 0x05,
            RelativeMove                            = 0x03,
            RelativeQuadraticCurve                  = 0x0B,
            RelativeRectangle                       = 0xF7,
            RelativeRoundedRectangle                = 0xE9,
            RelativeRoundedRectangle2               = 0xEB,
            RelativeRoundedRectangle4               = 0xED,
            RelativeRoundedRectangle8               = 0xEF,
            RelativeSmallArcCCW                     = 0x13,
            RelativeSmallArcCW                      = 0x15,
            RelativeSmoothQuadraticCurve            = 0x0F,
            RelativeSmoothCubicCurve                = 0x11,
            RelativeVerticalLine                    = 0x09,
            Restart                                 = 0xF0,

            RoundedRectangle                        = 0xE8,
            RoundedRectangle2                       = 0xEA,
            RoundedRectangle4                       = 0xEC,
            RoundedRectangle8                       = 0xEE,

            SmallArcCCW                             = 0x12,
            SmallArcCW                              = 0x14,
            SmoothQuadraticCurve                    = 0x0E,
            SmoothCubicCurve                        = 0x10,

            VerticalLine                            = 0x08,
        };

        constexpr PathCommands(enum Commands c = Move) :
            Value(c)
        {

        }

        constexpr operator ubyte() const { return Value; }

    private:
        ubyte Value;
};

struct PathFormats : public Enumerator
{
    enum Formats
    {
        SVG                                     = 0x9070,
        PS                                      = 0x9071,
    };

    constexpr PathFormats(enum Formats f = SVG) : Enumerator(f) { }
};

struct PathParameters : public Enumerator
{
    enum Parameters
    {
        ClientLength                            = 0x907F,
        CommandCount                            = 0x909D,
        ComputedLength                          = 0x90A0,
        CoordinateCount                         = 0x909E,
        DashArrayCount                          = 0x909F,
        DashCaps                                = 0x907B,
        DashOffset                              = 0x907E,
        DashOffsetReset                         = 0x90B4,
        EndCaps                                 = 0x9076,
        FillCoverMode                           = 0x9082,
        FillMask                                = 0x9081,
        FillMode                                = 0x9080,
        InitialDashCap                          = 0x907C,
        InitialEndCap                           = 0x9077,
        JoinStyle                               = 0x9079,
        MiterLimit                              = 0x907A,
        StrokeCoverMode                         = 0x9083,
        StrokeMask                              = 0x9084,
        StrokeBound                             = 0x9086,
        StrokeWidth                             = 0x9075,
        TerminalDashCap                         = 0x907D,
        TerminalEndCap                          = 0x9078,
    };

    constexpr PathParameters(enum Parameters p) : Enumerator(p) { }
};

struct TransformMatrices : public Enumerator
{
    enum Matrices
    {
        ModelView                               = 0x1700,
        Projection                              = 0x1701,
    };
};

struct TransformTypes : public Enumerator
{
    enum Types
    {
        None                                    = 0,
        TranslateX                              = 0x908E,
        TranslateY                              = 0x908F,
        Translate2D                             = 0x9090,
        Translate3D                             = 0x9091,
        Affine2D                                = 0x9092,
        Affine3D                                = 0x9094,
        TransposeAffine2D                       = 0x9096,
        TransposeAffine3D                       = 0x9098,
    };
};
