# Project 4

This project *litterally* builds upon the work you have done in all of the
previous projects! The goal, automate the build and set up of your admin
environment from which you will be able to remotely administer machines.

This process is often called *"bootstrapping"*. You will write a script
to bootstrap your admin environment completely. That way, if you ever
need to start working from another machine, you can simply re-run this
script on the new machine, and be up and running quickly.


## Fork the Repository

First, on the git server, begin by creating your own private clone of this
repository. At the top of this project page, click the fork button. It should
guide you through creating your own copy of this repository to work on.

***THIS IS KEY!***

*DO NOT* simply clone this repository, you don't have write permissions, so
you will not be able to push to this repository. You *HAVE* to fork!

**YOU'VE BEEN WARNED**

You may want to rename the repository when you fork it to something more
meaningful, like bootstrap, as you will be using this repository in the future
after you bootstrap your environment.

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


## Edit the Script

In this repository, you should find a starting `bootstrap.sh` file. This file
is similar to the `build_irssi.sh` script from the last project. It is actually
close to being done. It has some of the harder parts filled in already, like
downloading and verifying the source for python. You just need to set the
`PYTHON_VERSION` variable appropriately, and the rest should be good. The work
of downloading and verifying the python source has been moved as helper
functions into the aptly named `helper_funcs.sh` script. You shouldn't need to
modify anything in that script.

**Edit the HEADER COMMENT!** Update it to set *YOUR* name and email address
there as the author, and update the version number. Every time you update this
script in the future, update that version number.

*Pay attention to the TODO comments in bootstrap.sh!*

### Step One

So downloading the source is filled in for you. It downloads the source into
the directory pointed to by the `$SRC_DIR` variable. Make sure that variable
is set correctly.

The first step, unpack the python source somewhere, preferably somewhere in the
`$BUILD_DIR`. The reason we unpack and build in a separate directory, is that
it makes cleaning up after compiling easy. We know nothing important is in the
build directory that can't be easily re-created, so we can delete the whole
thing.

So, step one, unpack downloaded/verified tarball from it's location in the
`$SRC_DIR` to somewhere in `$BUILD_DIR`. (HINT: See the script comments)

Also, as a helper, there should be a variable named `$PYTHON_TAR` which
should be the name of the tarball file that was downloaded, so the full
path to the tar file that was downloaded should just be
`${SRC_DIR}/${PYTHON_TAR}`. You might want to run the untar command by hand
to see what the directory it creates is named, so that you can use the given
variables to know where to `cd` to for the next step.

### Step Two

Compile python. You all should be good at this, since you did it already for
your first project! Go back to your notes, and look at what steps you needed
to compile and install python.

Remember, you ***MUST*** override the installation path, and it ***MUST*** be
the path pointed to by `$INSTALL_ROOT`.

You can customize your compile options a bit if you want, but you need to
make sure that SSL is enabled, and ipv4 networking is enabled. We don't really
care if ipv6 is enabled, feel free to turn that off.

Also, as a hint, apparently the `configure` script has a -q flag to make that
process quieter, i.e. not output so much stuff.

Once python is compiled and installed into `$INSTALL_ROOT`, make sure it's
version is correct.

Figure out a way to capture the output of `$INSTALL_ROOT/bin/python -V` which
should be the installed python version number, and compare it to the version
number defined in `$PYTHON_VERSION`. If the two version numbers mismatch,
have the script exit! This is an error condition, something went wrong.

You can use the quit helper function to print a message and exit, like:

    quit "Installed version not as expected!"

Something along those lines. This test is **REQUIRED**! You will lose points
if it's not in there.

*HINT:* The output of python -V seems to go to stderr, so you may need to
redirect stderr into stdout in order to do anything with it. Research how to
do this in bash.

### Step Three

Now that your script is at the point where it downloads and installs a working
python interpreter, we need to install some third party python modules.

To do this, we will use `pip` the python package installer. The good news,
pip is now bundled with python. The bad news, it doesn't automatically install
a standalone pip command. You will need to tell python to directly run the
pip module, and use the pip module to install the latest version of pip.

This is important because it ends up installing the pip standalone command,
but it also updates pip to the latest version available (the bundled version
is a bit out of date).

*HINT* `python -m pip` is how you can run the built in pip module. Play with
it untill you can figure out the command line option to get pip installed
and upgraded to the latest version.

Put those commands in your script.

### Step Four

Now the your script downloads, builds, and installs python, and also updates pip
to the latest version available. The next step is to use the pip package 
manager to install the rest of our required tools.

Pip has a cool feature that lets you define in a text file, all of the packages
you want, and even define version requirements for them. This is often called
a *requirements* file. The repository has the starting point of a requirements
file in it.

For this step, you will update the requirements file so that it includes all
of the required third party modules and libraries. Then you will add a command
to your `bootstrap.sh` script to have pip install those requirements.

The requirements file in this repo is named `requirements.txt`. The one in this file is empty. Do some research on the internet on how to define requirements.

Any lines begining with `#` are comments. Any other lines are package names
with optional version number requirements.

For example:

    pip
    pip==8.0
    pip>=8.0
    pip<=9.0

The first one will install the latest available version of pip, the second,
installs exactly version 8.0, the second, installs any version greater than
or equal to 8.0, the last installs any version less than or equal to 9.0. There
are other options too, like for specifying just less than, just greater than,
or versions between ranges, etc. Look into it.

Once you have your mind wrapped around all of that. Update the
`requirements.txt` to make sure the following packages are installed:

* virtualenv        latest version
* virtualenv-clone  latest version
* virtualenvwrapper latest version
* Fabric            exactly version 1.12.0
* fabtools          exactly version 0.20.0
* Jinja2            any version greater than 2.8
* paramiko          exactly version 1.17.2
* ipython           any version greater than 5.1.0
* requests          any version greater than 2.7.0
* setuptools        latest version

Once you have those packages defined in your requirements.txt, update your
bootstrap script to pip install the requirements.txt file. You will need to
look at the `pip --help` options to see which flag lets you specify a
requirements file. Also, make sure you pass the upgrade flag in, so that if an
older version of a package is already installed, it will upgrade it to a newer
one if possible. **THIS IS KEY**, you will lose points if your bootstrap
script doesn't handle upgrades!

### Step Five

Now your script is nearly complete. It should download/verify, compile, install
python and all of the required packages we'll need. The last step is to go
over your script and make it a bit more efficient.

Lets say you boot strap your environment, but later, you want to update
something. Your script should before unpacking/compiling/installing python,
see if there is already a python installed in `$INSTALL_ROOT` that is the
version requested in the `$PYTHON_VERSION` variable. If it's already installed,
skip this step and move on to installing/upgrading the pip packages.

Before you try to tackle this step of verifying version number, make sure your
script is 100% up to this point. This should be the last step.

Once your script can automatically set up your admin environment, and it
does so efficiently, you're done! Commit all your changes and any additional
files you may need and push them up, then follow the submission steps in
the assignment.
