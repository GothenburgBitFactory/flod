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
#include <Configuration.h>
#include <map>
#include <string>
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// queue create Foo /path/to/queue --[no]archive
int handleCreate (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments.
  std::string name = "";
  std::string path = "";
  bool archive = true;
  for (int i = 2; i < argc; ++i)
  {
    std::cout << "# argv[" << i << "] " << argv[i] << "\n";

    if (argv[i][0] == '-')
    {
      if (! strcmp (argv[i], "--archive"))
        archive = true;
      else if (! strcmp (argv[i], "--noarchive"))
        archive = false;
    }
    else
    {
      if (name == "")
        name = argv[i];
      else
        path = argv[i];
    }
  }

  // Validate arguments.
  if (name == "")
    throw std::string ("Queue name required.");

  if (path == "")
    throw std::string ("Queue location required.");

  // Execute command.
  std::cout << "# queue creating "
            << name
            << " at location "
            << path
            << " with "
            << (archive ? "" : "no ")
            << "archiving.\n";

  // TODO Store config details.
  // TODO Create queue.

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
