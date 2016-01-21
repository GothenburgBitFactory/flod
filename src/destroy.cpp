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
#include <Args.h>
#include <map>
#include <string>
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// queue destroy Foo [--force]
int handleDestroy (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (2);         // destroy <name>
  args.addOption ("force", true);  // [--[no]force]
  args.scan (argc, argv);

  if (args.getPositionalCount () == 2)
  {
    auto force   = args.getOption ("force");
    auto command = args.getPositional (0);
    auto name    = args.getPositional (1);

    // Validate arguments.
    if (name == "")
      throw std::string ("Queue name required.");

    // Execute command.
    std::cout << "# queue destroying "
              << name
              << (force ? " using force" : "")
              << ".\n";

    // TODO Destroy queue.
    // TODO Update config details.
  }
  else if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  else
    throw std::string ("queue destroy [--force] <name>");

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
