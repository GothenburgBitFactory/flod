////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 - 2017, Paul Beckingham, Federico Hernandez.
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

#ifndef INCLUDED_Q
#define INCLUDED_Q

#include <FS.h>
#include <string>
#include <vector>

class Q
{
public:
  static std::vector <std::string> structure;

public:
  void create (const std::string&, const std::string&);
  bool destroy (bool force = false);
  bool scan (std::string&);
  void post (const std::string&) const;
  int cleanup () const;

  std::string activateEvent (const std::string&) const;
  void archiveEvent (const std::string&) const;
  void failEvent (const std::string&) const;

  void clear ();
  std::vector <std::string> active () const  { return events (Directory (_location + "/" + Q::structure[0])._data); }
  std::vector <std::string> archive () const { return events (Directory (_location + "/" + Q::structure[1])._data); }
  std::vector <std::string> failed () const  { return events (Directory (_location + "/" + Q::structure[2])._data); }
  std::vector <std::string> staging () const { return events (Directory (_location + "/" + Q::structure[3])._data); }
  std::vector <std::string> queue () const   { return events (Directory (_location + "/" + Q::structure[4])._data); }

private:
  std::string composeEventPrefix () const;
  std::vector <std::string> events (const std::string&) const;

private:
  std::string _name     {"queue"};
  std::string _location {"."};
};

#endif

