/* CHANGELOG
 * Written by Josh Grooms on 20170130
 */
export class InterfaceControl //implements IInteractive
 {
    constructor() {
        this.BackgroundColor = [0, 0, 0, 1];
        this.BorderColor = [0, 0, 0, 1];
        this.BorderRadius = [0, 0, 0, 0];
        this.BorderWidth = [1, 1, 1, 1];
        this.Components = [];
        this.IsClippingEnabled = true;
        this.IsEnabled = true;
        this.IsInteractive = false;
        this.IsVisible = true;
        this.Offset = [0, 0, 0];
        this.Orientation = [0, 0, 0];
        this.Position = [0, 0, 0];
        this.Scale = [1, 1, 1];
        this.Shape = [];
        this.Size = [1, 1, 1];
    }
}
export class Mesh3D {
    constructor() {
        this.Components = [];
        this.IsInteractive = false;
        this.IsVisible = true;
        this.Offset = [0, 0, 0];
        this.Orientation = [0, 0, 0];
        this.Position = [0, 0, 0];
        this.PrimaryColor = [0, 0, 0, 1];
        this.Scale = [1, 1, 1];
        this.SecondaryColor = [0, 0, 0, 1];
        this.Size = [1, 1, 1];
        this.Texture = '';
    }
}
//class Path2D
//{   
//    Components:         [ ]
//    CoverMode:          BoundingBox
//    FillMode:           CountUp
//    InitialCap:         Flat
//    IsInteractive:      false
//    IsVisible:          true
//    JoinStyle:          None
//    Offset:             [ 0, 0, 0 ]
//    Orientation:        [ 0, 0, 0 ]
//    Position:           [ 0, 0, 0 ]
//    PrimaryColor:       [ 0, 0, 0, 1 ]
//    Scale:              [ 1, 1, 1 ]
//    SecondaryColor:     [ 0, 0, 0, 1 ]
//    Size:               [ 1, 1, 1 ]
//    StrokeWidth:        1
//    TerminalCap:        Flat
//    Texture:            ''
//};
export class Scene3D {
}
//# sourceMappingURL=Classes.js.map