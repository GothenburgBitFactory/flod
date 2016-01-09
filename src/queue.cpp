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
#include <map>
#include <string>
#include <new>

int handleHelp ();
int handleVersion ();
int handleCreate  (int, const char**, std::map <std::string, std::string>&);
int handleDestroy (int, const char**, std::map <std::string, std::string>&);
int handleClear   (int, const char**, std::map <std::string, std::string>&);
int handleInfo    (int, const char**, std::map <std::string, std::string>&);
int handleStats   (int, const char**, std::map <std::string, std::string>&);
int handleHook    (int, const char**, std::map <std::string, std::string>&);
int handleUnhook  (int, const char**, std::map <std::string, std::string>&);

////////////////////////////////////////////////////////////////////////////////
std::string getConfigFile ()
{
  // Check $FLODRC.
  char* override = getenv ("FLODRC");
  if (override)
    return std::string (override);

  // TODO Find .flodrc.

  return ".flodrc";
}

////////////////////////////////////////////////////////////////////////////////
std::map <std::string, std::string> loadConfigFile (const std::string&)
{
  // TODO Load .flodrc.
  return {};
}

////////////////////////////////////////////////////////////////////////////////
void processArgs (
  int argc,
  const char** argv,
  std::string& command,
  std::map <std::string, std::string>& config)
{
  command = "";

  // TODO Process argc, argv.
  // TODO Apply CLI overrides to .flodrc.
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] != '-' &&
        command == "")
      command = argv[i];
  }

  if (command == "")
    command = "help";
}

////////////////////////////////////////////////////////////////////////////////
int main (int argc, const char** argv)
{
  int status = 0;

  try
  {
    auto config = loadConfigFile (getConfigFile ());
    std::string command;
    processArgs (argc, argv, command, config);

    // Dispatch commands.
         if (command == "help")    status = handleHelp    ();
    else if (command == "version") status = handleVersion ();
    else if (command == "create")  status = handleCreate  (argc, argv, config);
    else if (command == "destroy") status = handleDestroy (argc, argv, config);
    else if (command == "clear")   status = handleClear   (argc, argv, config);
    else if (command == "info")    status = handleInfo    (argc, argv, config);
    else if (command == "stats")   status = handleStats   (argc, argv, config);
    else if (command == "hook")    status = handleHook    (argc, argv, config);
    else if (command == "unhook")  status = handleUnhook  (argc, argv, config);
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
