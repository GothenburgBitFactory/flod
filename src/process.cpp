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
#include <set>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <thread>

////////////////////////////////////////////////////////////////////////////////
// Arguments are deliberately by value, not by ref.
void manageQueue (
  std::string name,
  Configuration config,
  bool exit_on_idle)
{
  // TODO If no scripts hook this queue, exit.

  auto location = getQueueLocation (config, name);
  auto archive  = config.getBoolean ("queue." + name + ".archive");
  auto timeout  = config.getInteger ("queue." + name + ".timeout");

  // Instantiate the queue
  Q q;
  q.create (name, location);

  // TODO loop
    // TODO q.scan
      // TODO Dispatch hooks

    // TODO scan active for timed out work --> requeue.
    // TODO Exit if all queues were empty and exit_on_idle
}

////////////////////////////////////////////////////////////////////////////////
void handleProcess (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (1);               // process
  args.addOption ("exit-on-idle", false);  // [--[no]exit-on-idle]
  args.scan (argc, argv);

  auto exit_on_idle = args.getOption ("exit-on-idle");

  // Create a thread to manage each queue.
  std::vector <std::thread> managers;
  for (const auto& name : getQueueNames (config))
    managers.push_back (std::thread (manageQueue, name, config, exit_on_idle));

  // Gather loose ends.
  for (auto& manager : managers)
    manager.join ();
}

////////////////////////////////////////////////////////////////////////////////
