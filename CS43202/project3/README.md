# Project `#3`

This project will build upon your knowledge from the previous two projects!
Using your knowledge of how to download, build and compile software,
combined with your knowledge of shell scripts, you will build (or actually
modify) a shell script which will automatically download some software,
build it, and install it.

## Fork the Repository

First, on the git server, begin by creating your own private clone of this
repository. At the top of this project page, click the fork button. It should
guide you through creating your own copy of this repository to work on.

***THIS IS KEY!***

*DO NOT* simply clone this repository, you don't have write permissions, so
you will not be able to push to this repository. You *HAVE* to fork!

**YOU'VE BEEN WARNED**


## Getting Started

Once you have forked this repository, and you have your very own copy of it,
start by logging onto the departmental machine where you intend to install
the software you will be compiling for this project.

Now, on the target machine where you will work, clone **YOUR** forked version
of this repository.

Once the git clone finishes, you can run `git remote -v` and it should show
you where you cloned it from. The remote URL should have *YOUR* username in
it. If you don't see *YOUR* username in the output of `git remote -v`, you
probably cloned the wrong repo! If that is the case *DO NOT PROCEDE*. Delete
the folder you just created with the git clone, go back to the previous
section, and make sure you forked, and that you are cloning your fork!


## Download and Compile irssi

Before you go and start working on this script, first find the source for
irssi, download it, and try compiling it manually.

Get an idea for the process. Don't install it, just run through the download,
unpack, and compile steps a few times until you know how to do that easily.

Once you know what you're doing, you can move on.


## Edit the Script

Once you know how to download, configure, and compile irssi, take a look at the
`build_irssi.sh` script. Some of the parts are filled out already, some you
just need to modify, other parts, you need to write completely your self!

Everywhere modifications are needed, you'll see a **TODO** comment before it
spelling it out for you.


## Test Your Script

Run your script. It should download the correct version of irssi, compile and
install it. And then once installed, it should verify the install (unless you
broke the script horribly). If it passes all of the tests at the end of the
script (you get all "ok" output). Then you are done. Go a head an commit all
your changes and push them up to the git server.


## Submission

Simply go on blackboard, and post the *ssh* clone url of your repo.

