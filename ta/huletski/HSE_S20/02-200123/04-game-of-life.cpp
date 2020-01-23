// sudo apt-get install libncurses5-dev
#include <ncurses.h>
#include <array>
#include <utility>
#include <cassert>
#include <iostream>
#include <unistd.h>

class NonCopyable {
public:
  NonCopyable() {}
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable(NonCopyable&&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
  NonCopyable&& operator=(NonCopyable&&) = delete;
};

//------------------------------------------------------------------------------
class LifeModel : private NonCopyable {
public:
  static constexpr std::size_t Rows_Nm = 20;
  static constexpr std::size_t Cols_Nm = 50;
private:
  using RowT = std::array<bool, Cols_Nm + 2>;
  using FieldT = std::array<RowT, Rows_Nm + 2>;
private:
  enum class CellDestiny {
    Keep_Alive, Die_Alone, Killed, Born_New, IDC
  };
public:

  LifeModel() {
    RowT row = RowT();
    row.fill(false);
    current_field_.fill(row);
    prev_field_ = current_field_;
  }

  void tick() {
    std::swap(current_field_, prev_field_);
    for (std::size_t i = 1; i <= Rows_Nm; i++) {
      for (std::size_t j = 1; j <= Cols_Nm; j++) {
        switch (cell_destiny(i, j)) {
        case CellDestiny::Die_Alone:
        case CellDestiny::Killed:
          current_field_[i][j] = 0;
          break;
        case CellDestiny::Keep_Alive:
          assert(prev_field_[i][j]);
        case CellDestiny::Born_New:
          current_field_[i][j] = 1;
          break;
        case CellDestiny::IDC:
          current_field_[i][j] = prev_field_[i][j];
          break;
        }
      }
    }
  }

  void flip(std::size_t r_i, std::size_t c_i) {
    set(r_i, c_i, !current_field_[r_i][c_i]);
  }

  void set(std::size_t r_i, std::size_t c_i, bool value) {
    ensure_inside(r_i, c_i);
    current_field_[r_i][c_i] = value;
  }

  bool is_cell_alive(std::size_t r_i, std::size_t c_i) const {
    ensure_inside(r_i, c_i);
    return current_field_[r_i][c_i];
  }

  void add_glider_at(std::size_t r, std::size_t c) {
    /*
     * . + .
     * .(.)+
     * + + +
     */
    flip(r - 1, c);
    flip(r, c + 1);
    flip(r + 1, c - 1);
    flip(r + 1, c);
    flip(r + 1, c + 1);
  }

  std::size_t height() const { return Rows_Nm; }
  std::size_t width() const { return Cols_Nm; }
private:
  void ensure_inside(std::size_t r_i, std::size_t c_i) const {
    assert(1 <= r_i && r_i <= height() && 1 <= c_i && c_i <= width());
  }
  
  CellDestiny cell_destiny(std::size_t i, std::size_t j) const {
    // count neighbors number
    unsigned neighbors_nm = 0;
    for (int d_i = -1; d_i <= 1; d_i++) {
      for (int d_j = -1; d_j <= 1; d_j++) {
        if (d_i == 0 && d_j == 0) {
          continue;
        }
        neighbors_nm += prev_field_[i + d_i][j + d_j];
      }
    }
    bool is_alive = prev_field_[i][j];
    if (is_alive) {
      switch (neighbors_nm) {
      case 0: case 1:      return CellDestiny::Die_Alone;
      case 2: case 3:      return CellDestiny::Keep_Alive;
      /*case 4+*/ default: return CellDestiny::Killed;
      }
    } else {
      if (neighbors_nm == 3) { return CellDestiny::Born_New; }
    }
    return CellDestiny::IDC;
  }

private:
  FieldT current_field_, prev_field_;
};

//------------------------------------------------------------------------------
enum class ColorMode {
  Empty = 1, Occupied = 2
};

class NcursesView : private NonCopyable {
  //TODO: draw in own window/handle bounds
public:
  void update_view(const LifeModel &m) {
    clear();
    for (std::size_t r_i = 1; r_i <= m.height(); r_i++) {
      for (std::size_t c_i = 1; c_i <= m.width(); c_i++) {
        ColorMode cm = m.is_cell_alive(r_i, c_i) ? ColorMode::Occupied
                                                 : ColorMode::Empty;
        attron(COLOR_PAIR(cm));
        printw(" ");
        attroff(COLOR_PAIR(cm));
      }
      printw("\n");
    }
    refresh();
  }
  void move_cursor_to_center() {
    move(0, 0); // FIXME
  }
  void move_cursor(int x, int y) {
    // TODO: validation
    move(x, y);
  }
  void dmove_cursor(int d_x, int d_y) {
    int cursor_x, cursor_y;
    getyx(stdscr, cursor_x, cursor_y);
    move_cursor(cursor_x + d_x, cursor_y + d_y);
  }
  void show_cursor() { curs_set(2); }
  void hide_cursor() { curs_set(0); }
  void cursor_local_pos(int &x, int &y) {
    // FIXME: add global offsets
    getyx(stdscr, x, y);
  }
};

//------------------------------------------------------------------------------
class AppController : private NonCopyable {
private:
  enum class ControllerMode {
    Simulation, Editing, Done
  };
public:
  AppController() {
    initscr();
    noecho();
    start_color();
    init_pair(int(ColorMode::Occupied), COLOR_YELLOW, COLOR_YELLOW);
    init_pair(int(ColorMode::Empty), COLOR_WHITE, COLOR_WHITE);
    keypad(stdscr, true);
  }

  ~AppController() {
    endwin();
  }

  void run() {
    m_.add_glider_at(5, 5);
    ControllerMode mode = ControllerMode::Simulation;
    while (true) {
      switch (mode) {
      case ControllerMode::Simulation:
        mode = run_simulation();
        break;
      case ControllerMode::Editing:
        mode = run_editing();
        break;
      case ControllerMode::Done:
        return;
      }
    }
  }
private:
  ControllerMode run_simulation() {
    nodelay(stdscr, true);
    v_.hide_cursor();
    while (true) {
      m_.tick();
      v_.update_view(m_);
      usleep(300000);
      switch (getch()) {
      case ERR: break;
      case ' ': return ControllerMode::Editing;
      case 27: return ControllerMode::Done; // on Esc
      }
    }
  }
  
  ControllerMode run_editing() {
    nodelay(stdscr, false);
    v_.show_cursor();
    v_.move_cursor_to_center();
    while (true) {
      int ch = getch();
      switch (ch) {
      case ' ': return ControllerMode::Simulation;
      case 27: return ControllerMode::Done; // on Esc
      case KEY_UP:    v_.dmove_cursor(-1, 0); break;
      case KEY_DOWN:  v_.dmove_cursor(1, 0);  break;
      case KEY_LEFT:  v_.dmove_cursor(0, -1); break;
      case KEY_RIGHT: v_.dmove_cursor(0, 1);  break;
      case 10: { // on Enter
        int x, y;
        v_.cursor_local_pos(x, y);
        m_.flip(x + 1, y + 1);
        v_.update_view(m_);
        v_.move_cursor(x, y);
        break;
      }
      case 'a': {
        int x, y;
        v_.cursor_local_pos(x, y);
        // TODO: validation
        m_.add_glider_at(x + 1, y + 1);
        v_.update_view(m_);
        v_.move_cursor(x, y);
      }
      }
    }
  }
private:
  NcursesView v_;
  LifeModel m_;
};

// g++ main.cpp -lncurses -Wall 
int main(int, char**) {
  AppController().run();
  return 0;
}
