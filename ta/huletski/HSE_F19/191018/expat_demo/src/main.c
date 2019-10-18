#include <stdio.h>
#include <expat.h>

void start_element(void *data, const char *element, const char **attribute) {
  // TODO
}

void end_element(void *data, const char *element) {
}

int parse_xml(const char *fname, size_t buf_size, int *out_point_nm) {
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    perror("Failed to open file");
    return 1;
  }

  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetElementHandler(parser, start_element, end_element);
  XML_SetUserData(parser, out_point_nm);

  int exit_status = 0;
  while (1) {
    // TODO: implement file reading (buffer size := buf_size):
    //       buf content update, done flag update

    if (XML_Parse(parser, buf, read_nm, done) == XML_STATUS_ERROR) {
      printf("Error: %s at line %lu\n",
             XML_ErrorString(XML_GetErrorCode(parser)),
             XML_GetCurrentLineNumber(parser));
      exit_status = 2;
      goto out;
    }
    if (done) { break; }
  }

out:
  XML_ParserFree(parser);
  fclose(f);
  return exit_status;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: ./demo <file.xml>");
    return 1;
  }
  static const size_t Buffer_Size = 16;
  int points_nm = 0;
  int status = parse_xml(argv[1], Buffer_Size, &points_nm);
  if (status == 0) {
    printf("Points number: %d\n", points_nm);
  } else {
    printf("Parse XML failed: %d\n", status);
  }
}

