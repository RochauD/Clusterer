/**
 * @file ClustererMenuBar.hpp
 * @brief The Menu bar for the Clusterer GUI
 */

#ifndef CLUSTERER_FRONTEND_CLUSTERER_MENU_BAR_HPP
#define CLUSTERER_FRONTEND_CLUSTERER_MENU_BAR_HPP

// standart headers
//own headers

// Exeternal Headers
#include <QWidget>
#include <QHboxLayout>

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
 * @class ClustererMenuBar
 * @brief The Menu bar for the Clusterer GUI
 */
class ClustererMenuBar : public QWidget
{
public:
  /**
   * @brief Standart constructor that sets up the widget
   */
   ClustererMenuBar();

  /**
   * @brief Adds a widget to the layout of the menu bar
   * @arg bttns The widget to be added
   */
   void addWidget(QWidget* widget);
private:
    /**
     * @brief The underlying layout of the menu bar
     */
    QHBoxLayout* layout;
};

}
}

#endif