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
#include <map>
#include <string>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// central process [--exit-on-idle] [--max N]
int handleProcess (
  int argc,
  const char** argv,
  Configuration& config)
{
  // Process arguments;
  Args args;
  args.limitPositionals (1);               // process
  args.addOption ("exit-on-idle", false);  // [--[no]exit-on-idle]
  args.addNamed ("max", "0");              // [--max N]
  args.scan (argc, argv);

  if (args.getPositionalCount () == 1)
  {
    auto exit_on_idle = args.getOption ("exit-on-idle");
    int maxN          = strtol (args.getNamed ("max").c_str (), NULL, 10);
    auto command      = args.getPositional (0);

    int event_count = 0;
    // TODO while (maxN == 0 || event_count < maxN)
      // TODO Create a Hook object for each defined hook.
      // TODO Create a Q object for each defined queue.
      // TODO loop over Q
        // TODO q.scan
        // TODO dispatch hooks
        // TODO scan active for timed out work --> requeue.

      // TODO Exit if all queues were empty and exit_on_idle
  }

  else
    throw std::string ("central process [--exit-on-idle] [--max N]");

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
