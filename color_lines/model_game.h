#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <QAbstractItemModel>
#include <QColor>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "settings.h"

class GameModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  enum ModelRoles {
    m_displayRole = Qt::DisplayRole,
    m_selectedBallRole = Qt::UserRole + 1
  };

  GameModel(QObject* parent = nullptr);
  ~GameModel();

  Q_PROPERTY(int height_field READ height_field CONSTANT)
  Q_PROPERTY(int width_field READ width_field CONSTANT)
  Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
  Q_PROPERTY(int record READ record NOTIFY recordChanged)

  int height_field() const;
  int width_field() const;

  Q_INVOKABLE void addRandomPoints();
  Q_INVOKABLE bool checkLines();
  Q_INVOKABLE bool changeSelectedBalls(const int& new_index);
  Q_INVOKABLE void swapBalls();
  Q_INVOKABLE bool isGameOver();
  Q_INVOKABLE void newGame(bool game_is_started = false);
  Q_INVOKABLE void setRecord();
  Q_INVOKABLE bool game_is_started();
  Q_INVOKABLE void setGame_is_started(const bool& isStarted);
  Q_INVOKABLE int selectedIndex();
  Q_INVOKABLE int freeIndex();
  Q_INVOKABLE void clearStateAtFirst();

  Q_INVOKABLE QVariant getColor(int index);
  Q_INVOKABLE void setColor(int index, QVariant newColor);
  Q_INVOKABLE void setState(int index, QString newState);

  int record() const;
  int score() const;
  void setScore(int newScore);

 signals:
  void scoreChanged();
  void recordChanged();

 private:
  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index, const QVariant& value,
               int role = Qt::EditRole) override;
  QModelIndex index(int row, int column = 0,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& child) const override;
  QHash<int, QByteArray> roleNames() const override;

  void initialiseVariables(const bool& game_is_started);
  void fillGameBoard(const bool& game_is_started);
  void getRandomPoints();
  void clearBingoRows();
  int setIndexFromCoord(const int& i, const int& j) const;
  void checkLine(int i, int j, const int& d_i, const int& d_j,
                 int& points_in_line);
  void checkDirection(const int& i, const int& j,
                      const std::pair<int, int>& diff_indexes);
  void finishGame();

  std::vector<std::pair<QColor, QString>> m_field;
  int m_selected_index;
  int m_free_index;
  int m_score;

  std::unordered_set<int> m_free_tiles;
  std::unordered_set<int> m_busy_tiles;
  std::unordered_set<int> m_tiles_bingo;
  std::vector<int> m_few_free_tiles;
  std::unordered_map<int, QColor> m_colors{
      {0, QColorConstants::Svg::deeppink},
      {1, QColorConstants::Svg::mediumseagreen},
      {2, QColorConstants::Svg::cornflowerblue},
      {3, QColorConstants::Svg::gold}};
  std::unordered_map<QString, std::pair<int, int>> m_directions{
      {"right", {0, 1}},
      {"down", {1, 0}},
      {"left_down_diagonal", {1, -1}},
      {"right_down_diagonal", {1, 1}}};
};

#endif  // MODEL_GAME_H
