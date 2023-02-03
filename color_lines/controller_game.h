#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H
#include <QDir>
#include <QObject>
#include <QStandardPaths>

#include "DBmanager.h"
#include "model_game.h"

class GameController : public QObject {
  Q_OBJECT
 public:
  GameController(QObject* parent = nullptr);
  ~GameController();

  Q_INVOKABLE GameModel* getModel();

 private:
  GameModel m_gameModel;
};

#endif  // CONTROLLER_GAME_H
