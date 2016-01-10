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
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
int handleHelp ()
{
  std::cout << "\n"
            << "usage: queue <command> [<args>]\n"
            << "\n"
            << "Command:\n"
            << "  help                                                  Shows usage\n"
            << "  version                                               Display program version\n"
            << "  create [--noarchive]                <name> <path>     Create a queue\n"
            << "  destroy [--force]                   <name>            Destroy a queue\n"
            << "  clear                               <name>            Clears a queue\n"
            << "  info                                <name>            Shows queue details\n"
            << "  stats [reset]                       <name>            Shows or resets queue statistics\n"
            << "  hook [success | failure] [--scan T] <name> <path>     Sets up a queue hook\n"
            << "  unhook                              <name> <path>     Removes a queue hook\n"
            << "  process [--exit-on-idle] [--max N]  <name>            Processes a queue\n"
            << "  post                                <name> <path>     Posts an event to a queue\n"
            << "  config                              <name> [<value>]  Sets, clears and defaults configuration\n"
            << "\n";

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
