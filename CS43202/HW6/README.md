# Homework 6

In homework 6 we will be using our ssh key and an ssh jump host to connect to
a container on a hidden network. Once there, we will be creating a script that
bootstraps the server to a minimal set up that you can then finish configuring
remotely.

The idea is that you normally want to automate the configuration of a server,
and idealy you use tools remotely. But before you can use those types of tools,
there are some minimal requirements, like a user account and credentials to
log in with, maybe some base software packages, etc.

Also, we will be configuring servers that are not directly accessible, so we'll
need to use an ssh *jump* host.


## What you'll find in this repository

1. `ssh_config` - A sample ssh config file you can use.

2. `cloud_init.sh` - A starting point for a script to initialize your server.


### ssh config

Copy the `ssh_config` file to `~/.ssh/config` or just copy some of the lines
in the file as you see fit (if you already have an ssh config).

Feel free to modify the lines as needed, obviously you'll need to change the
IdentityFile lines to be the path to *YOUR* ssh key.


### cloud init script

Read the comments, see the examples. Copy it to your container with `scp`.
Once in your container, run it to test that it works as expected.
