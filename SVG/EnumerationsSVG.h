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
        /// <summary> Indicates that fragments within the bounding box of a shape should be rasterized. </summary>
        BoundingBox                             = 0x908D,
        BoundingBoxOfBoundingBoxes              = 0x909C,
        /// <summary> Indicates that fragments within the covex hull of a shape should be rasterized. </summary>
        ConvexHull                              = 0x908B,
    };

    constexpr CoverModes(enum Modes m = BoundingBox) : Enumerator(m) { }
};

struct DashOffsetResets : public Enumerator
{
    enum Resets
    {
        MoveContinues                           = 0x90B6,
        MoveResets                              = 0x90B5,
    };
};

/// <summary> A list of supported end cap styles that can be applied to path segments. </summary>
struct EndCaps : public Enumerator
{
    enum Caps
    {
        /// <summary> A flat square end cap that does not extend beyond the final control point of the segment. </summary>
        Flat                                    = 0,
        /// <summary> A semicircular end cap that extends beyond the final control point of the segment. </summary>
        Round                                   = 0x90A4,
        /// <summary> A flat square end cap that extends beyond the final control point of the segment. </summary>
        Square                                  = 0x90A3,
        /// <summary> A triangular end cap that extends beyond the final control point of the segment. </summary>
        Triangular                              = 0x90A5,
    };

    constexpr EndCaps(enum Caps c = Flat) : Enumerator(c) { }
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

/// <summary> A list of support font rendering styles. </summary>
struct FontStyles : public Enumerator
{
    enum Styles
    {
        /// <summary> The normal character style. </summary>
        None                                    = 0,
        /// <summary> A style that produces thick, bold characters. </summary>
        Bold                                    = 0x01,
        /// <summary> A style that produces thinner characters with a slightly forward slant. </summary>
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

struct GlyphMetrics : public Enumerator
{
    enum Metrics
    {

    };
};

/// <summary> A list of supported styles by which path segments can be joined together. </summary>
struct JoinStyles : public Enumerator
{
    enum Styles
    {
        /// <summary> The normal square path segment joint. </summary>
        None                                    = 0,
        Bevel                                   = 0x90A6,
        MiterRevert                             = 0x90A7,
        MiterTruncate                           = 0x90A8,
        /// <summary> A style that produces path segment joints with rounded semicircular corners. </summary>
        Round                                   = 0x90A4,
    };

    constexpr JoinStyles(enum Styles s = None) : Enumerator(s) { }
};

/// <summary> A list of supported commands used to construct path segments. </summary>
struct PathCommands //: public Enumerator
{
    public:
        enum Commands : ubyte
        {
            /// <summary> Draws an arc using the parameters (rx, ry, roll, isLarge, isPositive, x, y). </summary>
            /// <param name="rx"> The radius of the arc along the x-axis. </param>
            /// <param name="ry"> The radius of the arc along the y-axis. </param>
            /// <param name="roll"> The arc's angle of rotation about the z-axis in degrees. </param>
            /// <param name="isLarge"> Determines if the angle subtended by the arc is greater than 180 degrees. </param>
            /// <param name="isPositive"> Determines if arc drawing should proceed through positive angles. </param>
            /// <param name="x"> The x-coordinate at which arc drawing should terminate. </param>
            /// <param name="y"> The y-coordinate at which arc drawing should terminate. </param>
            Arc                                     = 0xFE,
            CircularArcCCW                          = 0xF8,
            CircularArcCW                           = 0xFA,
            CircularTangentArc                      = 0xFC,
            /// <summary> Terminates a list of path commands. </summary>
            Close                                   = 0x00,
            ConicCurve                              = 0x1A,
            CubicCurve                              = 0x0C,

            DuplicateFirstCubicCurve                = 0xF2,
            DuplicateLastCubicCurve                 = 0xF4,
            /// <summary> Draws a straight horizontal line through the absolute axis intercept (y). </summary>
            HorizontalLine                          = 0x06,
            LargeArcCCW                             = 0x16,
            LargeArcCW                              = 0x18,
            /// <summary> Draws a straight line from the current path position to the absolute point (x, y). </summary>
            Line                                    = 0x04,
            /// <summary> Moves the current path position to the absolute location (x, y). </summary>
            Move                                    = 0x02,
            QuadraticCurve                          = 0x0A,

            /// <summary> Draws a 2D rectangle using the parameters (x, y, width, height). </summary>
            Rectangle                               = 0xF6,
            RelativeArc                             = 0xFF,
            RelativeConicCurve                      = 0x1B,
            RelativeCubicCurve                      = 0x0D,
            /// <summary> Draws a straight horizontal line through the relative axis intercept (dy). </summary>
            RelativeHorizontalLine                  = 0x07,
            RelativeLargeArcCCW                     = 0x17,
            RelativeLargeArcCW                      = 0x19,
            /// <summary> Draws a straight line from the current path position to the relative point (dx, dy). </summary>
            RelativeLine                            = 0x05,
            /// <summary> Moves the current path position to an offset location at (dx, dy). </summary>
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
            /// <summary> Draws a straight vertical light through the relative axis intercept (dx). </summary>
            RelativeVerticalLine                    = 0x09,
            Restart                                 = 0xF0,

            /// <summary> Draws a 2D rectangle with uniformly rounded corners using the parameters (x, y, width, height, radius). </summary>
            RoundedRectangle                        = 0xE8,
            RoundedRectangle2                       = 0xEA,
            RoundedRectangle4                       = 0xEC,
            RoundedRectangle8                       = 0xEE,

            SmallArcCCW                             = 0x12,
            SmallArcCW                              = 0x14,
            SmoothQuadraticCurve                    = 0x0E,
            SmoothCubicCurve                        = 0x10,
            /// <summary> Draws a straight vertical line through the absolute axis intercept (x). </summary>
            VerticalLine                            = 0x08,
        };

        constexpr PathCommands(enum Commands c = Move) : Value(c) { }
        
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
