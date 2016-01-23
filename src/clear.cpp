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
#include <central.h>
#include <Args.h>
#include <Q.h>
#include <map>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void handleClear (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (2);        // clear <name>
  args.scan (argc, argv);

  if (args.getPositionalCount () == 2)
  {
    auto command = args.getPositional (0);
    auto name    = args.getPositional (1);

    // Validate arguments.
    if (name == "")
      throw std::string ("Queue name required.");

    // TODO Validate queue name.

    Q q;
    q.create (name, config.get ("queue." + name + ".location"));
    q.clear ();

    std::cout << "Central cleared queue "
              << name
              << ".\n";
  }
  else if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  else
    throw std::string ("central clear <name>");
}

////////////////////////////////////////////////////////////////////////////////
