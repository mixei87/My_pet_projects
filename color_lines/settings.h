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

  const std::vector<QColor>& field() const;
  void setField(const int& index, const QColor color);

  int record() const;
  void setRecord(int newRecord);

  int points_to_1_ball() const;

  void setPoints_to_1_ball(int newPoints_to_1_ball);

  int current_score() const;
  void setCurrent_score(int newCurrent_score);

 private:
  Settings();

  QColor m_default_color;
  int m_count_next_balls;
  int m_points_in_row;
  int m_height_field;
  int m_width_field;
  std::vector<QColor> m_field;
  bool m_game_is_started;
  int m_record;
  int m_points_to_1_ball;
  int m_current_score;
};

#endif  // SETTINGS_H
