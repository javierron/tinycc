set -x
set -e

#if fail run this command
trap 'git checkout subverted' ERR

cp attack_template.c attack.c
./generate-attack-array < attack.c > attack-array.h
cat attack.c >> attack-array.h 
mv attack-array.h attack.c

git commit -s -a -m "attack"

./configure --cpu=x86_64 --cc=gcc
make clean
make
sudo make install

git checkout good
./configure --cpu=x86_64 --cc=tcc
make clean
make
sudo make install
rm -f attack-tmp.c
