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
#include <Q.h>
#include <text.h>
#include <map>
#include <string>
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// central destroy Foo [--force]
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

    // Remove all config "queue.<name>.*" entries.
    std::string prefix = "queue." + name + ".";
    for (const auto& setting : config.all ())
      if (closeEnough (prefix, setting))
        if (! unsetVariableInFile (config.file (), "queue." + name + ".location"))
          throw std::string ("Could not remove configuration 'queue." + name + ".location'.");

    // Update config details.
    auto location = config.get ("queue." + name + ".location");
    if (location == "")
      throw std::string ("Queue '" + name + "' not configured.");

    if (! unsetVariableInFile (config.file (), "queue." + name + ".location"))
      throw std::string ("Could not remove configuration 'queue." + name + ".location'.");

    if (! unsetVariableInFile (config.file (), "queue." + name + ".archive"))
      throw std::string ("Could not remove configuration 'queue." + name + ".archive'.");

    // Destroy queue.
    Q q;
    q.create (location);
    q.destroy (force);
    std::cout << "Removed " << location << "\n";

    std::cout << "Central destroyed "
              << name
              << (force ? " using force" : "")
              << ".\n";
  }
  else if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  else
    throw std::string ("central destroy [--force] <name>");

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
