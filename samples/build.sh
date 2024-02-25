#!/usr/bin/env bash
docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc gcc -O -c main.cpp test.cpp