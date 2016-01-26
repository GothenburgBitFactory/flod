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

////////////////////////////////////////////////////////////////////////////////
std::string getQueueLocation (const Configuration& config, const std::string& name)
{
  std::string key = "queue." + name + ".location";
  if (! config.has (key))
    throw std::string ("Queue '" + name + "' not configured.");

  return config.get (key);
}

////////////////////////////////////////////////////////////////////////////////
// Obtain a set of queue names.
std::set <std::string> getQueueNames (const Configuration& config)
{
  std::set <std::string> names;
  for (const auto& item : config.all ())
  {
    if (item.substr (0, 6) == "queue.")
    {
      auto period = item.find (".", 6);
      if (period != std::string::npos)
        names.insert (item.substr (6, period - 6));
    }
  }

  return names;
}

////////////////////////////////////////////////////////////////////////////////
// Obtain a set of hook script names for a given queue.
std::set <std::string> getHookScriptNames (
  const Configuration& config,
  const std::string& name)
{
  std::string key = "hook." + name + ".";
  auto len = key.length ();

  std::set <std::string> names;
  for (const auto& item : config.all ())
    if (item.substr (0, len) == key)
      names.insert (item.substr (len));

  return names;
}

////////////////////////////////////////////////////////////////////////////////
