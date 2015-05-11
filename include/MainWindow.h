/**
 * @file MainWindow.h
 * @brief Main window for the Clusterer GUI
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// External headers
#include <QMainWindow>
#include <QTimer>

// Internal headers
#include "GUINodePlotter.hpp"
#include "GUIFitnessPlot.hpp"

/**
 * @namespace Ui
 * @brief Auto-generated code from Qt goes in this namespace
 */
namespace Ui {
class MainWindow;
}


/**
* @namespace clusterer
* @brief The namespace clusterer is the main namespace of the clusterer project.
*/
namespace clusterer
{

/**
* @namespace frontend
* @brief The namespace frontend is the namespace for all frontend components of the
* project.
*/
namespace frontend
{

/**
 * @class MainWindow
 * @brief Main window for the Clusterer GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Standard constructor
     * @param parent The parent widget of the window
     */
    explicit MainWindow(QWidget *parent = 0);
    
    /**
     * @brief Standard destructor
     */
    ~MainWindow();
    
    /**
     * @brief Shows an alert popup message
     * @param title The title of the message
     * @param text The text of the message
     */
    void showAlert(const QString& title, const QString& text);

private slots:
    /**
     * @brief Updates the UI if the backend has provided new data
     */
    void updateFrontend();

    /**
     * @brief Executed when the "Start" button is clicked
     */
    void on_pushButton_clicked();

    /**
     * @brief Executed when the "Stop" button is clicked
     */
    void on_pushButton_4_clicked();

    /**
     * @brief Executed when the "Pause" button is clicked
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Executed when the "Resume" button is clicked
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Executed when the "Save Settings" menu item is clicked
     */
    void on_actionSave_Settings_2_triggered();

    /**
     * @brief Executed when the "Load Settings" menu item is clicked
     */
    void on_actionLoad_Settings_2_triggered();

    /**
     * @brief Executed when the "Save Graph" menu item is clicked
     */
    void on_actionSave_Graph_triggered();

    /**
     * @brief Executed when the "Load Graph -> Zachary Format" menu item is clicked
     */
    void on_actionZachary_format_triggered();

    /**
     * @brief Executed when the "Load Graph -> Movielens Format" menu item is clicked
     */
    void on_actionMovielens_format_triggered();

    /**
     * @brief Executed when the "Save Population" menu item is clicked
     */
    void on_actionSave_Population_triggered();

    /**
     * @brief Executed when the "Save Population" menu item is clicked
     */
    void on_actionLoad_Population_triggered();

    /**
     * @brief Executed when the "About" menu item is clicked
     */
    void on_actionAbout_2_triggered();

    /**
     * @brief Executed when the "Edit Settings" menu item is clicked
     */
    void on_actionEdit_Settings_triggered();

private:
    Ui::MainWindow *ui;
    QTimer timer;

};

}
}
#endif // MAINWINDOW_H
