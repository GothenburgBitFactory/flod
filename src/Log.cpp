////////////////////////////////////////////////////////////////////////////////
// flod - grid testing
//
// Copyright 2012 - 2016, Göteborg Bit Factory.
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
#include <Log.h>
#include <thread>
#include <mutex>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <text.h>

std::mutex logSerializer;

////////////////////////////////////////////////////////////////////////////////
Log::~Log ()
{
  if (_fh)
    fclose (_fh);
}

////////////////////////////////////////////////////////////////////////////////
void Log::setFile (const std::string& path)
{
  _filename = path;
}

////////////////////////////////////////////////////////////////////////////////
void Log::write (const std::string& line, bool multiline /* = false */)
{
  // Handle multilines by splitting and recursing.
  if (multiline)
  {
    auto lines = split (line, '\n');
    for (const auto& line : lines)
      write (line, false);
    return;
  }

  std::lock_guard<std::mutex> lock (logSerializer);

  if (line != "")
  {
    if (line == _prior)
    {
      ++_repetition;
    }
    else
    {
      _prior = line;

      if (! _fh)
        _fh = fopen (_filename.c_str (), "a");

      if (_fh)
      {
        timestamp ();

        if (_repetition)
        {
          fprintf (_fh, "%s (Repeated %d times)\n", _now, _repetition);
          _repetition = 0;
        }

        fprintf (_fh, "%s %s\n", _now, line.c_str ());
      }

      fclose (_fh);
      _fh = nullptr;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
void Log::format (const char* message, ...)
{
  // Crude and mostly ineffective check for buffer overrun.
  if (::strlen (message) >= 65536)
    throw std::string ("ERROR: Data exceeds 65,536 bytes.  Break data into smaller chunks.");

  char buffer[65536];
  va_list args;
  va_start (args, message);
  vsnprintf (buffer, 65536, message, args);
  va_end (args);

  std::string copy = buffer;
  write (copy);
}

////////////////////////////////////////////////////////////////////////////////
void Log::timestamp ()
{
  // Get time info, UTC.
  time_t current;
  time (&current);
  struct tm* t = gmtime (&current);

  // Generate timestamp.
  sprintf (_now, "%04d-%02d-%02d %02d:%02d:%02d",
                 t->tm_year + 1900,
                 t->tm_mon + 1,
                 t->tm_mday,
                 t->tm_hour,
                 t->tm_min,
                 t->tm_sec);
}

////////////////////////////////////////////////////////////////////////////////
