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
#include <iostream> // TODO Remove

////////////////////////////////////////////////////////////////////////////////
// Create the queue directories, if they do not already exist.
// Set file permissions to owner-only.
void Q::create (const std::string& location)
{
  _location = location;

  Directory base (_location);
  if (! base.exists ())
    base.create (0700);

  Directory active (base);
  active += "active";
  if (! active.exists ())
    active.create (0700);

  Directory archive (base);
  archive += "archive";
  if (! archive.exists ())
    archive.create (0700);

  Directory failed (base);
  failed += "failed";
  if (! failed.exists ())
    failed.create (0700);
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
    else if (item.name != "active" ||
             item.name != "archive" ||
             item.name != "failed")
    {
      throw std::string {"Cannot remove queue - there are ㄡnrecognized contents."};
    }
  }

  // Recursively remove everything.
  return contents.remove ();
}

////////////////////////////////////////////////////////////////////////////////
// Scans the queue for new events
bool Q::scan (std::string& event)
{
  // Record 'before' state, for comparison.
  auto before = _snapshot;

  // TODO Scan _location
  Directory events (_location);
  for (const auto& entry : events.list ())
  {
    if (! Path (entry).is_directory ())
    {
      std::cout << "# Q::scan " << entry << "\n";

      // TODO If item is not in _snapshot
      //   TODO Add item to snapshot
      //   TODO event <-- item
      //   TODO return true
      // TODO If _snapshot contains missing item
      //   TODO Remove _snapshot item

      event = entry;
      return true;
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
