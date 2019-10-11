#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

void print_usage() {
  fprintf(stdout, "Usage: ./demo (rt|wt|rb|wb|mx) <file_name> [args]\n");
}

int streq(const char *s1, const char *s2) {
  return strcmp(s1, s2) == 0;
}

void read_text(const char *fname);
void write_text(const char *fname, int nm, char **cstrs);
void read_binary(const char *fname);
void write_binary(const char *fname, int nm, char **cstrs);
void write_mix(const char *fname);

int main(int argc, char **argv) {
  static const size_t Mandatory_Args_Nm = 3;
  if (argc < Mandatory_Args_Nm) {
    print_usage();
    exit(1);
  }
  const char *mode = argv[1], *fname = argv[2];
  if (streq(mode, "rt")) {
    read_text(fname);
  } else if (streq(mode, "wt")) {
    write_text(fname, argc - Mandatory_Args_Nm, argv + Mandatory_Args_Nm);
  } else if (streq(mode, "rb")) {
    read_binary(fname);
  } else if (streq(mode, "wb")) {
    write_binary(fname, argc - Mandatory_Args_Nm, argv + Mandatory_Args_Nm);
  } else if (streq(mode, "mx")) {
    write_mix(fname);
  } else {
    printf("Unknown mode: %s\n", mode);
    print_usage();
    exit(1);
  }
}

void check_file_error(FILE *file) {
  if (!ferror(file)) { return; }
  perror("");
  exit(1);
}

void read_text(const char *fname) {
  // NB: find a BUG! Actually two bugs (at least)
  char *buf = malloc(16);

  printf("= fscanf\n");
  FILE *fscanf_stm = fopen(fname, "r");
  if (fscanf_stm == NULL) {
    perror("read_text, open file");
    exit(1);
  }
  while (!feof(fscanf_stm) && !ferror(fscanf_stm)) {
    int read_nm = fscanf(fscanf_stm, "%15s", buf); // ret # of items
    if (read_nm != 1) { continue; } // opt: break
    printf("%s|\n", buf);
    printf("------------\n");
  }
  perror("On fscanf end");
  fclose(fscanf_stm);

  printf("= fgets\n");
  FILE *fgets_stm = fopen(fname, "r");
  if (fgets_stm == NULL) {
    perror("read_text, open file");
    exit(1);
  }
  while (!feof(fgets_stm) && !ferror(fgets_stm)) {
    //fgets(,, stdin);
    char *str = fgets(buf, sizeof(buf) - 1, fgets_stm);
    assert(str == NULL || str == buf);
    if (!str) { continue; }
    printf("%s|\n", str);
    printf("------------\n");
  }
  perror("On getf end");
  fclose(fgets_stm);

  free(buf);
}

void write_text(const char *fname, int nm, char **cstrs) {
  FILE *out_stm = fopen(fname, "w");
  if (out_stm == NULL) {
    perror("write_text, open file");
    exit(1);
  }
  for (int i = 0; i < nm; i++) {
    {
      int printed_nm = fprintf(out_stm, "%s\n", cstrs[i]);
      assert(printed_nm == strlen(cstrs[i]) + 1);
    }
    {
      int status = fputs(cstrs[i], out_stm);
      assert(status != EOF);
    }
    fputc('\n', out_stm);
    check_file_error(out_stm);
  }
  fclose(out_stm);
}

void read_binary(const char *fname) {
  FILE *in_stm = fopen(fname, "r");
  if (in_stm == NULL) {
    perror("write_text, open file");
    exit(1);
  }

  while (1) {
    uint32_t len;
    size_t read_nm = fread(&len, sizeof(len), 1, in_stm);
    if (read_nm != 1) {
      assert(feof(in_stm) || ferror(in_stm));
      perror("On fread end");
      break;
    }
    char *buf = malloc(len + 1);
    bzero(buf, len + 1);
    read_nm = fread(buf, sizeof(*buf), len, in_stm);
    if (read_nm != len) {
      if (ferror(in_stm)) {
        perror("On fread fail");
      }
      assert(0 && "Unexpected file format");
    }
    puts(buf);
    free(buf);
  }
  
  fclose(in_stm);
}

void write_binary(const char *fname, int nm, char **cstrs) {
  // view with hexdump -C
  FILE *out_stm = fopen(fname, "w");
  if (out_stm == NULL) {
    perror("write_text, open file");
    exit(1);
  }
  for (int i = 0; i < nm; i++) {
    uint32_t len = strlen(cstrs[i]);
    size_t written_nm = fwrite(&len, sizeof(len), 1, out_stm);
    if (written_nm != 1 || ferror(out_stm)) {
      perror("Bin: on size write");
      break;
    }
    written_nm = fwrite(cstrs[i], sizeof(*cstrs[i]), len, out_stm);
    if (written_nm != len || ferror(out_stm)) {
      perror("Bin: on data write");
    }
  }

  fclose(out_stm);
}

void write_mix(const char *fname) {
  FILE *out_stm = fopen(fname, "w");
  fprintf(out_stm, "%d\n", 1);
  char c = '2';
  fwrite(&c, sizeof(c), 1, out_stm);
  fputc('3', out_stm);
  fclose(out_stm);
}
