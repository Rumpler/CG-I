#!/bin/bash

echo '- remove old html and latex folder';
rm -r ./html;
rm -r ./latex;

echo '- generate new documentation';
doxygen Doxyfile;

echo 'DONE';
