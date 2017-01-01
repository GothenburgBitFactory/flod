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

#include <cmake.h>
#include <central.h>
#include <Args.h>
#include <Q.h>
#include <FS.h>
#include <map>
#include <string>
#include <cstring>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void handleCreate (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (3);         // central <name> <location>
  args.addOption ("archive", true);  // [--[no]archive]
  args.addNamed ("timeout", "3600"); // [--timeout N]
  args.addNamed ("scan", "60");      // [--scan N]
  args.scan (argc, argv);

  if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  if (args.getPositionalCount () == 2)
    throw std::string ("Queue location required.");

  auto archive = args.getOption ("archive");
  auto timeout = args.getNamed ("timeout");
  auto scan    = args.getNamed ("scan");
  auto command = args.getPositional (0);
  auto name    = args.getPositional (1);
  auto path    = args.getPositional (2);

  // Warn if queue already exists.
  if (config.has ("queue." + name + ".location"))
    throw std::string ("Queue '" + name + "' is already defined.");

  Path location (path);

  // Store config details.
  if (! setVariableInFile (config.file (), "queue." + name + ".location", location._data))
    throw std::string ("Could not write configuration 'queue." + name + ".location'.");

  if (! setVariableInFile (config.file (), "queue." + name + ".archive",  (archive ? "yes" : "no")))
    throw std::string ("Could not write configuration 'queue." + name + ".archive'.");

  if (! setVariableInFile (config.file (), "queue." + name + ".timeout",  timeout))
    throw std::string ("Could not write configuration 'queue." + name + ".timeout'.");

  if (! setVariableInFile (config.file (), "queue." + name + ".scan",  scan))
    throw std::string ("Could not write configuration 'queue." + name + ".scan'.");

  // Create queue.
  Q q;
  q.create (name, path);

  std::cout << "Central created queue '"
            << name
            << "' at location "
            << path
            << (archive ? " with " : " without ")
            << "archiving, "
            << (timeout != "" ? "with timeout " + timeout + "s, " : "")
            << "with a scan every " << scan << "s"
            << ".\n";
}

////////////////////////////////////////////////////////////////////////////////
