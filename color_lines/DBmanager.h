#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class DBmanager {
 public:
  DBmanager(const QString &path);
  ~DBmanager();

 private:
  typedef struct _table_settings {
    QString id = "id";
    QString default_color = "default_color";
    QString count_next_balls = "count_next_balls";
    QString points_in_row = "points_in_row";
    QString default_height_field = "default_height_field";
    QString default_width_field = "default_width_field";
  } _table_settings;

  typedef struct _table_and_columns {
    _table_settings table_settings;
  } _table_and_columns;

  QSqlDatabase m_db;
  QString m_tableNameSettings = "tbl_settings";
  _table_and_columns *m_tables;
};

#endif  // DBMANAGER_H
