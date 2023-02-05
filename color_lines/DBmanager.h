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

 private:
  typedef struct _table_settings {
    QString id = "id";
    QString default_color = "default_color";
    QString count_next_balls = "count_next_balls";
    QString points_in_row = "points_in_row";
    QString height_field = "height_field";
    QString width_field = "width_field";
  } _table_settings;

  typedef struct _table_and_columns {
    _table_settings table_settings;
  } _table_and_columns;

  bool createSettingsTable();

  //  bool changeSettings(const QString &);

  QSqlDatabase m_db;
  _table_and_columns *m_tables;
  QString m_tableNameSettings = "tbl_settings";
  Settings m_settings;
};

#endif  // DBMANAGER_H
