#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showAlert(const QString&, const QString&);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionSave_Settings_2_triggered();

    void on_actionLoad_Settings_2_triggered();

    void on_actionSave_Graph_triggered();

    void on_actionZachary_format_triggered();

    void on_actionMovielens_format_triggered();

    void on_actionSave_Population_triggered();

    void on_actionLoad_Population_triggered();

    void on_actionAbout_2_triggered();

    void on_actionEdit_Settings_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
