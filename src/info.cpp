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
#include <Table.h>
#include <format.h>
#include <map>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void handleInfo (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (2);         // info <name>
  args.scan (argc, argv);

  // Display all queue names and locations.
  if (args.getPositionalCount () == 1)
  {
    Table table;
    table.extraPadding (0);
    table.intraPadding (1);
    table.add ("Queue");
    table.add ("Arch");
    table.add ("Timeout");
    table.add ("Scan");
    table.add ("Location");
    table.colorHeader ({"underline"});

    for (const auto& name : getQueueNames (config))
    {
      auto row = table.addRow ();
      table.set (row, 0, name);
      table.set (row, 1, config.getBoolean ("queue." + name + ".archive") ? "Yes" : "No");
      table.set (row, 2, format ("{1}s", config.getInteger ("queue." + name + ".timeout")));
      table.set (row, 3, format ("{1}s", config.getInteger ("queue." + name + ".scan")));
      table.set (row, 4, getQueueLocation (config, name));
    }

    std::cout << "\n"
              << table.render ()
              << "\n";
  }

  // Dispaly details for a single queue.
  else
  {
    auto name = args.getPositional (1);

    // Warn if queue already exists.
    auto location = getQueueLocation (config, name);

    // Create queue.
    Q q;
    q.create (name, location);

    std::cout << "\n"
              << name << " --> " << location << "\n"
              << "  Archive:  " << config.get ("queue." + name + ".archive") << "\n"
              << "  Timeout:  " << config.get ("queue." + name + ".timeout") << "s\n"
              << "  Scan:     " << config.get ("queue." + name + ".scan")    << "s\n"
              << "\n";

    std::cout << "  Queued:\n";
    for (const auto& event : q.queue ())
      std::cout << "    " << event << "\n";

    std::cout << "  Active:\n";
    for (const auto& event : q.active ())
      std::cout << "    " << event << "\n";

    std::cout << "  Failed:\n";
    for (const auto& event : q.failed ())
      std::cout << "    " << event << "\n";

    std::cout << "  Staging:\n";
    for (const auto& event : q.staging ())
      std::cout << "    " << event << "\n";

    std::cout << "  Archive:\n";
    for (const auto& event : q.archive ())
      std::cout << "    " << event << "\n";

    std::cout << "  Hook Scripts:\n";
    for (const auto& hook : getHookScriptNames (config, name))
      std::cout << "    " << config.get ("hook." + name + "." + hook + ".script") << "\n";

    std::cout << "\n";
  }
}

////////////////////////////////////////////////////////////////////////////////
