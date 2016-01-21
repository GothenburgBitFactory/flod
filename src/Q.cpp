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

#include <cmake.h>
#include <Q.h>

////////////////////////////////////////////////////////////////////////////////
void Q::initialize (const std::string& location)
{
  _location = location;

  // TODO Create a queue dir if it doesn't exist.
  // TODO Set file permissions to owner-only.
  // TODO Create 'active' dir.
  // TODO Create 'archive' dir.
  // TODO Create 'failed' dir.
}

////////////////////////////////////////////////////////////////////////////////
bool Q::scan (std::string& event)
{
  // TODO Scan _location
  // TODO If item is not in _snapshot
  //   TODO Add item to snapshot
  //   TODO event <-- item
  //   TODO return true
  // TODO If _snapshot contains missing item
  //   TODO Remove _snapshot item
  return false;
}

////////////////////////////////////////////////////////////////////////////////
