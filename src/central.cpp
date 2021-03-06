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
#include <shared.h>
#include <iostream>
#include <map>
#include <string>
#include <new>

////////////////////////////////////////////////////////////////////////////////
// The $FLODRC environment variable overrides all.
// The whole path between $PWD and one level below / is scanned.
// If not found, assumes ~/.flodrc.
//
// Note: This is expensive, and performed only once.
std::string getConfigFile ()
{
  // Check $FLODRC.
  char* override = getenv ("FLODRC");
  if (override)
    return std::string (override);

  // Discover .flodrc between $PWD and directories above, excluding /.
  Directory d {Directory::cwd ()};
  do
  {
    File config (d._data + "/.flodrc");
    if (config.exists () &&
        ! config.is_directory ())
      return config._data;
  }
  while (d._data != "/" &&
         d.up ());

  // Could not find .flodrc, assuming home dir.
  return "~/.flodrc";
}

////////////////////////////////////////////////////////////////////////////////
std::string processArgs (
  int argc,
  const char** argv,
  Configuration& /* config */)
{
  std::string command = "";

  // Simply scan argv, looking for the first non-binary, non-option arg, and
  // assume what it finds is a command.
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] != '-' && command == "")
      command = argv[i];

    // TODO Apply CLI overrides to configuration.
  }

  if (command == "")
    command = "help";

  return command;
}

////////////////////////////////////////////////////////////////////////////////
int main (int argc, const char** argv)
{
  int status = 0;

  try
  {
    Configuration config;
    config.load (getConfigFile ());

    auto command = processArgs (argc, argv, config);

    std::vector <std::string> matches;
    if (autoComplete (command,
                      {"help", "version", "create", "destroy", "clear", "retry",
                       "info", "hook", "unhook", "process", "post", "config"},
                      matches) == 1)
    {
      command = matches[0];

      // Dispatch commands.
           if (command == "help")    handleHelp    (argc, argv);
      else if (command == "version") handleVersion ();
      else if (command == "create")  handleCreate  (argc, argv, config);
      else if (command == "destroy") handleDestroy (argc, argv, config);
      else if (command == "clear")   handleClear   (argc, argv, config);
      else if (command == "retry")   handleRetry   (argc, argv, config);
      else if (command == "info")    handleInfo    (argc, argv, config);
      else if (command == "hook")    handleHook    (argc, argv, config);
      else if (command == "unhook")  handleUnhook  (argc, argv, config);
      else if (command == "process") handleProcess (argc, argv, config);
      else if (command == "post")    handlePost    (argc, argv, config);
      else if (command == "config")  handleConfig  (argc, argv, config);
    }
    else
    {
      std::cerr << "Urecognized command '" << command << "'\n";
      handleHelp (argc, argv);
    }
  }

  catch (const std::string& error)
  {
    std::cerr << error << "\n";
    status = -1;
  }

  catch (std::bad_alloc& error)
  {
    std::cerr << "Error: Memory allocation failed: " << error.what () << "\n";
    status = -3;
  }

  catch (...)
  {
    std::cerr << "Error: Unknown error, please report.\n";
    status = -2;
  }

  return status;
}

////////////////////////////////////////////////////////////////////////////////
