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
#include <Args.h>
#include <Configuration.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void handleHelp (int argc, const char** argv)
{
  // Process arguments;
  Args args;
  args.limitPositionals (2);        // help [<command>]
  args.scan (argc, argv);

  std::string help;
  if (args.getPositionalCount () > 0)
    help = args.getPositional (0);

  std::string command = "";
  if (args.getPositionalCount () > 1)
    command = args.getPositional (1);

  if (args.getPositionalCount () <= 1)
    std::cout << "\n"
              << "usage: central <command> [<args>]\n"
              << "\n"
              << "Command:\n"
              << "  help [<command>]                                                Shows usage and command help\n"
              << "  version                                                         Display program version\n"
              << "  create [--noarchive] [--timeout N] [--scan N] <name> <path>     Create a queue\n"
              << "  destroy [--force]                             <name>            Destroy a queue\n"
              << "  clear                                         <name>            Clears a queue\n"
              << "  retry                                         <name>            Retries failed events\n"
              << "  info                                          <name>            Shows queue details\n"
              << "  hook                                          <name> <path>     Sets up a queue hook\n"
              << "  unhook                                        <name> <path>     Removes a queue hook\n"
              << "  post                                          <name> <path>     Posts an event to a queue\n"
              << "  config [--force]                              <name> [<value>]  Sets, clears and defaults configuration\n"
              << "  process [--exit-on-idle]                                        Processes all queues\n"
              << "\n";
  else if (command == "help")
    std::cout << "\n";
  else if (command == "version")
    std::cout << "\n";
  else if (command == "create")
    std::cout << "\n";
  else if (command == "destroy")
    std::cout << "\n";
  else if (command == "clear")
    std::cout << "\n";
  else if (command == "retry")
    std::cout << "\n";
  else if (command == "info")
    std::cout << "\n";
  else if (command == "hook")
    std::cout << "\n";
  else if (command == "unhook")
    std::cout << "\n";
  else if (command == "post")
    std::cout << "\n";
  else if (command == "config")
    std::cout << "\n";
  else if (command == "process")
    std::cout << "\n";
  else
    std::cout << "\n"
              << "Unrecognized help topic '" << command << "'.\n";
}

////////////////////////////////////////////////////////////////////////////////
