#include "DBmanager.h"

DBmanager::DBmanager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);
  m_tables = new _table_and_columns;
  if (!m_db.open()) qDebug() << "Error: fail connection with database";
  if (isTableNotExist(m_table_name_settings)) {
    if (createSettingsTable()) insertSettingsTable();
  }
  if (isTableNotExist(m_table_name_gameboard)) {
    if (createGameboardTable()) {
      insertGameboardTable();
    }
  }
}

DBmanager::~DBmanager() {
  delete m_tables;
  if (m_db.isOpen()) {
    m_db.close();
  }
}

bool DBmanager::createSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString(
          "CREATE TABLE '%1' (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT,"
          "%4 INTEGER, %5 INTEGER, %6 INTEGER, %7 INTEGER, %8 BOOL, %9 "
          "INTEGER, %10 INTEGER, %11 INTEGER);")
          .arg(m_table_name_settings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field,
               m_tables->table_settings.game_is_started,
               m_tables->table_settings.record,
               m_tables->table_settings.points_to_1_ball,
               m_tables->table_settings.current_score));
  if (!query.exec()) return false;
  return true;
}

bool DBmanager::isTableNotExist(const QString &table) {
  QSqlQuery query;
  query.prepare(QString("SELECT name FROM sqlite_schema WHERE type = 'table' "
                        "AND name = '%1';")
                    .arg(table));
  query.exec();
  if (query.next()) return false;
  return true;
}

bool DBmanager::insertSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8, %9, %10, %11) "
              "VALUES(:id, "
              ":default_color, :count_next_balls, :points_in_row, "
              ":height_field, :width_field, :game_is_started, :record, "
              ":points_to_1_ball, :current_score);")
          .arg(m_table_name_settings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field,
               m_tables->table_settings.game_is_started,
               m_tables->table_settings.record,
               m_tables->table_settings.points_to_1_ball,
               m_tables->table_settings.current_score));

  query.bindValue(":id", 1);
  query.bindValue(":default_color", Settings::getSettings().default_color());
  query.bindValue(":count_next_balls",
                  Settings::getSettings().count_next_balls());
  query.bindValue(":points_in_row", Settings::getSettings().points_in_row());
  query.bindValue(":height_field", Settings::getSettings().height_field());
  query.bindValue(":width_field", Settings::getSettings().width_field());
  query.bindValue(":game_is_started",
                  Settings::getSettings().game_is_started());
  query.bindValue(":record", Settings::getSettings().record());
  query.bindValue(":points_to_1_ball",
                  Settings::getSettings().points_to_1_ball());
  query.bindValue(":current_score", Settings::getSettings().current_score());
  if (!query.exec()) return false;
  return true;
}

bool DBmanager::updateSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("UPDATE %1 SET %3 = :default_color, %4 = "
              ":count_next_balls, %5 = :points_in_row, %6 = :height_field, "
              "%7 =:width_field, %8 = :game_is_started, %9 = :record, "
              "%10 = :points_to_1_ball, %11 = :current_score "
              "WHERE %2= :id;")
          .arg(m_table_name_settings, m_tables->table_settings.id,
               m_tables->table_settings.default_color,
               m_tables->table_settings.count_next_balls,
               m_tables->table_settings.points_in_row,
               m_tables->table_settings.height_field,
               m_tables->table_settings.width_field,
               m_tables->table_settings.game_is_started,
               m_tables->table_settings.record,
               m_tables->table_settings.points_to_1_ball,
               m_tables->table_settings.current_score));

  query.bindValue(":id", 1);
  query.bindValue(":default_color", Settings::getSettings().default_color());
  query.bindValue(":count_next_balls",
                  Settings::getSettings().count_next_balls());
  query.bindValue(":points_in_row", Settings::getSettings().points_in_row());
  query.bindValue(":height_field", Settings::getSettings().height_field());
  query.bindValue(":width_field", Settings::getSettings().width_field());
  query.bindValue(":game_is_started",
                  Settings::getSettings().game_is_started());
  query.bindValue(":record", Settings::getSettings().record());
  query.bindValue(":points_to_1_ball",
                  Settings::getSettings().points_to_1_ball());
  query.bindValue(":current_score", Settings::getSettings().current_score());
  if (!query.exec()) return false;
  return true;
}

