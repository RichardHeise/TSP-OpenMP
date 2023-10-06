make clean 
make
echo -n 'Running code...'
echo ''
time ./tspp < ../tests/$1.in
