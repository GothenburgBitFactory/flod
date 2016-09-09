# Flod2 - Lightweight Continuous Integration

Flod2 uses the simplest, most flexible technology to create a CI solution that
uses minimal resources, yet delivers build status as fast as possible.


## Design

Flod consists of two main components.

The first is the flod binary, and is a queue management tool that triggers hook
scripts when event files appear in a queue, calling the script with a reference
to the event file and managing that file. The flod binary knows nothing about
CI, it only knows that events appear in queues, which are then processed by
hook scripts, which succeed or fail.

The second component manages a single VM instance.  It creates it, then can
install tools and libraries on it, copies a build script to it, and runs that
build script. It waits for a result event to appear, and then shuts down the
VM.

Everything else is a small script that is launched based on events triggering
hooks, each script having a small and well-defined purpose.

The combined effect is that a single commit will launch multiple VMs that test
that commit, yielding several results events, which contribute to a status
report. Then the VMs will be shut down and the system returns goes idle,
thereby using minimal resources.

There may be many scripts involved, using many queues.


## Workflow

1. A repository commit (task.git) triggers a VCS hook (git on-push) that
   composes and queues a commit-event file. This needs to be a very fast
   operation. The commit-event file identifies the repository, branch, and a
   range of commits.

2. A commit-event triggers a portability-build script that uses stored
   configuration to enumerate supported platforms and composes a build-event
   file tailored for each platform. The VM instance component is run, with
   the build-event file.

3. The VM instance component creates a VM, installs software, installs a
   build/test/report script, then runs that. It then waits for a result event
   file to appear, shuts down the VM and queues the results event.

4. The result-event triggers a report script that (in an undefined way)
   creates a status report of the commit.

There are other steps/events/scripts, for example, HTML report aggregation,
project overview report creation, performance testing on good builds, result
event archiving, tarball creation and so on.


## Data Storage

There needs to be a hierarchy constituting project/branch/commit/platform,
where result events are stored permanently.

All events should be archived. Archived events may be purged later.


## Configuration

There needs to be platform-specific configuration, including:

1. Platform-specific depdendencies, for example the presence of a 'libuuid'
   library is necessary on Fedora, but not on OSX.

2. Project-specific configuration, for example a sequence of commands to run
   in order to build and test a project.

3. Permanent queue details, such as a location, and set of triggered scripts.


## Example System

Recreating and extending the functionality of Flod 0.x requires creating
several queues and hook scripts.

   Queue   |  Mechanism
   --------|---------------------------------------------------------------
   commit  |  Source:   'git commit' hooks identify project, branch, commit
           |  Triggers: platform script that forwards the message to the
           |            build-* queues for each platform
           |
   build-P |  Source:   platform script
           |  Triggers: VM manager for platform P
           |
   result  |  Source:   build script on platform P provides results from
           |            each of the clone/prebuild/build/test steps
           |  Triggers: aggregator script that composes a tinderbox report
           |            fragment for the project/branch/commit, and posts a
           |            message to the 'report' queue
           |  Triggers: clean build detector, that identified project/branch
           |            commit that passes 100% tests on all platforms, and
           |            posts a message to the 'tarball' queue
           |
   report  |  Source:   aggregator script
           |  Triggers: assembly script that combines report fragments into
           |            an HTML page which is copied to the web server
           |            docroot
           |
   tarball |  Source:   clean build aggregator that identifies builds that
           |            should be made into snapshot tarballs
           |  Triggers: tarball creation and release script

This arrangement would permit a git hook to notify Flod of a commit on a branch
of a project, which would in turn cause multiple VMs to be started to build the
project on various platforms, the results of which are combined in a report
with clean builds automatically creating snapshot tarballs. Map reduce.


              +------+      +------+      +------+      +------+      +------+
   Commit --> |commit| -+-> |build | -+-> |result| ---> | test | -+-> | tar  |
              |      |  |   | P1   |  |   |      |      |report|  |   | ball |
              +------+  |   +------+  |   +------+      +------+  |   +------+
                        |             |                           |
                        |   +------+  |                           |   +------+
                        +-> |build | -+                           +-> | gcov |
                        |   | P2   |  |                               |report|
                        |   +------+  |                               +------+
                        |             |
                        |   +------+  |
                        +-> |build | -+
                            | P3   |
                            +------+

