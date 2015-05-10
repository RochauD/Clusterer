/**
* @file GeneticGui.cpp
* @brief
*/

// External headers
#include <QLabel>
#include <QDockWidget>
#include <QPushButton>
// Own headers
#include "../include/GeneticGui.hpp"


namespace clusterer
{
namespace frontend
{



void GeneticGui::startGui()
{
  window.show();
}

GeneticGui::GeneticGui()
{
  // Set up the main window
  menuBar = new ClustererMenuBar();

  // Instantiate the buttons.
  menuBar->addWidget(new QPushButton("&Read Graph"));
  menuBar->addWidget(new QPushButton("&Settings"));
  menuBar->addWidget(new QPushButton("&Run Algorithm"));
  menuBar->addWidget(new QPushButton("&Quit"));

  window.setMenuWidget(menuBar);

  // Blank items for the drawing widgets
  QDockWidget* fitnessGraph = new QDockWidget("Fitness Graph");
  QLabel* visualization = new QLabel("visualization");
  visualization->setMargin(300);

  window.addDockWidget(Qt::LeftDockWidgetArea, fitnessGraph);
  window.setCentralWidget(visualization);
}

}
}
