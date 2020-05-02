//
// Created by mac12 on 17/03/2020.
//

#ifndef SHOOTERC_TYPES_H
#define SHOOTERC_TYPES_H

#include <stdint.h>

typedef struct {
    // Inode Info
    uint32_t inodesCount;
    uint32_t freeInodesCount;
    uint32_t inodesGroup;
    uint32_t inodeSize;
    uint32_t firstInode;

    // Block Info
    uint32_t blockCount;
    uint32_t freeBlockCount;
    uint32_t reservedBlocksCount;
    uint32_t firstDataBlock;
    uint32_t blocksGroup;
    uint32_t blockSize;
    uint32_t fragsGroup;

    // Volume Info
    char volumeName[16];
    uint32_t lastCheck;
    uint32_t lastMounted;
    uint32_t lastWritten;
} Ext2Volume;

struct ext2_super_block {
    unsigned int   s_inodes_count;      /* Inodes count */
    unsigned int   s_blocks_count;      /* Blocks count */
    unsigned int   s_r_blocks_count;    /* Reserved blocks count */
    unsigned int   s_free_blocks_count; /* Free blocks count */
    unsigned int   s_free_inodes_count; /* Free inodes count */
    unsigned int   s_first_data_block;  /* First Data Block */
    unsigned int   s_log_block_size;    /* Block size */
    unsigned int   s_log_frag_size;     /* Fragment size */
    unsigned int   s_blocks_per_group;  /* # Blocks per group */
    unsigned int   s_frags_per_group;   /* # Fragments per group */
    unsigned int   s_inodes_per_group;  /* # Inodes per group */
    unsigned int   s_mtime;             /* Mount time */
    unsigned int   s_wtime;             /* Write time */
    unsigned short s_mnt_count;         /* Mount count */
    unsigned short s_max_mnt_count;     /* Maximal mount count */
    unsigned short s_magic;             /* Magic signature */
    unsigned short s_state;             /* File system state */
    unsigned short s_errors;            /* Behaviour when detecting errors */
    unsigned short s_minor_rev_level;   /* minor revision level */
    unsigned int   s_lastcheck;         /* time of last check */
    unsigned int   s_checkinterval;     /* max. time between checks */
    unsigned int   s_creator_os;        /* OS */
    unsigned int   s_rev_level;         /* Revision level */
    unsigned short s_def_resuid;        /* Default uid for reserved blocks */
    unsigned short s_def_resgid;        /* Default gid for reserved blocks */
    /*
     * These fields are for EXT2_DYNAMIC_REV superblocks only.
     *
     * Note: the difference between the compatible feature set and
     * the incompatible feature set is that if there is a bit set
     * in the incompatible feature set that the kernel doesn't
     * know about, it should refuse to mount the filesystem.
     *
     * e2fsck's requirements are more strict; if it doesn't know
     * about a feature in either the compatible or incompatible
     * feature set, it must abort and not try to meddle with
     * things it doesn't understand...
     */
    unsigned int   s_first_ino;         /* First non-reserved inode */
    unsigned short s_inode_size;        /* size of inode structure */
    unsigned short s_block_group_nr;    /* block group # of this superblock */
    unsigned int   s_feature_compat;    /* compatible feature set */
    unsigned int   s_feature_incompat;  /* incompatible feature set */
    unsigned int   s_feature_ro_compat; /* readonly-compatible feature set */
    unsigned char  s_uuid[16];          /* 128-bit uuid for volume */
    char           s_volume_name[16];   /* volume name */
    char           s_last_mounted[64];  /* directory where last mounted */
    unsigned int   s_algorithm_usage_bitmap; /* For compression */
    /*
     * Performance hints.  Directory preallocation should only
     * happen if the EXT2_COMPAT_PREALLOC flag is on.
     */
    unsigned char  s_prealloc_blocks;     /* Nr of blocks to try to preallocate*/
    unsigned char  s_prealloc_dir_blocks; /* Nr to preallocate for dirs */
    unsigned short s_padding1;
    /*
     * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
     */
    unsigned char  s_journal_uuid[16]; /* uuid of journal superblock */
    unsigned int   s_journal_inum;     /* inode number of journal file */
    unsigned int   s_journal_dev;      /* device number of journal file */
    unsigned int   s_last_orphan;      /* start of list of inodes to delete */
    unsigned int   s_hash_seed[4];     /* HTREE hash seed */
    unsigned char  s_def_hash_version; /* Default hash version to use */
    unsigned char  s_reserved_char_pad;
    unsigned short s_reserved_word_pad;
    unsigned int   s_default_mount_opts;
    unsigned int   s_first_meta_bg; /* First metablock block group */
    unsigned int   s_reserved[190]; /* Padding to the end of the block */
};


