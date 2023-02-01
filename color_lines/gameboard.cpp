#include "gameboard.h"

GameBoard::GameBoard(const int height_field, const int width_field,
                     QObject* parent)
    : QAbstractItemModel{parent},
      m_height_field{height_field},
      m_width_field{width_field},
      m_boardSize{m_height_field * m_width_field},
      m_field(m_boardSize, default_color),
      m_currentIndex{-1} {
  for (int i = 0; i < m_height_field * m_width_field; ++i) {
    m_field_free.insert(i);
  }
  addRandomPoints();
}

int GameBoard::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_field.size();
}

QVariant GameBoard::data(const QModelIndex& index, int role) const {
  if (index.isValid() && role == Qt::DisplayRole) {
    qDebug() << "index: " << index.row();
    return QVariant::fromValue(m_field[index.row()]);
  }
  return {};
  //  else if (role == selectedBall_) {
  //    return QVariant::fromValue(true);
  //  }
}

QModelIndex GameBoard::index(int row, int column,
                             const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return QAbstractItemModel::createIndex(row, column);
}

QModelIndex GameBoard::parent(const QModelIndex& child) const {
  Q_UNUSED(child);
  return {};
}

int GameBoard::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return {};
}

int GameBoard::height_field() const { return m_height_field; }

int GameBoard::width_field() const { return m_width_field; }

void GameBoard::clearBingoRows() {
  for (const auto& cell : m_field_for_free) {
    m_field[cell] = default_color;
    m_field_busy.erase(cell);
    m_field_free.insert(cell);
  }
  emitDataChanged(m_field_for_free);
  m_field_for_free.clear();
}

int GameBoard::setIndexFromCoord(const int& i, const int& j) {
  return i * m_height_field + j;
}

void GameBoard::checkLine(int i, int j, const int& d_i, const int& d_j,
                          int& points_in_line) {
  if (i + d_i >= 0 && i + d_i < m_height_field && j + d_j >= 0 &&
      j + d_j < m_width_field) {
    int index1 = setIndexFromCoord(i, j);
    int index2 = setIndexFromCoord(i + d_i, j + d_j);
    if (m_field[index1] != default_color &&
        m_field[index1] == m_field[index2]) {
      ++points_in_line;
      checkLine(i + d_i, j + d_j, d_i, d_j, points_in_line);
    }
  }
  if (points_in_line >= m_points_in_row) {
    m_field_for_free.insert(setIndexFromCoord(i, j));
  }
}

bool GameBoard::checkLines() {
  for (int i = 0; i < m_height_field; ++i) {
    for (int j = 0; j < m_width_field; ++j) {
      int points_in_line = 1;
      checkLine(i, j, 0, 1, points_in_line);
      points_in_line = 1;
      checkLine(i, j, 1, -1, points_in_line);
      points_in_line = 1;
      checkLine(i, j, 1, 0, points_in_line);
      points_in_line = 1;
      checkLine(i, j, 1, 1, points_in_line);
    }
  }
  if (m_field_for_free.size()) {
    clearBingoRows();
    return true;
  }
  return false;
}

void GameBoard::emitDataChanged(const int& index) {
  QModelIndex ind = GameBoard::index(index, 0);
  emit dataChanged(ind, ind);
}

void GameBoard::emitDataChanged(const vector<int>& indexes) {
  for (const auto& index : indexes) {
    emitDataChanged(index);
  }
}

void GameBoard::emitDataChanged(const unordered_set<int>& indexes) {
  for (const auto& index : indexes) {
    emitDataChanged(index);
  }
}

bool GameBoard::setCurrentIndex(int newIndex) {
  if (m_currentIndex == newIndex) {
    m_currentIndex = -1;
  } else {
    m_currentIndex = newIndex;
  }
  return true;
}

int GameBoard::getCurrentIndex() { return m_currentIndex; }

bool GameBoard::moveBall(int index) {
  if (m_currentIndex == -1) return false;
  swap(m_field[m_currentIndex], m_field[index]);
  m_field_busy.erase(m_currentIndex);
  m_field_busy.insert(index);
  m_field_free.erase(index);
  m_field_free.insert(m_currentIndex);
  vector<int> indexes{index, m_currentIndex};
  m_currentIndex = -1;
  emitDataChanged(indexes);
  return true;
}

void GameBoard::getRandomPoints(const unordered_set<int>& field,
                                vector<int>& seq_points,
                                const int& count_points) {
  seq_points.clear();
  auto gen = mt19937{random_device{}()};
  sample(begin(field), end(field), back_inserter(seq_points), count_points,
         gen);
}

void GameBoard::addRandomPoints() {
  getRandomPoints(m_field_free, m_seq_free_points, m_count_next_balls);
  for (const auto& n : m_seq_free_points) {
    auto gen = mt19937{random_device{}()};
    std::uniform_int_distribution<mt19937::result_type> color(0, 3);
    m_field[n] = m_colors[color(gen)];
    m_field_free.erase(n);
    m_field_busy.insert(n);
  }
  emitDataChanged(m_seq_free_points);
  checkLines();
}
