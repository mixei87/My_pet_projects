#include "model_game.h"

GameModel::GameModel(QObject* parent) : QAbstractItemModel{parent} {
  newGame(Settings::getSettings().game_is_started());
}

GameModel::~GameModel() { finishGame(); }

void GameModel::newGame(bool game_is_started) {
  Settings::getSettings().setGame_is_started(game_is_started);
  initialiseVariables(game_is_started);
  if (!game_is_started) {
    addRandomPoints();
  }
}

QString GameModel::record() const {
  return QString::number(Settings::getSettings().record());
}

void GameModel::setRecord() {
  if (m_score > Settings::getSettings().record())
    Settings::getSettings().setRecord(m_score);
}

void GameModel::initialiseVariables(const bool& game_is_started) {
  m_field.clear();
  m_free_tiles.clear();
  m_busy_tiles.clear();
  m_tiles_bingo.clear();
  m_few_free_points.clear();
  fillGameBoard(game_is_started);
  m_selected_index = -1;
  if (game_is_started)
    m_score = Settings::getSettings().current_score();
  else
    m_score = 0;
  emit dataChanged(GameModel::index(0, 0),
                   GameModel::index(Settings::getSettings().field().size(), 0));
}

void GameModel::fillGameBoard(const bool& game_is_started) {
  QColor default_color = Settings::getSettings().default_color();
  QColor color;
  for (size_t i = 0; i < Settings::getSettings().field().size(); ++i) {
    if (game_is_started)
      color = Settings::getSettings().field()[i];
    else
      color = default_color;
    m_field.push_back({color, QString{}});
    if (color == default_color) m_free_tiles.insert(i);
  }
}

int GameModel::height_field() const {
  return Settings::getSettings().height_field();
}

int GameModel::width_field() const {
  return Settings::getSettings().width_field();
}

void GameModel::addRandomPoints() {
  getRandomPoints();
  for (const auto& n : m_few_free_points) {
    auto gen = std::mt19937{std::random_device{}()};
    std::uniform_int_distribution<std::mt19937::result_type> color(0, 3);
    m_field[n].first = m_colors[color(gen)];
    m_free_tiles.erase(n);
    m_busy_tiles.insert(n);
  }
  emitDataChanged(m_few_free_points);
  checkLines();
}

bool GameModel::checkLines() {
  for (int i = 0; i < Settings::getSettings().height_field(); ++i) {
    for (int j = 0; j < Settings::getSettings().width_field(); ++j) {
      checkDirection(i, j, m_directions["right"]);
      checkDirection(i, j, m_directions["down"]);
      // ---- optionality for diagonals --------------------------------
      //      checkDirection(i, j, m_directions["left_down_diagonal"]);
      //      checkDirection(i, j, m_directions["right_down_diagonal"]);
    }
  }
  if (m_tiles_bingo.size()) {
    clearBingoRows();
    return true;
  }
  return false;
}

void GameModel::checkDirection(const int& i, const int& j,
                               const std::pair<int, int>& diff_indexes) {
  int points_in_line = 1;
  checkLine(i, j, diff_indexes.first, diff_indexes.second, points_in_line);
}

void GameModel::checkLine(int i, int j, const int& d_i, const int& d_j,
                          int& points_in_line) {
  if (i + d_i >= 0 && i + d_i < Settings::getSettings().height_field() &&
      j + d_j >= 0 && j + d_j < Settings::getSettings().width_field()) {
    int index1 = setIndexFromCoord(i, j);
    int index2 = setIndexFromCoord(i + d_i, j + d_j);
    if (m_field[index1].first != Settings::getSettings().default_color() &&
        m_field[index1].first == m_field[index2].first) {
      ++points_in_line;
      checkLine(i + d_i, j + d_j, d_i, d_j, points_in_line);
    }
  }
  // if need EXACT match quantity in row - you need change '>=' to '=='
  if (points_in_line >= Settings::getSettings().points_in_row()) {
    m_tiles_bingo.insert(setIndexFromCoord(i, j));
  }
}

void GameModel::clearBingoRows() {
  int score = 0;
  for (const auto& cell : m_tiles_bingo) {
    m_field[cell].first = Settings::getSettings().default_color();
    m_busy_tiles.erase(cell);
    m_free_tiles.insert(cell);
    score += Settings::getSettings().points_to_1_ball();
  }
  m_score += score;
  emit scoreChanged();
  //  setScore(score);
  emitDataChanged(m_tiles_bingo);
  m_tiles_bingo.clear();
}

bool GameModel::moveBall(int free_index) {
  if (m_selected_index == -1) return false;
  Settings::getSettings().setGame_is_started(true);
  m_field[m_selected_index].second = "";
  emitDataChanged(m_selected_index);
  swap(m_field[m_selected_index], m_field[free_index]);
  m_busy_tiles.erase(m_selected_index);
  m_busy_tiles.insert(free_index);
  m_free_tiles.erase(free_index);
  m_free_tiles.insert(m_selected_index);
  std::vector<int> indexes{free_index, m_selected_index};
  m_selected_index = -1;
  emitDataChanged(indexes);
  return true;
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

bool GameModel::isGameOver() {
  if (m_free_tiles.empty()) return true;
  return false;
}

int GameModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return m_field.size();
}

int GameModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return {};
}

QVariant GameModel::data(const QModelIndex& index, int role) const {
  if (index.isValid()) {
    if (role == Qt::DisplayRole) {
      return m_field[index.row()].first;
    } else if (role == m_selectedBallRole) {
      return m_field[index.row()].second;
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

QHash<int, QByteArray> GameModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[m_displayRole] = "display";
  roles[m_selectedBallRole] = "selectedBallRole";
  return roles;
}

void GameModel::getRandomPoints() {
  m_few_free_points.clear();
  auto gen = std::mt19937{std::random_device{}()};
  sample(begin(m_free_tiles), end(m_free_tiles),
         back_inserter(m_few_free_points),
         Settings::getSettings().count_next_balls(), gen);
}

int GameModel::setIndexFromCoord(const int& i, const int& j) const {
  return i * Settings::getSettings().height_field() + j;
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

void GameModel::finishGame() {
  if (m_free_tiles.empty()) Settings::getSettings().setGame_is_started(false);
  if (Settings::getSettings().game_is_started()) {
    for (size_t i = 0; i < m_field.size(); ++i) {
      Settings::getSettings().setField(i, m_field[i].first);
    }
    Settings::getSettings().setCurrent_score(m_score);
  } else {
    setRecord();
    for (size_t i = 0; i < m_field.size(); ++i) {
      Settings::getSettings().setField(i,
                                       Settings::getSettings().default_color());
    }
    Settings::getSettings().setCurrent_score(0);
  }
}

int GameModel::score() const { return m_score; }
