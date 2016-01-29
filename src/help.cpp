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
                 "usage: central <command> [<args>]\n"
                 "\n"
                 "Command:\n"
                 "  help [<command>]                                                 Shows usage and command help\n"
                 "  version                                                          Display program version\n"
                 "  create [--noarchive] [--timeout N] [--scan N] <queue> <location> Create a queue\n"
                 "  destroy [--force]                             <queue>            Destroy a queue\n"
                 "  clear                                         <queue>            Clears a queue\n"
                 "  retry                                         <queue>            Retries failed events\n"
                 "  info                                         [<queue>]           Shows queue configuration summary or detail\n"
                 "  hook                                          <queue> <script>   Sets up a queue hook\n"
                 "  unhook                                        <queue> <script>   Removes a queue hook\n"
                 "  post                                          <queue> <event>    Posts an event to a queue\n"
                 "  config [--force]                             [<queue> [<value>]] Lists, sets, clears and defaults configuration\n"
                 "  process [--exit-on-idle]                                         Processes all queues\n"
                 "\n";

  else if (command == "help")
    std::cout << "\n"
                 "central help [<command>]\n"
                 "\n"
                 "  Running 'central help' will display a list of commands with a brief description.\n"
                 "  Running 'central help <command>' will show more details about the command.\n"
                 "\n"
                 "  Alternately, try 'man flod' or 'man central' for full details.\n"
                 "\n";

  else if (command == "version")
    std::cout << "\n"
                 "central version\n"
                 "\n"
                 "  Displays the Flod version number and copyright information.\n"
                 "\n";

  else if (command == "create")
    std::cout << "\n"
                 "central create <queue> <location>\n"
                 "    [--[no]archive]\n"
                 "    [--timeout <seconds>]\n"
                 "    [--scan <seconds>]\n"
                 "\n"
                 "  Creates a named queue in the specified location. There will be a top-level\n"
                 "  directory named <name>, and several ѕub-directories.\n"
                 "\n"
                 "  If the '--noarchive' option is specified, then event archiving will not be\n"
                 "  performed, and processed events will be deleted.\n"
                 "\n"
                 "  The '--timeout' argument (default: 3600) will cause timeout and retry of jobs\n"
                 "  that exceed this length.\n"
                 "\n"
                 "  The '--scan' argument іs the number of seconds before a queue re-scan is\n"
                 "  performed, after the queue is depleted.\n"
                 "\n";

  else if (command == "destroy")
    std::cout << "\n"
                 "central destroy <queue> [--force]\n"
                 "\n"
                 "  Destroys the queue, by removing the associated directories and configuration settings.\n"
                 "\n"
                 "  If the queue contains any files or unrecognized content, the command will stop safely.\n"
                 "  To remove a queue that does have contents, use the '--force' option.\n"
                 "\n";

  else if (command == "clear")
    std::cout << "\n"
                 "central clear <queue>\n"
                 "\n"
                 "  Simply removes all the events in the queue, in an irreversible way.\n"
                 "\n";

  else if (command == "retry")
    std::cout << "\n"
                 "central retry\n"
                 "\n"
                 "  For the specified queue, takes all failed events and queues them for processing\n"
                 "  again.\n"
                 "\n";

  else if (command == "info")
    std::cout << "\n"
                 "central info [<queue>]\n"
                 "\n"
                 "  The command 'central info' will display a list of configured queues.\n"
                 "\n"
                 "  The command 'central info <queue>' will display full details of the specified queue\n"
                 "  which will include all events, configuration options, and hook scripts.\n"
                 "\n";

  else if (command == "hook")
    std::cout << "\n"
                 "central hook <queue> <script>\n"
                 "\n"
                 "  Creates a link between the named queue and hook script, such that new events\n"
                 "  posted to the queue cause the script to be run with the absolute path to the\n"
                 "  event file as the first (and only) argument. For example:\n"
                 "\n"
                 "    $ cat <<EOF >hook_script.sh\n"
                 "    #!/bin/sh\n"
                 "    echo Processing event $1\n"
                 "    EOF\n"
                 "    $\n"
                 "    $ chmod +x hook_script.sh\n"
                 "    $ central hook my_queue hook_script.sh\n"
                 "    Central hooked queue 'my_queue' to trigger script 'hook_script.sh'.\n"
                 "\n"
                 "  If multiple hook scripts are linked to the same queue, they are executed in\n"
                 "  the order they are configured.\n"
                 "\n"
                 "  Use 'central info <name>' to check the hook scripts for a queue.\n"
                 "\n";

  else if (command == "unhook")
    std::cout << "\n"
                 "central unhook <queue> <script>\n"
                 "\n"
                 "  Disassociates a hook script from a named queue.\n"
                 "\n"
                 "  Use 'central info <name>' to check the hook scripts for a queue.\n"
                 "\n";

  else if (command == "post")
    std::cout << "\n"
                 "central post <queue> <event>\n"
                 "\n"
                 "  Posts an event to the named queue. Do not compose event files in the queue.\n"
                 "  Instead, create the file in a temporary location, and use the 'post' command\n"
                 "  to move the event into the queue.\n"
                 "\n"
                 " The event file is renamed such that the queue name and timestamp are prepended\n"
                 " to the original name.\n"
                 "\n";

  else if (command == "config")
    std::cout << "\n"
                 "central config [--force] [<setting> [<value>]]\n"
                 "\n"
                 "  List, create, modify or remove a configuration setting. For example:\n"
                 "\n"
                 "    $ central config foo bar     # 1\n"
                 "    $ central config foo ''      # 2\n"
                 "    $ central config foo         # 3\n"
                 "    $ central config             # 4\n"
                 "\n"
                 "  The first example sets the configuration setting 'foo' to a value of 'bar'.\n"
                 "  This will either create or overwrite a setting. The second eample sets the\n"
                 "  value of 'foo' to blank, but does not delete the entry. The third example\n"
                 "  deletes 'foo' from the configuration file.\n"
                 "\n"
                 "  The fourth example lists all the configuration settings.\n"
                 "\n"
                 "  Note that the configuration file is by default '~/.flodrc', but a '.flodrc'\n"
                 "  file may exist in any parent directory. Note that setting the 'FLODRC'\n"
                 "  environment variable overrides this.\n"
                 "\n"
                 "  If the '--force' option is provided, user confirmation is not sought.\n"
                 "\n";

  else if (command == "process")
    std::cout << "\n"
                 "central process [--exit-on-idle]\n"
                 "\n"
                 "  Running 'central process' launches a non-interactive queue processor. Every\n"
                 "  defined queue is scanned, and every time an event is posted, the associated\n"
                 "  hook scripts are run.\n"
                 "\n"
                 "  Each queue is handled by a separate thread. If the queue has no hook scripts\n"
                 "  associated, the thread terminates. If the '--exit-on-idle' option is specified,\n"
                 "  and the queue is depleted, the thread terminates. Without '--exit-on-idle', if\n"
                 "  a queue is depleted processing waits for a number of seconds before re-scanning\n"
                 "  (see 'create' command).\n"
                 "\n"
                 "  When a hook script is called, the event file is first relocated to the 'active'\n"
                 "  sub-directory. On success, it is moved again to the 'archive' sub-directory,\n"
                 "  or deleted if no archiving is needed (see 'create' command). On failure, it is\n"
                 "  moved to the 'failed' sub-directory.\n"
                 "\n"
                 "  If the configuration changes (adding a hook script, for example), then the\n"
                 "  'central process' command must be restarted for it to be referenced.\n"
                 "\n";

  else
    std::cout << "\n"
                 "Unrecognized help topic '" << command << "'.\n"
                 "\n";
}

////////////////////////////////////////////////////////////////////////////////
