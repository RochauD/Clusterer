/**
 * @file SettingsDialog.h
 * @brief The custom dialog for modifying the settings of the project
 */
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

// External headers
#include <QDialog>

/**
 * @namespace Ui
 * @brief Auto-generated code from Qt goes in this namespace
 */
namespace Ui {
class SettingsDialog;
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
 * @class SettingsDialog
 * @brief The custom dialog for modifying the settings of the project
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Standard Constructor. Instantiates the dialog and sets its title
     * @param parent The parent widget of the dialog
     */
    explicit SettingsDialog(QWidget *parent = 0);
   
    /**
     * @brief Standard destructor
     */
    ~SettingsDialog();

private slots:
    /**
     * @brief Invoked when the "Okay" button is clicked
     */
    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *ui;
};

}
}

#endif // SETTINGSDIALOG_H
