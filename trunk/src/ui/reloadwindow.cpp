#include "reloadwindow.h"
#include <QDebug>

ReloadWindow::ReloadWindow()
{
    this->density = SceneBuilder::NB_INSTANCE;
    this->spacing = Ground::MAP_MAX;

    QPushButton* btnRegenerate = new QPushButton("Go !");
    QLabel* density = new QLabel("density :");
    QLabel* spacing = new QLabel("spacing :");

    QSpinBox* densitySlider = new QSpinBox();
    densitySlider->setRange(0, 4000);
    densitySlider->setSingleStep(50);
    densitySlider->setValue(SceneBuilder::NB_INSTANCE);

    QSpinBox* spacingSlider = new QSpinBox();
    spacingSlider->setRange(100, 450);
    spacingSlider->setSingleStep(50);
    spacingSlider->setValue(Ground::MAP_MAX);

    QVBoxLayout* layoutRegenerate = new QVBoxLayout;
    layoutRegenerate->addWidget(density);
    layoutRegenerate->addWidget(densitySlider);
    layoutRegenerate->addWidget(spacing);
    layoutRegenerate->addWidget(spacingSlider);
    layoutRegenerate->addWidget(btnRegenerate);

    QGroupBox* groupRegenerate = new QGroupBox("Regenerate");
    groupRegenerate->setLayout(layoutRegenerate);

    // Dock layout
    QVBoxLayout* layoutDock = new QVBoxLayout;
    layoutDock->addWidget(groupRegenerate);

    this->setLayout(layoutDock);

    QObject::connect(densitySlider, SIGNAL(valueChanged(int)), this, SLOT(setDensity(int)));
    QObject::connect(spacingSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpacing(int)));
    QObject::connect(btnRegenerate, SIGNAL(clicked()), this, SLOT(reGenerate()));
}

void ReloadWindow::reGenerate()
{
    SceneBuilder::reloadGo(this->density, this->spacing);
    this->close();
}

void ReloadWindow::setDensity(int d)
{
    this->density = d;
}

void ReloadWindow::setSpacing(int s)
{
    this->spacing = s;
}

int ReloadWindow::getDensity()
{
    return this->density;
}

int ReloadWindow::getSpacing()
{
    return this->spacing;
}