struct ext2_group_desc
{
    unsigned int   bg_block_bitmap;      /* Blocks bitmap block */
    unsigned int   bg_inode_bitmap;      /* Inodes bitmap block */
    unsigned int   bg_inode_table;       /* Inodes table block */
    unsigned short bg_free_blocks_count; /* Free blocks count */
    unsigned short bg_free_inodes_count; /* Free inodes count */
    unsigned short bg_used_dirs_count;   /* Directories count */
    unsigned short bg_pad;
    unsigned int   bg_reserved[3];
};

struct ext2_inode {
    unsigned short i_mode;        /* File mode */
    unsigned short i_uid;         /* Low 16 bits of Owner Uid */
    unsigned int   i_size;        /* Size in bytes */
    unsigned int   i_atime;       /* Access time */
    unsigned int   i_ctime;       /* Creation time */
    unsigned int   i_mtime;       /* Modification time */
    unsigned int   i_dtime;       /* Deletion Time */
    unsigned short i_gid;         /* Low 16 bits of Group Id */
    unsigned short i_links_count; /* Links count */
    unsigned int   i_blocks;      /* Blocks count IN DISK SECTORS*/
    unsigned int   i_flags;       /* File flags */
    unsigned int   osd1;          /* OS dependent 1 */
    unsigned int   i_block[15];   /* Pointers to blocks */
    unsigned int   i_generation;  /* File version (for NFS) */
    unsigned int   i_file_acl;    /* File ACL */
    unsigned int   i_dir_acl;     /* Directory ACL */
    unsigned int   i_faddr;       /* Fragment address */
    unsigned int   extra[3];
};

typedef struct {
    uint32_t inode;
    uint16_t recordLength;
    unsigned char nameLength;
    unsigned char fileType;
    char fileName[255];
} Ext2Directory;

typedef struct {
    unsigned long i_mode;
    unsigned long i_uid;
    unsigned long i_size;
    unsigned long i_atime;
    unsigned long i_ctime;
    unsigned long i_mtime;
    unsigned long i_dtime;
    unsigned long i_gid;
    unsigned long i_links_count;
    unsigned long i_blocks;
    unsigned long i_flags;
    unsigned long i_osd1;
    unsigned long i_block[15];
    unsigned long i_generation;
    unsigned long i_file_acl;
    unsigned long i_dir_acl;
    unsigned long i_faddr;
    unsigned long i_osd2;
} InodeEntry;

typedef struct {
    char systemName[8];
    uint16_t sectorSize;
    uint8_t sectorCluster;
    uint16_t reservedSectors;
    uint8_t numberFats;
    uint16_t rootEntries;
    uint32_t sectorsFat;
    char volumeName[12];
} FAT16Volume;

typedef struct {
    char name[12];
    char extension[4];
    unsigned char fileAttribute;
    uint16_t reserved;
    uint16_t time;
    uint16_t date;
    uint16_t firstCluster;
    uint32_t size;
} FAT16Directory;


#endif //SHOOTERC_TYPES_H
