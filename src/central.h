////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 - 2016, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_CENTRAL
#define INCLUDED_CENTRAL

#include <Configuration.h>

// Command handlers.
void handleHelp ();
void handleVersion ();
int handleCreate  (int, const char**, Configuration&);
int handleDestroy (int, const char**, Configuration&);
int handleClear   (int, const char**, Configuration&);
int handleRetry   (int, const char**, Configuration&);
int handleInfo    (int, const char**, Configuration&);
int handleStats   (int, const char**, Configuration&);
int handleHook    (int, const char**, Configuration&);
int handleUnhook  (int, const char**, Configuration&);
int handleProcess (int, const char**, Configuration&);
int handlePost    (int, const char**, Configuration&);
int handleConfig  (int, const char**, Configuration&);

#endif

