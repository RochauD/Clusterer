/**
 * @file ClustererMenuBar.cpp
 * @brief The Menu bar for the Clusterer GUI
 */

// standard headers

// Exeternal Headers

// Own headers
#include "../include/ClustererMenuBar.hpp"

namespace clusterer
{
namespace frontend
{

ClustererMenuBar::ClustererMenuBar()
{
  layout = new QHBoxLayout();
  this->setLayout(layout);
}

void ClustererMenuBar::addWidget(QWidget* widget)
{
  layout->addWidget(widget);
}

}
}