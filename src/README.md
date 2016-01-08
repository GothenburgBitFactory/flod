Queue
-----

Create a queue in /path/to/queue, and optionally record whether the event
files are archived. Name the queue Foo, which means it processes Foo events.

  $ queue create Foo [--path /path/to/queue] --[no]archive

Destroy a queue in /path/to/queue.

  $ queue destroy Foo
  $ queue destroy Foo --force

Flush a queue by archiving or deleting its events.

  $ queue clear Foo

Obtain info about a queue.

  $ queue info Foo

Associate a script with a queue. Will process all outstanding events.

  $ queue hook Foo /path/to/script

Disassociate a script from a queue. Will abandon all outstanding events.

  $ queue unhook Foo /path/to/script

Process a queue.

  $ queue process Foo [--exit-on-idle] [--max N]

Post an event.

  $ queue Foo /path/to/event


Configuration
-------------

By default, Flod will use a .flodrc file in the current directory, or traverse
the filesystem 'upwards' until it finds one, or hits a volume boundary. This
file can be overridden with the command line:

  $ queue ... --config $FILE

Or with an environment variable:

  FLODRC=$FILE queue ...

Command line override of individual setting:

  $ queue ... --NAME=VALUE

Command line configuration update:

  $ queue config NAME VALUE       # Set NAME to VALUE
  $ queue config NAME ''          # Set NAME to no value
  $ queue config NAME             # Delete NAME, reverting to default, if any


What is a queue?
----------------

A queue is a directory, in which event files are placed.

    my_queue/*
    my_queue/processing/*
    my_queue/archive/*

An event file would be composed and written in a work directory, then moved into
the 'my_queue' directory. It would not be written directly into 'my_queue',
because that could be processed before the write completes. This means queues
should be only writable by the owner, which is the user running flod, which will
prevent this problem.

An event will sit in the queue until it is processed, which is an unspecified
time, and dependent on whether the queue processor is running. The queue is
therefore a spool.

When an event file is to be processed, it is moved into the 'my_queue/processing'
directory. On successful completion, it moves into 'my_queue/archive'. On error
it moves back to 'my_queue'.

