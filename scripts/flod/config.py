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

import flod

class Config(object):
  """Uses the 'central config' command to enumerate all settings, which are
     captured and loaded into a dict.
  """
  def __init__(self):
    self.data = dict()

    central = flod.Central()
    for line in central.config().split('\n'):
      if line != "":
        sep = line.index('=')
        self.data[line[:sep]] = line[sep + 1:]

  def get(self, name):
    """Return value given name."""
    return self.data[name] if name in self.data else ''

  def items(self):
    """Return header items, to allow k,v iteration."""
    return self.data.items()

