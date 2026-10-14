#!/bin/bash

while true; do
	./r.out > inp
	./a.out < inp
	if [ $? -ne 0 ]; then
		echo "a.out caused a runtime error. Exiting..."
		break;
	fi
done
