#ifndef SETTINGS_H
#define SETTINGS_H
#include <QColor>

class Settings {
 public:
  Settings();
  ~Settings(){};

  QColor m_default_color;
  int m_count_next_balls;
  int m_points_in_row;
  int m_height_field;
  int m_width_field;
  bool m_game_is_started;
};

#endif  // SETTINGS_H
