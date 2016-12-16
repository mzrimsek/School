# CS43202 Final Project

This is the base repository for the final project for CS43202.

## Contents of this Repository

* INSTALL.md

    * File to be filled out by student detailing how to use their selected
      automation tool in order to deploy application for final project.

* requirements.txt

    * Requirements for the tools used in this repository, install with 
      `pip install -r` in your environment on wasp/hornet.

* ansible/

    * This directory contains the starting point to a working ansible setup.
      Edit the files contained in here as needed.

* fabric/

    * This directory contains the starting point to a working fabric setup.
      Edit the files contained in here as needed.


## Verifying Your Work

The example Fabric `fabfile.py` in the fabric directory has an extra task
named `verifydeploy` that you can use (even if you used ansible for your
project) to verify that your deploy works. You just `cd` into the fabric
directory, and run:

    fab verifydeploy

And you should see some fabric non-sense and if your application deployed
correctly, you should also see a quote returned from the application.

You can probably also implement a similar check in ansible if you use that
using the `uri` module.
