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






What is a queue?
----------------

A queue is a directory, in which event files are placed.

    my_queue/*
    my_queue/processing/*
    my_queue/archive/*


Configuration
-------------


