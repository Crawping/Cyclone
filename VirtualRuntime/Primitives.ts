/* CHANGELOG
 * Written by Josh Grooms on 20170131
 */



export class Border
{
    Top:        number;
    Bottom:     number;
    Left:       number;
    Right:      number;

    //constructor
    constructor(values)
    {
        //if (typeof values == "
        [ this.Top, this.Bottom, this.Left, this.Right ] = values;
    }
}

export class Color
{
    R: number;
    G: number;
    B: number;
    A: number;

    //constructor(r?: number, g?: number, b?:number, a?: number)
    //constructor(color: number[])
    //{
    //    //{ this.R, this.G, this.B, this.A } = color;
    //}
}

export class Vector2
{
    X: number;
    Y: number;
}

export class Vector3
{
    X: number;
    Y: number;
    Z: number;
}

export class Vector4
{
    X: number;
    Y: number;
    Z: number;
    W: number;
}