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
#include <format.h>
#include <Q.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
void handleHook (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (3);         // hook <name> <script>
  args.scan (argc, argv);

  if (args.getPositionalCount () == 1)
    throw std::string ("Queue name required.");

  if (args.getPositionalCount () == 2)
    throw std::string ("Hook script command required.");

  auto command = args.getPositional (0);
  auto name    = args.getPositional (1);
  auto script  = args.getPositional (2);

  auto location = getQueueLocation (config, name);

  // Assert script is acceptable.
  File hookScript (script);
  if (! hookScript.exists ())
    throw std::string ("Hook script '" + script + "' not found.");

  if (! hookScript.readable ())
    throw std::string ("Hook script '" + script + "' is not readable.");

  if (! hookScript.executable ())
    throw std::string ("Hook script '" + script + "' is not executable.");

  // Generate unique name for hook.
  auto hookNames = getHookScriptNames (config, name);
  int count = 1;
  std::string hookName = "h1";
  while (std::find (hookNames.begin (), hookNames.end (), hookName) != hookNames.end ())
    hookName = format ("h{1}", ++count);

  // Add configuration.
  if (! setVariableInFile (config.file (), "hook." + name + "." + hookName + ".script",  hookScript._data))
    throw std::string ("Could not write configuration 'hook." + name + "." + hookName + ".script'.");

  std::cout << "Central hooked queue '"
            << name
            << "' to trigger script '"
            << script
            << "'.\n";
}

////////////////////////////////////////////////////////////////////////////////
