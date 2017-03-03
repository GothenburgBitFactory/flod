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
#include <Log.h>
#include <format.h>
#include <shared.h>
#include <set>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

////////////////////////////////////////////////////////////////////////////////
// Arguments are deliberately by value, not by ref.
void manageQueue (
  std::shared_ptr <Log> log,
  std::string name,
  Configuration config,
  bool exit_on_idle)
{
  log->write (format ("{1} Startup thread {2}", name, std::this_thread::get_id ()));

  auto location = getQueueLocation (config, name);
  auto archive  = config.getBoolean ("queue." + name + ".archive");
  // TODO auto timeout  = config.getInteger ("queue." + name + ".timeout");
  std::chrono::seconds wait (config.getInteger ("queue." + name + ".scan"));

  // Get hook names. If no scripts hook this queue, exit.
  auto hookNames = getHookScriptNames (config, name);
  if (hookNames.size () == 0)
  {
    log->write (format ("{1} Exit thread {2} no hooks", name, std::this_thread::get_id ()));
    return;
  }

  std::vector <std::string> hookScripts;
  for (const auto& hookName : hookNames)
    hookScripts.push_back (config.get ("hook." + name + "." + hookName + ".script"));

  // Instantiate the queue
  Q q;
  q.create (name, location);

  while (1)
  {
    std::string event;
    if (q.scan (event))
    {
      // Move event to q/active.
      event = q.activateEvent (event);
      bool success = true;

      for (const auto& script : hookScripts)
      {
        try
        {
          // TODO Timeout the execute call.

          log->write (format ("{1} --> {2} {3}", name, script, event));

          std::string output;
          if (execute (script, {event}, "", output) == 0)
          {
            // TODO Debug mode perhaps.
            //log->write (format ("{1} --> {2} success", name, script));
          }
          else
          {
            success = false;
            log->write (format ("{1} --> {2} failed", name, script));
          }

          // Only show non-trivial output.
          if (output != "")
            log->write (format ("{1} --> {2}: {3}", name, script, output), true);
        }
        catch (std::string& e)
        {
          log->write (format ("{1} Error {2}", name, e));
          success = false;
        }
      }

      // Move event to either q/archive or q/failed, based on status.
      if (success && archive)
        q.archiveEvent (event);

      if (! success)
        q.failEvent (event);
    }

    // Cleanup and delays only occur on idle.
    else
    {
      // TODO scan active for timed out work --> requeue.
      // TODO Exit if all queues were empty and exit_on_idle

      if (exit_on_idle)
        break;

      // TODO Debug mode perhaps?
      //log->write (format ("{1} Idle thread {2}", name, std::this_thread::get_id ()));
      std::this_thread::sleep_for (wait);
    }
  }

  log->write (format ("{1} Exit thread {2} idle", name, std::this_thread::get_id ()));
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

  // Log file override.
  std::shared_ptr <Log> log = std::make_shared <Log> ();
  if (config.has ("log.file"))
    log->setFile (config.get ("log.file"));

  log->write (std::string ("=== ") + PACKAGE_STRING + " ===");
  log->write ("Processing begin");

  // Create a thread to manage each queue.
  std::vector <std::thread> managers;
  for (const auto& name : getQueueNames (config))
    managers.push_back (std::thread (manageQueue, log, name, config, exit_on_idle));

  // Gather loose ends.
  for (auto& manager : managers)
    manager.join ();

  log->write ("Processing end");
}

////////////////////////////////////////////////////////////////////////////////
