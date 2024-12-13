# super block
echo "super block:"
xxd -u -a -g 1 -c 16 -s 0x9E0000 -l 64 80m.img
echo

# inode-map
echo "inode-map:"
xxd -u -a -g 1 -c 16 -s 0x9E0200 -l 32 80m.img
echo

# sector-map
# echo "sector-map:"
# xxd -u -a -g 1 -c 16 -s 0x9E0400 -l 512 80m.img
# echo

# inode-array
echo "inode-array:"
xxd -u -a -g 1 -c 16 -s 0x9E1800 -l 512 80m.img
echo 

# root directory
echo "root directory:"
xxd -u -a -g 1 -c 16 -s 0xA01800 -l 512 80m.img