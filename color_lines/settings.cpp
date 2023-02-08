#include "settings.h"

Settings::Settings()
    : m_default_color{Qt::black},
      m_count_next_balls{3},
      m_points_in_row{5},
      m_height_field{9},
      m_width_field{9},
      m_field(m_height_field * m_width_field, {m_default_color}),
      m_game_is_started{false},
      m_record{0},
      m_points_to_1_ball{2},
      m_current_score{0} {}

Settings &Settings::getSettings() {
  static Settings m_settings;
  return m_settings;
}

const QColor &Settings::default_color() const { return m_default_color; }

void Settings::setDefault_color(const QColor &newDefault_color) {
  m_default_color = newDefault_color;
}

int Settings::count_next_balls() const { return m_count_next_balls; }

void Settings::setCount_next_balls(int newCount_next_balls) {
  m_count_next_balls = newCount_next_balls;
}

int Settings::points_in_row() const { return m_points_in_row; }

void Settings::setPoints_in_row(int newPoints_in_row) {
  m_points_in_row = newPoints_in_row;
}

int Settings::height_field() const { return m_height_field; }

void Settings::setHeight_field(int newHeight_field) {
  m_height_field = newHeight_field;
}

int Settings::width_field() const { return m_width_field; }

void Settings::setWidth_field(int newWidth_field) {
  m_width_field = newWidth_field;
}

bool Settings::game_is_started() const { return m_game_is_started; }

void Settings::setGame_is_started(bool newGame_is_started) {
  m_game_is_started = newGame_is_started;
}

const std::vector<QColor> &Settings::field() const { return m_field; }

void Settings::setField(const int &index, const QColor color) {
  m_field[index] = color;
}

int Settings::record() const { return m_record; }

void Settings::setRecord(int newRecord) { m_record = newRecord; }

int Settings::points_to_1_ball() const { return m_points_to_1_ball; }

void Settings::setPoints_to_1_ball(int newPoints_to_1_ball) {
  m_points_to_1_ball = newPoints_to_1_ball;
}

int Settings::current_score() const { return m_current_score; }

void Settings::setCurrent_score(int newCurrent_score) {
  m_current_score = newCurrent_score;
}
