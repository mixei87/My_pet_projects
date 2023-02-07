#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H

#include <QDir>
#include <QObject>

#include "DBmanager.h"
#include "model_game.h"

class GameController : public QObject {
  Q_OBJECT
 public:
  GameController(QObject* parent = nullptr);
  ~GameController();

  Q_INVOKABLE GameModel* getModel();

 private:
  GameModel* m_gameModel;
  DBmanager* m_db;
};

#endif  // CONTROLLER_GAME_H
