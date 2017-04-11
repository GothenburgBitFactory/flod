# Flod2 - Lightweight Continuous Integration

Flod2 uses the simplest, most flexible technology to create a CI solution that
uses minimal resources, yet delivers build status as fast as possible.


## Design

Flod consists of one main component, and a set of focussed support scripts.

The 'central' binary is a queue management tool that triggers hook scripts when
event files are queued. Central can create, destroy, hook, unhook and process
queues. Central knows nothing about CI, but does know how to manage workflow.

The most important of the scripts is the 'build_vm' script, which instantiates
a new VM, provisions that VM, then builds and tests the project, queueing the
results.

The combined effect of queues and hook scripts is a graph of dependent
functionality that implements the complex workflow of CI.


## Workflow

   git        +------+      +------+      +------+      +------+      +------+      +-------+
   commit --> |change| -+-> |build | -+-> |result| ---> |digest| -+-> |clean | -+-> |publish|
              |      |  |   | P1   |  |   |      |      |      |  |   |      |  |   |       |
              +------+  |   +------+  |   +------+      +------+  |   +------+  |   +-------+
                        |             |                           |             |
                        |   +------+  |                           +-------------+
                        +-> |build | -+
                        |   | P2   |  |
                        |   +------+  |
                        |             |
                        |   +------+  |
                        +-> |build | -+
                            | P3   |
                            +------+

## Git: commit

When a project commit is made, either a 'post-commit' or 'post-receive' git
hook script composes and posts a change event.


## Queue: change

The 'platforms' script is triggered by a change event. Using a combination of
details in the change event and central configuration, it determines the set of
supported platforms, and their associated details and commands.

A build event is created for each platform, and queued in the corresponding
build_{platform} queue.


## Queue: build_{platform}

The 'build_local', 'build_remote', or 'build_vm' script is triggered by a build
event, depending on which script was used to hook build events.

The 'build_local' script is the simplest, and it creates a work directory, then
clones the project, builds and tests it. The combined log of all this is added
as the payload in a result event which is queued.

The 'build_remote' script does all this on a remote machine.

The 'build_vm' script does all the above but instantiates and provisions a VM,
then destroys it afterwards. This script may also simply power up an already
created VM and power it down afterwards.

The three scripts generate identical result events. It is important that a
complete capture of all commands is in the result. This allows an upgraded
central to re-process results when new capabilities are added. In the case of
'build_vm', the full log is needed because the VM may no longer exist, and
diagnosis is more difficult.


## Queue: result

The 'thresher' script is triggered by a result event, and has the task of
separating the wheat from the chaff. This means taking a full build transcript,
and reducing it to only the interesting parts, which includes warnings, errors
and test results. This result is a digest event.


## Queue: digest

A digest event triggers two scripts. The first is a report script, which builds
the tinderbox report. It stores the thresher results in a platform file. It
then combines platform files into a commit file, representing the results for
all platforms for a specific commit. Then it combines commit files into a full
report. The resulting HTML file path is referenced in a publish event.

If the commit result across all platforms is considered good, then a 'clean'
event is posted.

The second is the summary script, which creates the overall summary page you
see on https://central.tasktools.org. This too is added as payload to a
report, which is referenced in a publish event.


## Queue: clean

A clean event triggers two scripts. The first is a coverage script, which runs
a coverage tool, generating a coverage report, which is then queued for
publishing.

The second script is a snapshot script that creates a snapshot tarball, which
is referenced in a publish event.


## Queue: publish

A publish event triggers an rsync/scp of a file in the event, to a web server.

---
