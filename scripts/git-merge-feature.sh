#!/bin/sh
# Helper script to merge feature back into the dev branch
# Uses --no-ff to keep all the commits inside the history
if [ ! $1 ]
then
    echo "Please give an argument"
    exit
fi

echo "Merging..."
git checkout dev
git merge --no-ff $1
echo "Deleting branch..."
git branch -D $1
echo "Pushing..."
git push origin dev




