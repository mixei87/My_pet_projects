#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H
#include <QDir>
#include <QObject>
#include <QStandardPaths>

#include "DBmanager.h"
#include "model_game.h"
#include "settings.h"

class GameController : public QObject {
  Q_OBJECT
 public:
  GameController(QObject* parent = nullptr);
  ~GameController();

  Q_INVOKABLE GameModel* getModel();

 private:
  GameModel* m_gameModel;
  Settings m_settings;
};

#endif  // CONTROLLER_GAME_H

// CREATE TABLE IF NOT EXISTS tbl_settings (id INTEGER PRIMARY KEY
// AUTOINCREMENT, default_color TEXT, count_next_balls INTEGER, points_in_row
// INTEGER, height_field INTEGER, width_field INTEGER); INSERT INTO tbl_settings
// (id, default_color, count_next_balls, points_in_row, height_field,
// width_field) VALUES(1, "Qt::black", 3, 5, 9, 9);
