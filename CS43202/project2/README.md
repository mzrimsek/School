# Project `#2`

For this project, you need to clone this git repository somewhere with a posix
compatible shell to work on it. You should be able to log into *wasp* or *hornet*
to complete this assignment. You don't *HAVE* to work on it on those machines, but
you will need a working posix shell to test your changes.

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
start by logging onto the machine where you intend to work on this project.
Now, on the target machine where you will work, clone **YOUR** forked version
of this repository.

Once the git clone finishes, you can run `git remote -v` and it should show
you where you cloned it from. The remote URL should have *YOUR* username in
it. If you don't see *YOUR* username in the output of `git remote -v`, you
probably cloned the wrong repo! If that is the case *DO NOT PROCEDE*. Delete
the folder you just created with the git clone, go back to the previous
section, and make sure you forked, and that you are cloning your fork!

## Fix the Shell Script

Once you have your forked version cloned and ready to work on, you will find
a file at the top level named `fix_me.sh`. Essentially, open that file up,
and fix it. Read the comments, they will steer you towards what the script
needs to do.

Some things, there will be actual errors preventing the script from working,
some things, it will work, but not as intended, and you will need to make
it work as intended.

Make changes, test it that it *ACTUALLY RUNS*.

## Test the Script

Once you have the script functioning, and you're confident that you also
implemented missing functionality, find the script named `test_me.sh`.

Run that and it will test that you fixed everything correctly. If it reports
any errors, go back and fix them in the `fix_me.sh` script, and then test
again.

Once the `test_me.sh` reports that your script is 100%, commit all your
changes, and push your changes back up to your repository. I can then clone
your repository and verify your work.


## Submission

Simply go on blackboard, and post the *ssh* clone url of your repo.

