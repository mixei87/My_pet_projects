#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QColor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include "settings.h"

class DBmanager {
 public:
  DBmanager(const QString &path);
  ~DBmanager();

  Settings &getSettings();
  bool updateGameboardTable();

 private:
  typedef struct _table_settings {
    QString id = "id";
    QString default_color = "default_color";
    QString count_next_balls = "count_next_balls";
    QString points_in_row = "points_in_row";
    QString height_field = "height_field";
    QString width_field = "width_field";
    QString game_is_started = "game_is_started";
  } _table_settings;

  typedef struct _table_gameboard {
    QString id = "id";
    QString index = "index_field";
    QString color = "color";
  } _table_gameboard;

  typedef struct _table_and_columns {
    _table_settings table_settings;
    _table_gameboard table_gameboard;
  } _table_and_columns;

  bool createSettingsTable();
  bool isTableNotExist(const QString &table);
  bool insertSettingsTable();
  //  bool changeSettings(const QString &);

  bool createGameboardTable();
  bool insertGameboardTable();

  QSqlDatabase m_db;
  _table_and_columns *m_tables;
  QString m_table_name_settings = "tbl_settings";
  QString m_table_name_gameboard = "tbl_gameboard";
  Settings m_settings;
};

#endif  // DBMANAGER_H
