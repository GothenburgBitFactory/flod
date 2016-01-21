////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2006 - 2016, Paul Beckingham, Federico Hernandez.
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
#include <inttypes.h>
#include <stdlib.h>
#include <FS.h>
#include <text.h>

////////////////////////////////////////////////////////////////////////////////
// Read the Configuration file and populate the *this map.  The file format is
// simply lines with name=value pairs.  Whitespace between name, = and value is
// not tolerated, but blank lines and comments starting with # are allowed.
//
// Nested files are now supported, with the following construct:
//   include /absolute/path/to/file
//
void Configuration::load (const std::string& file, int nest /* = 1 */)
{
  if (nest > 10)
    throw std::string ("Configuration files may only be nested to 10 levels.");

  // First time in, load the default values.
  if (nest == 1)
  {
    // This is where defaults would be set.
    _original_file = File (file);
  }

  // Read the file, then parse the contents.
  std::string contents;
  if (File::read (file, contents) && contents.length ())
    parse (contents, nest);
}

////////////////////////////////////////////////////////////////////////////////
void Configuration::parse (const std::string& input, int nest /* = 1 */)
{
  // Shortcut case for default constructor.
  if (input.length () == 0)
    return;

  // Parse each line.
  for (auto& line : split (input, '\n'))
  {
    // Remove comments.
    auto pound = line.find ("#");
    if (pound != std::string::npos)
      line = line.substr (0, pound);

    // Skip empty lines.
    line = trim (line);
    if (line.length () > 0)
    {
      auto equal = line.find ("=");
      if (equal != std::string::npos)
      {
        std::string key   = trim (line.substr (0, equal));
        std::string value = trim (line.substr (equal+1, line.length () - equal));

        (*this)[key] = jsonDecode (value);
      }
      else
      {
        auto include = line.find ("include");
        if (include != std::string::npos)
        {
          Path included (trim (line.substr (include + 7)));
          if (included.is_absolute ())
          {
            if (included.readable ())
              load (included, nest + 1);
            else
              throw format ("Could not read include file '{1}'.", included._data);
          }
          else
            throw format ("Can only include files with absolute paths, not '{1}'", included._data);
        }
        else
          throw format ("Malformed entry '{1}' in config file.", line);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
bool Configuration::has (const std::string& key)
{
  return (*this).find (key) != (*this).end ();
}

////////////////////////////////////////////////////////////////////////////////
// Return the configuration value given the specified key.
std::string Configuration::get (const std::string& key)
{
  return (*this)[key];
}

////////////////////////////////////////////////////////////////////////////////
int Configuration::getInteger (const std::string& key)
{
  if ((*this).find (key) != (*this).end ())
    return strtoimax ((*this)[key].c_str (), nullptr, 10);

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
double Configuration::getReal (const std::string& key)
{
  if ((*this).find (key) != (*this).end ())
    return strtod ((*this)[key].c_str (), nullptr);

  return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
bool Configuration::getBoolean (const std::string& key)
{
  if ((*this).find (key) != (*this).end ())
  {
    std::string value = lowerCase ((*this)[key]);
    if (value == "true"   ||
        value == "1"      ||
        value == "y"      ||
        value == "yes"    ||
        value == "on")
      return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
void Configuration::set (const std::string& key, const int value)
{
  (*this)[key] = format (value);
}

////////////////////////////////////////////////////////////////////////////////
void Configuration::set (const std::string& key, const double value)
{
  (*this)[key] = format (value, 1, 8);
}

////////////////////////////////////////////////////////////////////////////////
void Configuration::set (const std::string& key, const std::string& value)
{
  (*this)[key] = value;
}

////////////////////////////////////////////////////////////////////////////////
// Provide a vector of all configuration keys.
std::vector <std::string> Configuration::all () const
{
  std::vector <std::string> items;
  for (const auto& it : *this)
    items.push_back (it.first);

  return items;
}

////////////////////////////////////////////////////////////////////////////////
std::string Configuration::file () const
{
  return _original_file._data;
}

////////////////////////////////////////////////////////////////////////////////
