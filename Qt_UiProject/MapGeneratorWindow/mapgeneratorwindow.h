#ifndef MAPGENERATORWINDOW_H
#define MAPGENERATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class MapGeneratorWindow;
}

class MapGeneratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapGeneratorWindow(QWidget *parent = 0);
    ~MapGeneratorWindow();

private:
    Ui::MapGeneratorWindow *ui;
};

#endif // MAPGENERATORWINDOW_H
