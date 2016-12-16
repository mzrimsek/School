#!/bin/bash

#This causes the script to exit on any failure
set -e

#variables
USERNAME="mzrimsek"

SSHDIR="/home/${USERNAME}/.ssh"
SSHKEYFILE="${SSHDIR}/authorized_keys"
SSHKEY="ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIHhmLH6kF5uEY8bIdyw0uf8R7dvHKe5a+OKRQoNaWBdK mzrimsek@kent.edu"

SUDOERS="${USERNAME} ALL=NOPASSWD:ALL"
SUDOERSFILE="/etc/sudoers.d/${USERNAME}"

#functions
user_exists () {
    getent passwd | grep -q $1
}

quit() {
    printf "$1\n"
    exit
}

#create user if necessary...quit if failed
user_exists ${USERNAME} || adduser ${USERNAME}
user_exists ${USERNAME} || quit "Error creating user!"

#ssh stuff for new user
if [ ! -d ${SSHDIR} ]; then
    mkdir -p ${SSHDIR}
fi

echo ${SSHKEY} >> ${SSHKEYFILE}
chmod 440 ${SSHKEYFILE}

chown ${USERNAME} ${SSHDIR}
chown ${USERNAME} ${SSHDIR}/authorized_keys

#install required packages
yum -y install epel-release && yum clean all && yum -y upgrade
yum -y install sudo vim python rpm-python curl wget openssh openssh-clients openssh-server git puppet
yum update

#create sudoers entry
echo ${SUDOERS} >> ${SUDOERSFILE}
chmod 440 ${SUDOERSFILE}
