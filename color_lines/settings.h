#ifndef SETTINGS_H
#define SETTINGS_H
#include <QColor>
#include <QDebug>
#include <QString>
#include <vector>

class Settings {
 public:
  ~Settings(){};
  Settings(Settings& other) = delete;
  void operator=(const Settings&) = delete;
  static Settings& getSettings();

  const QColor& default_color() const;
  void setDefault_color(const QColor& newDefault_color);
  int count_next_balls() const;
  void setCount_next_balls(int newCount_next_balls);
  int points_in_row() const;
  void setPoints_in_row(int newPoints_in_row);
  int height_field() const;
  void setHeight_field(int newHeight_field);
  int width_field() const;
  void setWidth_field(int newWidth_field);
  bool game_is_started() const;
  void setGame_is_started(bool newGame_is_started);
  int board_size() const;
  void setBoard_size();

  const std::vector<std::pair<QColor, QString>>& field() const;
  void setField(const int& index, const QColor color);

 private:
  Settings();

  QColor m_default_color;
  int m_count_next_balls;
  int m_points_in_row;
  int m_height_field;
  int m_width_field;
  int m_board_size;
  std::vector<std::pair<QColor, QString>> m_field;
  bool m_game_is_started;
};

#endif  // SETTINGS_H
