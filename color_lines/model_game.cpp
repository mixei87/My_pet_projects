#include "model_game.h"

GameModel::GameModel(int i, int j, QObject* parent)
    : QAbstractItemModel{parent},
      m_height_field{i},
      m_width_field{j},
      m_boardSize{m_height_field * m_width_field},
      m_field(m_boardSize, {m_default_color, {}}),
      m_selected_index{-1} {
  for (int i = 0; i < m_boardSize; ++i) {
    m_field_free.insert(i);
  }
  addRandomPoints();
}

int GameModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_field.size();
}

QVariant GameModel::data(const QModelIndex& index, int role) const {
  if (index.isValid()) {
    if (role == Qt::DisplayRole) {
      return QVariant::fromValue(m_field[index.row()].first);
    } else if (role == m_selectedBallRole) {
      return QVariant(m_field[index.row()].second);
    }
  }
  return QVariant();
}

QModelIndex GameModel::index(int row, int column,
                             const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return QAbstractItemModel::createIndex(row, column);
}

QModelIndex GameModel::parent(const QModelIndex& child) const {
  Q_UNUSED(child);
  return {};
}

int GameModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return {};
}

QHash<int, QByteArray> GameModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[m_displayRole] = "display";
  roles[m_selectedBallRole] = "selectedBallRole";
  return roles;
}

int GameModel::height_field() const { return m_height_field; }

int GameModel::width_field() const { return m_width_field; }

void GameModel::clearBingoRows() {
  for (const auto& cell : m_field_for_free) {
    m_field[cell].first = m_default_color;
    m_field_busy.erase(cell);
    m_field_free.insert(cell);
  }
  emitDataChanged(m_field_for_free);
  m_field_for_free.clear();
}

int GameModel::setIndexFromCoord(const int& i, const int& j) {
  return i * m_height_field + j;
}

void GameModel::checkLine(int i, int j, const int& d_i, const int& d_j,
                          int& points_in_line) {
  if (i + d_i >= 0 && i + d_i < m_height_field && j + d_j >= 0 &&
      j + d_j < m_width_field) {
    int index1 = setIndexFromCoord(i, j);
    int index2 = setIndexFromCoord(i + d_i, j + d_j);
    if (m_field[index1].first != m_default_color &&
        m_field[index1].first == m_field[index2].first) {
      ++points_in_line;
      checkLine(i + d_i, j + d_j, d_i, d_j, points_in_line);
    }
  }
  // if need EXACT match quantity in row - you need change '>=' to '=='
  if (points_in_line >= m_points_in_row) {
    m_field_for_free.insert(setIndexFromCoord(i, j));
  }
}

void GameModel::checkDirection(const int& i, const int& j,
                               const std::pair<int, int>& diff_indexes) {
  int points_in_line = 1;
  checkLine(i, j, diff_indexes.first, diff_indexes.second, points_in_line);
}

bool GameModel::checkLines() {
  for (int i = 0; i < m_height_field; ++i) {
    for (int j = 0; j < m_width_field; ++j) {
      checkDirection(i, j, m_directions["right"]);
      checkDirection(i, j, m_directions["down"]);
      // ---- optionality for diagonals --------------------------------
      //      checkDirection(i, j, m_directions["left_down_diagonal"]);
      //      checkDirection(i, j, m_directions["right_down_diagonal"]);
    }
  }
  if (m_field_for_free.size()) {
    clearBingoRows();
    return true;
  }
  return false;
}

void GameModel::emitDataChanged(const int& index) {
  QModelIndex ind = GameModel::index(index, 0);
  emit dataChanged(ind, ind);
}

void GameModel::emitDataChanged(const std::vector<int>& indexes) {
  for (const auto& index : indexes) {
    emitDataChanged(index);
  }
}

void GameModel::emitDataChanged(const std::unordered_set<int>& indexes) {
  for (const auto& index : indexes) {
    emitDataChanged(index);
  }
}

void GameModel::changeSelectedBalls(int new_index) {
  if (new_index == m_selected_index) {
    m_field[m_selected_index].second = "";
    emitDataChanged(m_selected_index);
    m_selected_index = -1;
  } else if (m_selected_index == -1) {
    m_field[new_index].second = "clicked";
    emitDataChanged(new_index);
    m_selected_index = new_index;
  } else {
    m_field[m_selected_index].second = "";
    emitDataChanged(m_selected_index);
    m_field[new_index].second = "clicked";
    emitDataChanged(new_index);
    m_selected_index = new_index;
  }
}

bool GameModel::moveBall(int free_index) {
  if (m_selected_index == -1) return false;
  m_field[m_selected_index].second = "";
  emitDataChanged(m_selected_index);
  swap(m_field[m_selected_index], m_field[free_index]);
  m_field_busy.erase(m_selected_index);
  m_field_busy.insert(free_index);
  m_field_free.erase(free_index);
  m_field_free.insert(m_selected_index);
  std::vector<int> indexes{free_index, m_selected_index};
  m_selected_index = -1;
  emitDataChanged(indexes);
  return true;
}

void GameModel::getRandomPoints() {
  m_seq_free_points.clear();
  auto gen = std::mt19937{std::random_device{}()};
  sample(begin(m_field_free), end(m_field_free),
         back_inserter(m_seq_free_points), m_count_next_balls, gen);
}

void GameModel::addRandomPoints() {
  getRandomPoints();
  for (const auto& n : m_seq_free_points) {
    auto gen = std::mt19937{std::random_device{}()};
    std::uniform_int_distribution<std::mt19937::result_type> color(0, 3);
    m_field[n].first = m_colors[color(gen)];
    m_field_free.erase(n);
    m_field_busy.insert(n);
  }
  emitDataChanged(m_seq_free_points);
  checkLines();
}
