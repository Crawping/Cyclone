﻿class Greeter 
{
    Element:    HTMLElement;
    Span:       HTMLElement;
    TimerToken: number;

    constructor(element: HTMLElement) 
    {
        this.Element = element;
        this.Element.innerHTML += "The time is: ";
        this.Span = document.createElement('span');
        this.Element.appendChild(this.Span);
        this.Span.innerText = new Date().toUTCString();
    }

    Start() 
    {
        this.TimerToken = setInterval(() => this.Span.innerHTML = new Date().toUTCString(), 500);
    }
    Stop()
    {
        clearTimeout(this.TimerToken);
    }

}

window.onload = () => 
{
    var el = document.getElementById('content');
    var greeter = new Greeter(el);
    greeter.Start();
};

let border: number[] = [ 0, 0, 0, 0 ];
console.log(typeof border);