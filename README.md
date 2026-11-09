A tempo multiplier breakpoint file generator for Max. Intended to be used with [modmetro~](http://github.com/flats/modmetro-Max).

This is a Max external, originally written against version 6.1.4 of the Max SDK and tested against Max 7. It now builds with the current [Max SDK](https://github.com/Cycling74/max-sdk-base) as a universal binary (Apple Silicon and Intel) and has been tested in Max 9. It creates breakpoint text files contained sequential tempo multipliers based on a variety of factors. These factors are intended to modulate a given tempo beat by beat when used with [modmetro~](http://github.com/flats/modmetro-Max).

This external uses the wave.c library by Richard Dobson from the fantabulous [_The Audio Programming Book_](https://mitpress.mit.edu/books/audio-programming-book).

This patch has only been tested on macOS and may not work on other platforms (especially the parts related to file handling).

## Why This Exists

This exists because I wanted to create variable tempo maps (unsteady tempos, accelerando, rallentando, etc.) in Logic Pro X and Pro Tools. I generate a breakpoint file with breakgen, import that file with modmetro~, wire the output up to player~, record the audio output, import the audio into one of those DAWs, and then detect the tempo.

## Installation

breakgen is distributed as a Max package, which includes the external, its help patcher and its reference page.

1. Download `OSX-breakgen.zip` from the [latest release](https://github.com/flats/breakgen-Max/releases/latest) and unzip it.
2. Move the `breakgen` folder into your Max packages folder. For Max 9 on macOS, that's `~/Documents/Max 9/Packages/`.
3. Restart Max.

If you installed an earlier version by copying `breakgen.mxo` and `breakgen.maxhelp` into `~/Documents/Max 9/Library/`, delete those two files so Max doesn't find two copies.

The external is ad-hoc signed rather than signed with an Apple Developer ID, so macOS may block it after you download it. If Max says it can't load `breakgen`, remove the quarantine flag:

```
xattr -dr com.apple.quarantine ~/Documents/Max\ 9/Packages/breakgen
```

## Using breakgen

Each `bang` outputs the next tempo multiplier. modmetro~ multiplies the length of each beat by one of these values: 1.0 leaves the beat unchanged, values above 1.0 lengthen it (slower) and values below 1.0 shorten it (faster). The values come from an oscillator that advances one step per value, so one cycle takes `sr` / `freq` steps (100 with the defaults).

| Message | What it does |
| --- | --- |
| `bang` | Output the next tempo multiplier. |
| `wavetype` *0–5* | Waveform: sine (default), triangle, square, saw down, saw up, or constant. |
| `freq` *float* | Oscillator frequency, default 100. |
| `sr` *float* | Steps per second, default 10000. Also restarts the cycle. |
| `constval` *float* | Value for the constant waveform, default 1.0. |
| `set random` *0–3* | Randomness: no random (default), replace, multi, or multi interp. |
| `set intensity` *float* | How strongly random modes 2 and 3 pull values toward random ones, default 0.05. |
| `set interval` *int* | Steps between new random targets in mode 3, default 1. |
| `writefile` *steps [depth]* | Save *steps* values as a breakpoint file for modmetro~ (opens a Save dialog). *depth* below 1 scales how far the values swing from 1.0. |
| `writebuf` *buffer steps* | Write *steps* values, centered on 0.0, into a `buffer~`. |

`set` *parameter value* also works for `freq`, `sr`, `wavetype`, `constval` and `buffer`. In Max, open the help patcher (right-click the object and choose Open breakgen Help) for working examples, or the reference page for full details on every message.

## Building

You'll need Xcode (or the Command Line Tools) and [CMake](https://cmake.org) 3.19 or later. The Max SDK headers come in as a git submodule:

```
git clone --recursive https://github.com/flats/breakgen-Max.git
cd breakgen-Max
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you already cloned without `--recursive`, run `git submodule update --init` first. The universal `breakgen.mxo` ends up in `externals/`. To work in Xcode instead, generate a project with `cmake -S . -B build -G Xcode` and open `build/breakgen.xcodeproj`.

The repository is laid out as a Max package (`externals/`, `help/`, `docs/refpages/`, `package-info.json`), so for development you can link it into your packages folder and restart Max:

```
ln -s "$PWD" ~/Documents/Max\ 9/Packages/breakgen
```

The help patcher is `help/breakgen.maxhelp`, and the reference page is `docs/refpages/breakgen-ref/breakgen.maxref.xml`.

## Contributors

Any feedback would be greatly appreciated - don't hesitate to drop me a line or create an issue.

## License

This software is released under the MIT License, which is included herein and is described here as well:

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
