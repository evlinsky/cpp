#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#pragma pack(push, 1)

struct BmpFileHeader {
  uint16_t type;
  uint32_t size;
  int32_t __reserved;
  uint32_t image_offset;
};

#pragma pack(pop)

void check_bfh_sanity(struct BmpFileHeader *bfh);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: ./bmp_demo <bmp file>\n");
    exit(EXIT_FAILURE);
  }

  FILE *bmp_file = fopen(argv[1], "rb"); // NB: 'b' flag
  assert(bmp_file);
  struct BmpFileHeader bfh;
  assert(fread(&bfh, sizeof(bfh), 1, bmp_file) == 1);
  printf("= BMP File Header =\n");
  printf("Type: 0x%x\nSize: %u\nOffset: %u\n",
         bfh.type, bfh.size, bfh.image_offset);
  // 'Move' to image data
  int seek_status = fseek(bmp_file, bfh.image_offset, SEEK_SET);
  assert(seek_status == 0);
}

void check_bfh_sanity(struct BmpFileHeader *bfh) {
  #define BMP_MAGIC_NUMBER 0x4d42
  assert(bfh->type == BMP_MAGIC_NUMBER);
  #undef BMP_MAGIC_NUMBER
}
