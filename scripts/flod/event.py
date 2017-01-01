#!/usr/bin/env python
# -*- coding: utf-8 -*-
################################################################################
##
## Copyright 2012 - 2017, Göteborg Bit Factory.
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included
## in all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
## OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
## THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##
## http://www.opensource.org/licenses/mit-license.php
##
################################################################################

import os
import tempfile

class Event(object):
  """Reads and writes event files."""
  def __init__(self):
    self.headers = dict()
    self.body = ''

  def load(self, file):
    """Load an event file and populate the header dict and body string."""
    self.headers = dict()
    self.body = ''
    in_headers = True
    with open(file) as fh:
      for line in fh:
        if line == "\n":
          in_headers = False
        elif in_headers:
          sep = line.index(': ')
          self.headers[line[:sep]] = line.strip()[sep + 2:]
        else:
          self.body += line

  def save(self):
    """Write the headers and body to a temp file, and return the file name."""
    temp_fh, temp_name = tempfile.mkstemp()

    for k, v in self.headers.items():
      os.write(temp_fh, '{}: {}\n'.format(k, v))

    os.write(temp_fh, '\n')
    os.write(temp_fh, self.body)
    if self.body != '' and not self.body.endswith('\n'):
      os.write(temp_fh, '\n')

    os.close(temp_fh)
    return temp_name

  def header(self, name, value=None):
    """Return the header named value, or an empty string if it does not exist."""
    if value is not None:
      self.headers[name] = value
    else:
      return self.headers[name] if name in self.headers else ''

  def payload(self, value=None):
    """Return the body as a single string."""
    if value is not None:
      self.body = value
    else:
      return self.body

  def has(self, name):
    """Indicate whether name is found in the header dict."""
    return name in self.headers

  def items(self):
    """Return header items, to allow k,v iteration."""
    return self.headers.items()

