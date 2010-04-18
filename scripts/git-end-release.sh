#!/bin/sh
# Helper script start a release branch from dev
if [ ! $1 ]
then
    echo "First argument must be a release number (like '0.4.0')"
    exit
fi

git checkout master
git merge --no-ff rel_$1
git tag -a $1




