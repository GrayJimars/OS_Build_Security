#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "keyboard.h"
#include "proto.h"

PUBLIC void* do_search() {
    // char* dir = fs_msg.buf; // "/"
    // memcpy(dir, fs_msg.buf, strlen(fs_msg.buf));
    // printl("dir = %s\n", dir);

    char filename[MAX_PATH];
    memset(filename, 0, MAX_FILENAME_LEN);
    struct inode* dir_inode;
    if (strip_path(filename, fs_msg.buf, &dir_inode) != 0) {
        printl("strip path error!\n");
        return (void*)0;
    }
    // After strip_path, we get
    // filename = "\0"
    // dir_inode = root_inode
    // printl("filename = %s\n", filename);
    // printl("inode = %d\n", dir_inode->i_num);

    // the start sector of root directory
    int dir_blk0_nr = dir_inode->i_start_sect;
    // let i_size be integer multiple SECTOR_SIZE
    int nr_dir_blks = (dir_inode->i_size + SECTOR_SIZE - 1) / SECTOR_SIZE;
    // printl("num of blocks: %d\n", nr_dir_blks);
    // num of entries
    int nr_dir_entries = dir_inode->i_size / DIR_ENTRY_SIZE;
    // printl("num of entries: %d\n", nr_dir_entries);

    int m = 0;
    struct dir_entry* pde;
    int pointer = 0;
    int i, j;
    // processing every dir_entry of every sector
    for (i = 0; i < nr_dir_blks; i++) {
        RD_SECT(dir_inode->i_dev, dir_blk0_nr + i);
        pde = (struct dir_entry* )fsbuf;
        for (j = 0; j < SECTOR_SIZE / DIR_ENTRY_SIZE; j++, pde++) {
            // save the file name into dir(msg.buf actually)
            memcpy(fs_msg.buf + pointer, pde->name, strlen(pde->name));
            // printl("%s\n", fs_msg.buf);
            pointer += strlen(pde->name);
            fs_msg.buf[pointer] = ' ';
            pointer += 1;
            if (++m > nr_dir_entries)
                break;
        }
        if (m > nr_dir_entries) 
            break;
    }
    fs_msg.buf[pointer] = '\0';
    return (void*)fs_msg.buf;
    
}
