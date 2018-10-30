#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLK_SIZE 4096

struct super_block {
	unsigned int inodes_count;
	unsigned int blocks_count;
	unsigned int inode_size;
	unsigned int block_size;
	unsigned int disk_size;
	char label[10];
};

struct super_block* createSuperblock(unsigned int size, char label[]);
int terminal(FILE* hd);
int get_size(FILE* hd);
void mount(FILE* hd, char label[]);
FILE* mkfs(char file_name[], char label[]);

int main()
{
	int quit;
	FILE* hd = NULL;
	char label[10] = "Label";
	//char fname[20];
	//scanf("%s",fname);

	hd = fopen("file.bin", "r+");
	mount(hd, label);

	quit = terminal(hd);
	if (quit) {
		fclose(hd);
		exit(0);
	}
	return 0;
}

/*Superblock contructor*/
struct super_block* createSuperblock(unsigned int size, char label[])
{
	struct super_block* temp = (struct super_block*)malloc(sizeof(struct super_block));
	strcpy(temp->label, label);
	temp->blocks_count = size / BLK_SIZE;
	temp->block_size = BLK_SIZE;
	temp->disk_size = size;
	temp->inode_size = 256;
	temp->inodes_count = (size / 10) / 256;
	return temp;
}

int terminal(FILE* hd)
{
	char arg1[10], arg2[10], arg3[10];
	while (1) {
		printf(">");
		scanf("%s", arg1);
		if (strcmp(arg1, "mkfs") == 0) {
			mkfs("file.bin",arg2);
		}

		else if (strcmp(arg1, "mount") == 0) {
			mount(hd, arg2);
		}

		else if (strcmp(arg1, "quit")) {
			return 1;
		}
		else {
			printf("\"%s\" command not found, use quit to exit the system \n", arg1);
		}
	}
}

/*Returns the size of the file*/
int get_size(FILE* hd)
{
	int size;

	fseek(hd,0,SEEK_END);
	size = ftell(hd);
	fseek(hd,0,SEEK_SET);

	return size;
}

FILE* mkfs(char file_name[], char label[])
{
	FILE* hd = NULL;

	hd = fopen(file_name, "r+b");

	return hd;
}

/*Mounts the disk*/
void mount(FILE* hd, char label[])
{
	int size;

	printf("Mounting the disk\n_ _ _ _ _ _ _ _ _ _ _ \n");
	size = get_size(hd);

	struct super_block* sb = createSuperblock(size,label);
	fwrite(sb, sizeof(struct super_block), 1, hd);
}

