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
#include <shared.h>
#include <map>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void handleUnhook (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (3);         // unhook <name> <script>
  args.scan (argc, argv);

  if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  if (args.getPositionalCount () == 2)
    throw std::string ("Hook script command required.");

  auto command = args.getPositional (0);
  auto name    = args.getPositional (1);
  auto script  = args.getPositional (2);

  File hookScript (script);

  // Remove all settings for 'hook.<name>.<hookName>.*'
  for (auto& hookName : getHookScriptNames (config, name))
  {
    std::string prefix = "hook." + name + "." + hookName;
    for (const auto& setting : config.all ())
      if (closeEnough (setting, prefix))
        if (! unsetVariableInFile (config.file (), setting))
          throw std::string ("Could not remove configuration '" + setting + "'.");
  }

  std::cout << "Central unhooked queue '"
            << name
            << "' from triggering script '"
            << script
            << "'.\n";
}

////////////////////////////////////////////////////////////////////////////////
