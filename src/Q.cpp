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
#include <Q.h>
#include <FS.h>
#include <text.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <sys/time.h>

//                                        0         1          2         3
std::vector <std::string> Q::structure = {"active", "archive", "failed", "staging"};

////////////////////////////////////////////////////////////////////////////////
// Create the queue directories, if they do not already exist.
// Set file permissions to owner-only.
void Q::create (const std::string& name, const std::string& location)
{
  _name = name;
  _location = location;

  Directory base (_location);
  if (! base.exists ())
    base.create (0700);

  for (const auto& item : structure)
  {
    Directory dir {base};
    dir += item;
    if (! dir.exists ())
      dir.create (0700);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Remove a queue, if possible.
bool Q::destroy (bool force)
{
  Directory contents (_location);

  // Contents in the queue prevent destruction unless 'force' is used.
  for (const auto& entry : contents.listRecursive ())
  {
    Path item (entry);
    if (! item.is_directory ())
    {
      if (! force)
        throw std::string {"Cannot remove queue that is not empty.  Use '--force'."};
    }
    else if (std::find (structure.begin (), structure.end (), item.name ()) == structure.end ())
    {
      throw std::string {"Cannot remove queue - there are unrecognized contents."};
    }
  }

  // Recursively remove everything.
  return contents.remove ();
}

////////////////////////////////////////////////////////////////////////////////
// Scans the queue for events to process, that are not listed in Q::structure.
bool Q::scan (std::string& event)
{
  Directory events {_location};
  for (const auto& item : events.list ())
  {
    if (std::find (Q::structure.begin (),
                   Q::structure.end (),
                   Path (item).name ()) == Q::structure.end ())
    {
      event = item;
      return true;
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
void Q::post (const std::string& event) const
{
  // Compose event prefix string: <name>.YYYYMMDDThhmmss.
  auto prefix = composeEventPrefix ();
  auto name = File (event).name ();
  std::string staging      = _location + "/staging/" + prefix + name;
  std::string destination  = _location + "/"         + prefix + name;

  // Detect collision in 'staging'.
  if (File (staging).exists ())
    throw std::string {"Staging area collision - unlikely, but it just happened."};

  // Detect collision in queue.
  if (File (destination).exists ())
    throw std::string {"Queued event collision - unlikely, but it just happened."};

  // The copy is expensive, the move is atomic.
  if (! File::copy (event, staging))
    throw std::string {"Failed to copy missing " + event};

  if (! File::move (staging, destination))
    throw std::string {"Failed to move " + staging + " to " + destination};
}

////////////////////////////////////////////////////////////////////////////////
// Move event from queued to active.
std::string Q::activateEvent (const std::string& event) const
{

  return event;
}

////////////////////////////////////////////////////////////////////////////////
// Move event from active to archive.
void Q::archiveEvent (const std::string& event) const
{
}

////////////////////////////////////////////////////////////////////////////////
void Q::clear ()
{
  Directory events (_location);
  for (const auto& entry : events.list ())
    if (! Path (entry).is_directory ())
      File (entry).remove ();
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::queue () const
{
  return events (_location);
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::active () const
{
  Directory queueDir (_location);
  queueDir += Q::structure[0];
  return events (queueDir._data);
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::archive () const
{
  Directory queueDir (_location);
  queueDir += Q::structure[1];
  return events (queueDir._data);
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::failed () const
{
  Directory queueDir (_location);
  queueDir += Q::structure[2];
  return events (queueDir._data);
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::staging () const
{
  Directory queueDir (_location);
  queueDir += Q::structure[3];
  return events (queueDir._data);
}

////////////////////////////////////////////////////////////////////////////////
// Compose event prefix string: <name>.YYYYMMDDThhmmss.
std::string Q::composeEventPrefix () const
{
  struct timeval nowus;
  gettimeofday (&nowus, nullptr);
  time_t now   = static_cast <time_t> (nowus.tv_sec);
  time_t usecs = static_cast <time_t> (nowus.tv_usec);
  struct tm* t = localtime (&now);

  std::stringstream prefix;
  prefix << _name
         << '.'
         << std::setw (4) << std::setfill ('0') << t->tm_year + 1900
         << std::setw (2) << std::setfill ('0') << t->tm_mon + 1
         << std::setw (2) << std::setfill ('0') << t->tm_mday
         << 'T'
         << std::setw (2) << std::setfill ('0') << t->tm_hour
         << std::setw (2) << std::setfill ('0') << t->tm_min
         << std::setw (2) << std::setfill ('0') << t->tm_sec
         << '.'
         << std::setw (6) << std::setfill ('0') << usecs
         << '.';

  return prefix.str ();
}

////////////////////////////////////////////////////////////////////////////////
std::vector <std::string> Q::events (const std::string& path) const
{
  std::vector <std::string> events;
  Directory queueDir (path);

  for (const auto& entry : queueDir.list ())
    if (! Path (entry).is_directory ())
      events.push_back (entry);

  return events;
}

////////////////////////////////////////////////////////////////////////////////
