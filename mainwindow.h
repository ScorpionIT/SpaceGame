#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QLabel>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private:
    QProgressBar* progress;
    QPushButton* startGame;
    QPushButton* quitGame;
    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;
    QLabel* label;

signals:

public slots:
    void launchGame();

};

#endif // MAINWINDOW_H
