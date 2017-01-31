/* CHANGELOG
 * Written by Josh Grooms on 20170131
 */



class Color
{
    R: number;
    G: number;
    B: number;
    A: number;

    //constructor(r?: number, g?: number, b?:number, a?: number)
    constructor(color: number[])
    {
        { this.R, this.G, this.B, this.A } = color;
    }
}



class Vector2
{
    X: number;
    Y: number;
}

class Vector3
{
    X: number;
    Y: number;
    Z: number;
}

class Vector4
{
    X: number;
    Y: number;
    Z: number;
    W: number;
}