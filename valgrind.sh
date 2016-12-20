#!/bin/bash

make && cd bin && valgrind --leak-check=yes ./ikaruga && cd ..
