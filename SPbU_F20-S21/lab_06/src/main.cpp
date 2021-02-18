#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <algorithm>

#include "my_vector.h"

struct Cmd {
  static constexpr size_t MAX_ARGS = 2;
  char name[20];
  size_t arg_nm;
  int args[MAX_ARGS];
};

void init_cmd(Cmd *cmd, char *buff) {
  char *tok = strtok(buff, " \n");
  strncpy(cmd->name, buff, sizeof(cmd->name));
  cmd->name[sizeof(cmd->name) - 1] = '\0';
  cmd->arg_nm = 0;

  while ((tok = strtok(NULL, " ")) && cmd->arg_nm < Cmd::MAX_ARGS) {
    cmd->args[cmd->arg_nm] = strtol(tok, NULL, 0);
    cmd->arg_nm++;
  }
}

int main(int argc, char **argv) {
  char buff[30];
  MyVector v;
  Cmd cmd;

#define CMD_ARGS_CHECK(CMD_NAME, ARGS_NM)                 \
  if (cmd.arg_nm != ARGS_NM) {                            \
    printf(#CMD_NAME" must take "#ARGS_NM" args.\n");     \
    continue;                                             \
  }

  while (1) {
    printf("> ");
    assert(fgets(buff, sizeof(buff), stdin));
    init_cmd(&cmd, buff);

    if (!strcmp(cmd.name, "info")) {
      CMD_ARGS_CHECK(Info, 0);
      printf("SZ: %zu; CAP: %zu;\n", v.size(), v.capacity());
      for (size_t i = 0; i < v.size(); ++i) {
        printf("%d ", v.get(i));
      }
      printf("\n");
    } else if (!strcmp(cmd.name, "set")) {
      CMD_ARGS_CHECK(Set, 2);
      v.set(cmd.args[0], cmd.args[1]);
    } else if (!strcmp(cmd.name, "reserve")) {
      CMD_ARGS_CHECK(Reserve, 1);
      v.reserve(cmd.args[0]);
    } else if (!strcmp(cmd.name, "resize")) {
      CMD_ARGS_CHECK(Resize, 1);
      v.resize(cmd.args[0]);
    } else if (!strcmp(cmd.name, "push_back")) {
      CMD_ARGS_CHECK(Push_back, 1);
      v.push_back(cmd.args[0]);
    } else if (!strcmp(cmd.name, "insert")) {
      CMD_ARGS_CHECK(Insert, 2);
      v.insert(cmd.args[0], cmd.args[1]);
    } else if (!strcmp(cmd.name, "erase")) {
      CMD_ARGS_CHECK(Erase, 1);
      v.erase(cmd.args[0]);
    } else if (!strcmp(cmd.name, "exit")) {
      CMD_ARGS_CHECK(Exit, 0);
      break;
    } else {
      printf("Unknown command\n");
      char c;
      while ((c = getchar()) != '\n' && c != EOF);
    }
  }

#undef CMD_ARGS_CHECK

}
