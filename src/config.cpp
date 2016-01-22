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
#include <text.h>
#include <map>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
int handleConfig (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (3);         // config <name> [<value>]
  args.addOption ("force", false);   // [--[no]force]
  args.scan (argc, argv);

  if (args.getPositionalCount () == 0)
    throw std::string ("central config [--force] <name> [<value>]");

  else if (args.getPositionalCount () == 1)
    throw std::string ("Configuration setting name required.");

  auto force   = args.getOption ("force");
  auto command = args.getPositional (0);
  auto name    = args.getPositional (1);

  // Validate arguments.
  if (name == "")
    throw std::string ("Configuration setting required.");

  // central config <anme>
  if (args.getPositionalCount () == 2)
  {
    if (force ||
        confirm ("Please confirm that you wish to remove '" + name + "'"))
    {
      if (unsetVariableInFile (config.file (), name))
        std::cout << "Removed '" << name << "'.\n";
      else
        std::cout << "No changes necessary.\n";
    }
    else
      std::cout << "No confirmation. No changes made.\n";
  }

  // central config <name> <value>
  else if (args.getPositionalCount () == 3)
  {
    auto value = args.getPositional (2);

    if (force ||
        confirm ("Please confirm that you wish to set '" + name + "' to a value of '" + value + "'"))
    {
      if (setVariableInFile (config.file (), name, value))
        std::cout << "Modified '" << name << "' to have value '" << value << "'.\n";
      else
        std::cout << "No changes necessary.\n";
    }
    else
      std::cout << "No confirmation. No changes made.\n";
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
