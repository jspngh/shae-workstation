#!/bin/bash

OPTIONS="--options=coding-conventions.astylerc"

RETURN=0
ASTYLE=$(which astyle)
if [ $? -ne 0 ]; then
	echo "[!] astyle not installed. Unable to check source file format policy." >&2
	exit 1
fi

FILES=`git diff --cached --name-only --diff-filter=ACMR | grep -E "\.(c|cpp|h)$"`
for FILE in $FILES; do
	$ASTYLE $OPTIONS < $FILE | cmp -s $FILE -
	if [ $? -ne 0 ]; then
		echo "[!] $FILE does not respect the agreed coding style." >&2
		RETURN=1
	fi
done

if [ $RETURN -eq 1 ]; then
	echo "" >&2
	echo "One or more files did not follow the coding conventions." >&2
	echo "Run the script \"refactor-code.sh\" to refactor the code then recommit." >&2
fi

exit $RETURN
