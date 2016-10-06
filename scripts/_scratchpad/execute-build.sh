#1/bin/bash

apt-get update
apt-get -y install git build-essential cmake gnutls-dev uuid-dev python >> /tmp/01-aptget.txt   2>&1

git clone https://git.tasktools.org/scm/tm/taskd.git /opt/flod2/taskd   >> /tmp/02-gitclone.txt 2>&1
git clone https://git.tasktools.org/scm/tm/task.git  /opt/flod2/task    >> /tmp/02-gitclone.txt 2>&1

cd /opt/flod2/taskd
cmake .      >> /tmp/03-cmake.txt 2>&1
make install >> /tmp/04-make.txt  2>&1

cd /opt/flod2/task
git checkout 2.5.1 && cmake . >> /tmp/05-cmake.txt 2>&1
make                          >> /tmp/06-make.txt  2>&1
make test                     >> /tmp/07-test.txt  2>&1

touch /tmp/08-ready.txt
