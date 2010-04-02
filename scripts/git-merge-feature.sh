#!/bin/sh
# Helper script to merge feature back into the dev branch
# Uses --no-ff to keep all the commits inside the history
delete() {
    echo "Deleting branch..."
    git branch -D $1
}

push() {
    echo "Pushing branch..."
    git push origin dev
}

skip() {
    echo
}

if [ ! $1 ]
then
    echo "Please give an argument"
    exit
fi

echo "Merging..."
git checkout dev
git merge --no-ff $1

echo "Do you want to delete the branch ? (y/n) [N]"
read REPLY
echo
case $REPLY in
    y | Y)
	delete
	;;
    n | N)
	skip
	;;
    *)
	skip
	;;
esac

echo "Do you want to push the branch ? (y/n) [N]"
read REPLY
echo
case $REPLY in
    y | Y)
	push
	;;
    n | N)
	skip
	;;
    *)
	skip
	;;
esac



