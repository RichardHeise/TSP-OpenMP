make clean 
make
echo -n 'Running code...'
echo ''
time ./tsp < ../tests/$1.in
