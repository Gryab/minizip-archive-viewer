#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "clickable_label.h"

#include "table_view_model.h"

QT_BEGIN_NAMESPACE
class QTableView; // forward declaration
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);

    void handlePath(const std::string &path);
public slots:
    void handleClick(void);

private:
    QTableView *m_tableView;
    std::vector<std::string> m_filesInfo;
    TableViewModel m_tableModel;
    ClickableLabel *m_label;
    void setLabel(const QString &text);
    void displayTableView(void);
    void handleListOfUrls(QList<QUrl> urls);

};

#endif // MAINWINDOW_H
