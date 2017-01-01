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
import subprocess

class Central(object):
  """Communicates with central."""

  def post(self, queue, event):
    """Serialize the event, and post the file to the queue."""
    temp_name = event.save()
    out, err = subprocess.Popen(["central", "post", queue, temp_name], stdout=subprocess.PIPE, stderr=subprocess.STDOUT).communicate()
    # TODO Do something with errors.
    os.unlink(temp_name)

  def config(self):
    """Generate a list of all configuration settings, return as a single string."""
    return subprocess.Popen(["central", "config"], stdout=subprocess.PIPE).communicate()[0]

