# Make run summary

make_run_summary is a simple script that produces a
nice table with the informations on the
runs since the beginning of the shift by collecting the information
from the "New run" entries of the elog.
Can be useful for the end of shift report.

## Installation

This code can be run at KEKCC or on any computer with Linux and python2/3

to install it clone the repository and make `make_runs_summary` executable
```
git clone https://gdujany@stash.desy.de/scm/~gdujany/make_runs_summary.git
cd make_runs_summary
chmod 755 make_runs_summary
```

## Usage

Typical use is `./make_run_summary`

To see the options avalable do `./make_run_summary -h`
