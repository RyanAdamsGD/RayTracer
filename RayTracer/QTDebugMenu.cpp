#include "QTDebugMenu.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qboxlayout.h>
#include <QtGui\qcheckbox>
#include <Qt\qstring.h>
#include <QtGui\qlabel>
#include <QtGui\qslider.h>
#include <QtGui\qlabel.h>
#include <QtCore\qcoreapplication.h>
#include <QtGui\qmainwindow.h>
#include <Qt\qpushbutton.h>
QTDebugMenu QTDebugMenu::instance;

static const float SLIDER_GRANULARITY = 50.0;

#ifndef DEBUGMENU
void QTDebugMenu::Init(QWidget* m){}
void QTDebugMenu::visible(){}
void QTDebugMenu::addSlider(const char* name, float* value, float min , float max,bool ){}
void QTDebugMenu::addCheckBox(const char* name, bool* value, bool){}
void QTDebugMenu::addWatchFloat(const char* name, const float* value,bool){}
void QTDebugMenu::update(){}
#else

void QTDebugMenu::Init(QWidget* m)
{
	instance.nextCheckBox=0;
	instance.nextSlider=0;
	instance.nextWatchFloat=0;
	instance.menu=m;
	instance.menu->setLayout(instance.mainLayout = new QVBoxLayout);
	instance.menu->setMaximumHeight(250);
}

void QTDebugMenu::visible()
{
	if(!instance.menu->isHidden())
	{
		instance.menu->hide();
	}
	else
	{
		instance.menu->show();
	}
}

void QTDebugMenu::addSlider(const char* name, float* value, float min, float max, bool newLine)
{
	if(instance.nextSlider == 0 || newLine)
		instance.mainLayout->addLayout(instance.sliderLayout = new QHBoxLayout);

	QVBoxLayout* layout;
	instance.sliderLayout->addLayout(layout = new QVBoxLayout);
	QLabel* label;
	layout->addWidget(label = new QLabel(name));
	label->setAlignment(Qt::AlignCenter);
	Slider& where = instance.sliders[instance.nextSlider++];
	layout->addWidget(where.slide = new QSlider(instance.menu));
	layout->addWidget(where.label = new QLabel);
	where.label->setMinimumWidth(35);
	where.label->setAlignment(Qt::AlignCenter);
	where.slide->setOrientation(Qt::Horizontal);
	where.slide->setMinimum(min * SLIDER_GRANULARITY);
	where.slide->setMaximum(max * SLIDER_GRANULARITY);
	where.slide->setValue(*value * SLIDER_GRANULARITY);
	where.value = value;
}

void QTDebugMenu::addCheckBox(const char* name, bool* value, bool newLine)
{
	if(instance.nextCheckBox == 0 || newLine)
		instance.mainLayout->addLayout(instance.checkBoxLayout = new QHBoxLayout);

	QVBoxLayout* layout;
	instance.checkBoxLayout->addLayout(layout = new QVBoxLayout);
	QLabel* label;
	layout->addWidget(label = new QLabel(name));
	CheckBox& where = instance.checkBoxes[instance.nextCheckBox++];
	layout->addWidget(where.checkbox = new QCheckBox);
	where.value = value;
	where.checkbox->setChecked(*value);
}

void QTDebugMenu::addWatchFloat(const char* name, const float* value, bool newLine)
{
	if(instance.nextWatchFloat == 0 || newLine)
		instance.mainLayout->addLayout(instance.watchFloatLayout = new QHBoxLayout);

	QHBoxLayout* layout;
	instance.watchFloatLayout->addLayout(layout = new QHBoxLayout);
	QLabel* label;
	layout->addWidget(label = new QLabel(name));
	label->setAlignment(Qt::AlignRight);
	WatchFloat& where = instance.WFloats[instance.nextWatchFloat++];
	layout->addWidget(where.text = new QLabel);
	where.text->setAlignment(Qt::AlignLeft);
	where.value = value;
}

void QTDebugMenu::addButton(const char* text, basicEvent func, bool newLine)
{
	if(instance.nextButton == 0 || newLine)
		instance.mainLayout->addLayout(instance.buttonLayout = new QHBoxLayout);

	QVBoxLayout* layout;
	instance.buttonLayout->addLayout(layout = new QVBoxLayout);
	Button& where = instance.buttons[instance.nextButton++];
	layout->addWidget(where.button = new QPushButton);
	where.button->setText(text);
	where.func = func;
	where.wasDown = false;
}


void QTDebugMenu::update()
{
	for(uint i=0;i<instance.nextSlider;i++)
	{
		Slider& where = instance.sliders[i];
		*where.value = where.slide->value() / SLIDER_GRANULARITY;
		QString temp;
		temp.setNum(*where.value);
		where.label->setText(temp);
	}

	for(uint i=0;i<instance.nextCheckBox;i++)
	{
		CheckBox& where = instance.checkBoxes[i];
		*where.value = where.checkbox->isChecked();
	}

	for(uint i=0;i<instance.nextWatchFloat;i++)
	{
		WatchFloat& where = instance.WFloats[i];
		QString temp;
		temp.setNum(*where.value);
		where.text->setText(temp);
	}

	for(uint i=0;i<instance.nextButton;i++)
	{
		Button& where = instance.buttons[i];
		if(where.button->isDown())
		{
			where.wasDown = true;
		}
		else if(where.wasDown)
		{
			where.wasDown = false;
			where.func();
		}
	}
}

#endif