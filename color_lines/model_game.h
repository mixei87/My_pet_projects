#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <QAbstractItemModel>
#include <QColor>
#include <QDir>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "DBmanager.h"
#include "settings.h"

class GameModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  enum ModelRoles {
    m_displayRole = Qt::DisplayRole,
    m_selectedBallRole = Qt::UserRole + 1
  };

  GameModel(Settings& settings, QObject* parent = nullptr);
  ~GameModel(){};

  int height_field() const;
  int width_field() const;

  Q_INVOKABLE void addRandomPoints();
  Q_INVOKABLE bool checkLines();
  Q_INVOKABLE bool moveBall(int free_index);
  Q_INVOKABLE void changeSelectedBalls(int new_index);

 private:
  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& child) const override;
  QHash<int, QByteArray> roleNames() const override;

  void getRandomPoints();
  void clearBingoRows();
  int setIndexFromCoord(const int& i, const int& j) const;
  void checkLine(int i, int j, const int& d_i, const int& d_j,
                 int& points_in_line);
  void checkDirection(const int& i, const int& j,
                      const std::pair<int, int>& diff_indexes);
  void emitDataChanged(const int& index);
  void emitDataChanged(const std::vector<int>& indexes);
  void emitDataChanged(const std::unordered_set<int>& indexes);
  void finishGame();

  QColor m_default_color;
  int m_count_next_balls;
  int m_points_in_row;
  int m_height_field;
  int m_width_field;
  int m_boardSize;
  std::vector<std::pair<QColor, QString>> m_field;
  int m_selected_index;

  std::unordered_set<int> m_field_free;
  std::unordered_set<int> m_field_busy;
  std::unordered_set<int> m_field_for_free;

  std::vector<int> m_seq_free_points;
  std::vector<int> m_seq_busy_points;

  std::unordered_map<int, QColor> m_colors{
      {0, Qt::red},
      {1, QColorConstants::Svg::mediumseagreen},
      {2, QColorConstants::Svg::cornflowerblue},
      {3, QColorConstants::Svg::gold}};

  std::unordered_map<QString, std::pair<int, int>> m_directions{
      {"right", {0, 1}},
      {"down", {1, 0}},
      {"left_down_diagonal", {1, -1}},
      {"right_down_diagonal", {1, 1}}};

  Q_PROPERTY(int height_field READ height_field CONSTANT)
  Q_PROPERTY(int width_field READ width_field CONSTANT)
};

#endif  // MODEL_GAME_H
