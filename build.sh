#!/bin/bash

cd src
./build-soush.sh || exit 1
cd ..

echo "Done!"