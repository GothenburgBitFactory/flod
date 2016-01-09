# Queue

Create a queue in /path/to/queue, and optionally record whether the event
files are archived. Name the queue Foo, which means it processes Foo events.

  $ queue create Foo /path/to/queue --[no]archive

Destroy a queue in /path/to/queue.

  $ queue destroy Foo [--force]

Flush a queue by archiving or deleting its events.

  $ queue clear Foo

Obtain info about a queue.

  $ queue info Foo

Obtain queue stats, reset stats.

  $ queue stats Foo
  $ queue stats reset Foo

Associate a script with a queue. Will process all outstanding events.

  $ queue hook Foo /path/to/script [--scan 60]
  $ queue hook Foo success /path/to/script
  $ queue hook Foo failure /path/to/script

Disassociate a script from a queue. Will abandon all outstanding events.

  $ queue unhook Foo /path/to/script

Process a queue.

  $ queue process Foo [--exit-on-idle] [--max N]

Post an event.

  $ queue post Foo /path/to/event


## Configuration

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


## What is a queue?

A queue is a directory, in which event files are placed.

    my_queue/*
    my_queue/active/*
    my_queue/archive/*
    my_queue/failed/*

An event file is composed and written in a work directory, then moved into the
'my_queue' directory. It is not written directly into 'my_queue', which could
mean it is processed before the write completes. Queues are only writable by
the owner, which is the user running flod.

An event will sit in the queue until it is processed, which is dependent on
whether the queue processor is running and whether the queue is hooked. The
queue is therefore a spool.

When an event file is processed, it is moved into the 'my_queue/active'
directory. On successful completion, it moves into 'my_queue/archive'. On error
it moves to 'my_queue/failed'.


## What is an event file?

An event file is a text file based on RFC2822 [1]. It consists of a set of
headers KV pairs, and a body. Here is an example:

    name: value<CRLF>                 | header section
    width: 3<CRLF>                    |
    <CRLF>
    body                              | optional body

The header section is a set of KV pairs that comprise the metadata that is in
every event file.


## Event File Types

There are several types of even files, and the actual header/body contents are
type-specific, but are independent of the queue system. Instead, event file
types are described by the direct producers and consumers, which are the hook
scripts that are attached to queues.


## Example Usage

Create and hook a queue:

  $ queue create Foo /var/queue/foo
  $ queue hook Foo /path/to/script
  $ queue stats clear Foo

Launch a queue processor:

  $ queue process Foo

Queue an event file:

  $ queue Foo /path/to/event


## References

[1] RFC2822 - https://tools.ietf.org/html/rfc2822