void DBmanager::selectSettingsTable() {
  QSqlQuery query;
  query.prepare(
      QString("SELECT * FROM %1 WHERE id = 1;").arg(m_table_name_settings));
  if (!query.exec() || !query.next()) {
    return;
  }
  QSqlRecord rec = query.record();
  int name_default_color = rec.indexOf(m_tables->table_settings.default_color);
  int name_count_next_balls =
      rec.indexOf(m_tables->table_settings.count_next_balls);
  int name_points_in_row = rec.indexOf(m_tables->table_settings.points_in_row);
  int name_height_field = rec.indexOf(m_tables->table_settings.height_field);
  int name_width_field = rec.indexOf(m_tables->table_settings.width_field);
  int name_game_is_started =
      rec.indexOf(m_tables->table_settings.game_is_started);
  int name_record = rec.indexOf(m_tables->table_settings.record);
  int name_points_to_1_ball =
      rec.indexOf(m_tables->table_settings.points_to_1_ball);
  int name_current_score = rec.indexOf(m_tables->table_settings.current_score);

  Settings::getSettings().setDefault_color(
      query.value(name_default_color).value<QColor>());
  Settings::getSettings().setCount_next_balls(
      query.value(name_count_next_balls).toInt());
  Settings::getSettings().setPoints_in_row(
      query.value(name_points_in_row).toInt());
  Settings::getSettings().setHeight_field(
      query.value(name_height_field).toInt());
  Settings::getSettings().setWidth_field(query.value(name_width_field).toInt());
  Settings::getSettings().setGame_is_started(
      query.value(name_game_is_started).toBool());
  Settings::getSettings().setRecordGame(query.value(name_record).toInt());
  Settings::getSettings().setPoints_to_1_ball(
      query.value(name_points_to_1_ball).toInt());
  Settings::getSettings().setCurrent_score(
      query.value(name_current_score).toInt());
}

bool DBmanager::createGameboardTable() {
  QSqlQuery query;
  query.prepare(
      QString(
          "CREATE TABLE '%1' (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER,"
          "%4 TEXT);")
          .arg(m_table_name_gameboard, m_tables->table_gameboard.id,
               m_tables->table_gameboard.index,
               m_tables->table_gameboard.color));
  if (!query.exec()) return false;
  return true;
}

bool DBmanager::insertGameboardTable() {
  QVariantList id;
  QVariantList index;
  QVariantList color;
  for (size_t i = 0; i < Settings::getSettings().field().size(); ++i) {
    id << static_cast<int>(i + 1);
    index << static_cast<int>(i);
    color << Settings::getSettings().default_color();
  }

  QSqlQuery query;
  query.prepare(QString("INSERT INTO %1 (%2, %3, %4) VALUES(:id, "
                        ":index, :color);")
                    .arg(m_table_name_gameboard, m_tables->table_gameboard.id,
                         m_tables->table_gameboard.index,
                         m_tables->table_gameboard.color));
  query.addBindValue(id);
  query.addBindValue(index);
  query.addBindValue(color);

  if (!query.execBatch()) return false;
  return true;
}

void DBmanager::selectGameBoardTable() {
  QSqlQuery query;
  query.prepare(QString("SELECT * FROM %1;").arg(m_table_name_gameboard));
  if (!query.exec()) return;

  QSqlRecord rec = query.record();
  int name_index = rec.indexOf(m_tables->table_gameboard.index);
  int name_color = rec.indexOf(m_tables->table_gameboard.color);
  while (query.next()) {
    Settings::getSettings().setField(query.value(name_index).toInt(),
                                     query.value(name_color).value<QColor>());
  }
}

bool DBmanager::updateGameboardTable() {
  bool isUpdate = true && Settings::getSettings().field().size();

  for (size_t index = 0; index < Settings::getSettings().field().size();
       ++index) {
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET %2 = :color WHERE %3 = :index;")
                      .arg(m_table_name_gameboard,
                           m_tables->table_gameboard.color,
                           m_tables->table_gameboard.index));
    query.bindValue(":index", static_cast<int>(index));
    query.bindValue(":color", Settings::getSettings().field()[index]);
    if (!query.exec()) isUpdate = false;
  }
  return isUpdate;
}
