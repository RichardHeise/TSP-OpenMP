make clean 
make
echo -n 'Running code...'
echo ''
./tspp < ../tests/$1.in
