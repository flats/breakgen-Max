A tempo multiplier breakpoint file generator for Max 7. Intended to be used with [modmetro~](http://github.com/flats/modmetro-Max).

This is a Max external written against [version 6.1.4 of the MaxSDK](https://cycling74.com/sdk/MaxSDK-6.1.4/html/index.html). It should be compatible with most 32-bit (Max 5 and earlier) and 64-bit versions of Max, but I've only tested it extensively against Max 7. It creates breakpoint text files contained sequential tempo multipliers based on a variety of factors. These factors are intended to modulate a given tempo beat by beat when used with [modmetro~](http://github.com/flats/modmetro-Max).

This external uses the wave.c library by Richard Dobson from the fantabulous [_The Audio Programming Book_](https://mitpress.mit.edu/books/audio-programming-book).

This patch has only been tested on OS X and may not work on other platforms (especially the parts related to file handling).

## Why This Exists

This exists because I wanted to create variable tempo maps (unsteady tempos, accelerando, rallentando, etc.) in Logic Pro X and Pro Tools. I generate a breakpoint file with breakgen~, import that file with this object, wire the output up to player~, record the audio output, import the audio into one of those DAWs, and then detect the tempo.

## Installation

Just download the `OSX-modmetro~.zip` file and drop the contents (`modmetro~.mxo` and `modmetro~.maxhelp`) into your Max 7 user library. On OS X, that's probably `/Users/Shared/Max 7/Library/`.

If you want to compile these, download the MaxSDK and drop this whole repo into `MaxSDK-6.1.4/examples/audio`. It should work with other, later versions of the SDK, and it can go in any subfolder under `examples`.

## Contributors

Any feedback would be greatly appreciated - don't hesitate to drop me a line or create an issue.

## License

This software is released under the MIT License, which is included herein and is described here as well:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
