/* CHANGELOG
 * Written by Josh Grooms on 20170130
 */

//import { Color } from './Primitives';
import { Color, Vector2 } from './Primitives';

//module.exports = Classes = 

//    Double:
//        Value:          0

//    Enumeration:
//        Count:          0
//        Values:         [ ]

//    Function:
//        Arity:          [ 0, 0 ]
        
//    Integer:
//        Value:          0

//    Object:
//        Methods:        [ ]
//        Properties:     [ ]

//    String:
//        Count:          0
//        Value:          ''




export interface IInteractive
{
    IsInteractive:      boolean;

    ProcessButtonPress(button: any, position: Vector2);
    ProcessButtonRelease(button: any, position: Vector2);
    ProcessKeyPress(key: any, position: Vector2);
    ProcessKeyRelease(key: any, position: Vector2);
    ProcessPointerEntry(position: Vector2);
    ProcessPointerExit(position: Vector2);
    ProcessPointerMotion(position: Vector2);
    ProcessPropertyChange(property: string);
}

export class InterfaceControl //implements IInteractive
{
    BackgroundColor:    number[] = [ 0, 0, 0, 1 ];
    BorderColor:        number[] = [ 0, 0, 0, 1 ];
    BorderRadius:       number[] = [ 0, 0, 0, 0 ];
    BorderWidth:        number[] = [ 1, 1, 1, 1 ];
    Components:         number[] = [ ]
    IsClippingEnabled:  boolean = true;
    IsEnabled:          boolean = true;
    IsInteractive:      boolean = false;
    IsVisible:          boolean = true;
    Offset:             number[] = [ 0, 0, 0 ];
    Orientation:        number[] = [ 0, 0, 0 ];
    Parent:             any;
    Position:           number[] = [ 0, 0, 0 ];
    Scale:              number[] = [ 1, 1, 1 ];
    Shape:              number[] = [ ];
    Size:               number[] = [ 1, 1, 1 ];


    //OnHighlight:
    //{
    //    BackgroundColor: number[] = [ 0.5, 0.5, 0.5, 1 ];
    //};

    

    //OnButtonPress:      null
    //OnButtonRelease:    null
    //OnHighlight:        null
    //OnKeyPress:         null
    //OnKeyRelease:       null
    //OnPointerEntry:     null
    //OnPointerExit:      null
    //OnPropertyChange:   null
    //OnSelection:        null
}


export class Mesh3D
{
    Components:         number[] = [ ];
    IsInteractive:      boolean = false;
    IsVisible:          boolean = true;
    Offset:             number[] = [ 0, 0, 0 ];
    Orientation:        number[] = [ 0, 0, 0 ];
    Position:           number[] = [ 0, 0, 0 ];
    PrimaryColor:       number[] = [ 0, 0, 0, 1 ];
    Scale:              number[] = [ 1, 1, 1 ];
    SecondaryColor:     number[] = [ 0, 0, 0, 1 ];
    Size:               number[] = [ 1, 1, 1 ];
    Texture:            string = '';
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


export class Scene3D
{

}


        
