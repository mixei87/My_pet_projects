#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractItemModel>
#include <QColor>
#include <algorithm>
//#include <chrono>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class GameBoard : public QAbstractItemModel {
  Q_OBJECT
 public:
  enum ModelRoles { selectedBall_ = Qt::UserRole + 1 };

  GameBoard(const int height_field = default_height_field,
            const int width_field = default_width_field,
            QObject* parent = nullptr);

  int height_field() const;
  int width_field() const;
  Q_INVOKABLE bool swapPoints(int index);
  Q_INVOKABLE bool addRandomPoints();
  Q_INVOKABLE bool setCurrentIndex(int newCurrentIndex);
  Q_INVOKABLE int getCurrentIndex();

 signals:
  void currentIndexChanged();

 private:
  bool move(int index);
  static const int default_height_field{9};
  static const int default_width_field{9};
  const QColor default_color{Qt::black};

  const int m_height_field;
  const int m_width_field;
  const int m_boardSize;
  std::vector<QColor> m_field;
  int m_currentIndex;
  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& child) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  const int m_count_next_balls = 3;
  const int m_points_in_row = 5;

  unordered_map<int, QColor> m_colors{{0, QColorConstants::Svg::deeppink},
                                      {1, QColorConstants::Svg::mediumseagreen},
                                      {2, QColorConstants::Svg::cornflowerblue},
                                      {3, QColorConstants::Svg::gold}};

  unordered_set<int> m_field_free;
  unordered_set<int> m_field_busy;
  unordered_set<int> m_field_for_free;

  vector<int> m_seq_free_points;
  vector<int> m_seq_busy_points;

  Q_PROPERTY(int height_field READ height_field CONSTANT)
  Q_PROPERTY(int width_field READ width_field CONSTANT)

  void clearBingoRows();

  int setIndexFromCoord(const int& i, const int& j);

  void checkLine(int i, int j, const int& d_i, const int& d_j,
                 int& points_in_line);

  bool checkLines();

  void getRandomPoints(const unordered_set<int>& field, vector<int>& seq_points,
                       const int& count_points);
};

#endif  // GAMEBOARD_H
