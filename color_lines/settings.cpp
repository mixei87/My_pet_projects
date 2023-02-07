#include "settings.h"

Settings *Settings::m_settings = nullptr;

Settings::Settings()
    : m_default_color{Qt::black},
      m_count_next_balls{3},
      m_points_in_row{5},
      m_height_field{9},
      m_width_field{9},
      m_board_size{m_height_field * m_width_field},
      m_field(m_board_size, {m_default_color, {}}),
      m_game_is_started{false} {}

Settings::~Settings() { delete m_settings; }

Settings *Settings::getSettings() {
  if (!m_settings) m_settings = new Settings();
  return m_settings;
}
// update tbl_gameboard set color = "#ff0000

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

int Settings::board_size() const { return m_board_size; }

void Settings::setBoard_size() {
  if (m_height_field > 0 && m_width_field > 0)
    m_board_size = m_height_field * m_width_field;
}

const std::vector<std::pair<QColor, QString> > &Settings::field() const {
  return m_field;
}

void Settings::setField(const int &index, const QColor color) {
  m_field[index].first = color;
  m_field[index].second = QString();
}
