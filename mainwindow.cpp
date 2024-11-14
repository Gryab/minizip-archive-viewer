#include "mainwindow.h"
#include "clickable_label.h"

#include <QTableView>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>
 #include <QFileDialog>
#include <string>

int32_t minizip_list(const std::string &path, std::vector<std::string> &filesInfo);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_tableModel.setFilesInfo(&m_filesInfo);

    setWindowTitle(QString("hmmmmm"));
    resize(800, 600);

    setLabel("Drag and drop a zip archive");

    setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    handleListOfUrls(e->mimeData()->urls());
}

void MainWindow::handlePath(const std::string &path)
{
    minizip_list(path, m_filesInfo);
    displayTableView();
}

void MainWindow::handleListOfUrls(QList<QUrl> urls)
{
    foreach (const QUrl &url, urls) {
        if(url.fileName().endsWith(".zip"))
        {
            handlePath(url.path().toStdString());
            return;
        }
    }
    setLabel("try other file");
}

void MainWindow::handleClick(void)
{
    QList<QUrl> urls = QFileDialog::getOpenFileUrls();
    handleListOfUrls(urls);
}

void MainWindow::setLabel(const QString& text)
{
    m_label = new ClickableLabel(this);
    m_label->setText(text);
    m_label->setAlignment(Qt::AlignCenter);
    connect(m_label, SIGNAL(clicked()), this, SLOT(handleClick()));
    setCentralWidget(m_label);
}

void MainWindow::displayTableView(void)
{
    m_tableView = new QTableView(this);
    m_tableView->setModel(&m_tableModel);
    m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    setCentralWidget(m_tableView);
    m_tableModel.update();
}
