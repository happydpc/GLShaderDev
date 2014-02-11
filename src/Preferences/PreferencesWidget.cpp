/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without een the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */


#include <QMessageBox>
#include <QSplitter>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QVariant>
#include <QString>

#include "PreferencesWidget.h"
#include "Dialog/GLInfoDialog.h"
#include "Preferences/PreferenceListItemDelegate.h"
#include "Preferences/Panels/GeneralPanel.h"
#include "Preferences/Panels/ShaderExtansionsPanel.h"


PreferencesWidget::PreferencesWidget()
{
  setWindowIcon(QIcon(":/preferences-other.png"));
  setWindowTitle("Preferences");
  setModal(true);
  
  _panels.push_back(new GeneralPanel(this));
  _panels.push_back(new ShaderExtansionsPanel(this));
  
  initPreferences();

  _buttons = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Ok | QDialogButtonBox::Apply);
  connect(_buttons, SIGNAL(accepted()), this, SLOT(accept()));
  connect(_buttons, SIGNAL(rejected()), this, SLOT(cancel()));
  connect(_buttons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(apply(QAbstractButton*)));
  _buttons->button(QDialogButtonBox::Apply)->setEnabled(false);

  _listView = new QListView;
  _listView->setFixedWidth(205);
  _listView->setMinimumHeight(3 * 100);
  _listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  _panel = new QStackedWidget;
  
  QStandardItemModel*	itemModel = new QStandardItemModel(_listView);
  itemModel->appendRow(_panels.at(General)->getItem());
  itemModel->appendRow(_panels.at(ShaderExtansions)->getItem());

  _listView->setModel(itemModel);
  _listView->setItemDelegate(new PreferenceListItemDelegate(_listView));
  _listView->setAutoScroll(false);

  QWidget*	menuList = new QWidget;
  QVBoxLayout*	menuLayout = new QVBoxLayout;
  menuLayout->addWidget(_listView);
  menuLayout->setContentsMargins(5, 5, 5, 5);
  menuList->setLayout(menuLayout);

  _panel->addWidget(_panels.at(General));
  _panel->addWidget(_panels.at(ShaderExtansions));
  _panel->setCurrentIndex(0);
  QPalette pal(palette());
  _panel->setAutoFillBackground(true);
  pal.setColor(QPalette::Background, Qt::white);
  _panel->setPalette(pal);

  QGridLayout*		settingLayout = new QGridLayout;

  settingLayout->addWidget(menuList, 0, 0);
  settingLayout->addWidget(_panel, 0, 1);
  settingLayout->addWidget(_buttons, 1, 1);
  settingLayout->setColumnStretch(1, 1);

  setLayout(settingLayout);

  connect(_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onSelectionChanged(QItemSelection)));
}

PreferencesWidget::~PreferencesWidget() {}

void PreferencesWidget::enableApply()
{
  _buttons->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void PreferencesWidget::initPreferences()
{
  QSettings 		settings;
  
  //-->[START]-->GENERAL
  int 			maxRecentFiles = settings.value("maxRecentFiles").toInt();
  if (maxRecentFiles == 0)
  {
     settings.setValue("maxRecentFiles", 9);
     maxRecentFiles = 9;
  }
 _panels.at(General)->getSettings().setSetting("maxRecentFiles", new QVariant(maxRecentFiles));
 //-->[END]-->GENERAL
 
 //-->[START]-->SHADEREXTANSIONS
  QString 		vertexShaderPath(settings.value("vertexShaderPath").toString());
  if (vertexShaderPath.isEmpty())
  {
     settings.setValue("vertexShaderPath", QString("nowhere"));
     vertexShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("vertexShaderPath", new QVariant(vertexShaderPath));
 
  QString 		tesselationControlShaderPath(settings.value("tesselationControlShaderPath").toString());
  if (tesselationControlShaderPath.isEmpty())
  {
     settings.setValue("tesselationControlShaderPath", QString("nowhere"));
     tesselationControlShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("tesselationControlShaderPath", new QVariant(tesselationControlShaderPath));
 
  QString 		tesselationEvaluationShaderPath(settings.value("tesselationEvaluationShaderPath").toString());
  if (tesselationEvaluationShaderPath.isEmpty())
  {
     settings.setValue("tesselationEvaluationShaderPath", QString("nowhere"));
     tesselationEvaluationShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("tesselationEvaluationShaderPath", new QVariant(tesselationEvaluationShaderPath));
 
  QString 		geometryShaderPath(settings.value("geometryShaderPath").toString());
  if (geometryShaderPath.isEmpty())
  {
     settings.setValue("geometryShaderPath", QString("nowhere"));
     geometryShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("geometryShaderPath", new QVariant(geometryShaderPath));
 
  QString 		fragmentShaderPath(settings.value("fragmentShaderPath").toString());
  if (fragmentShaderPath.isEmpty())
  {
     settings.setValue("fragmentShaderPath", QString("nowhere"));
     fragmentShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("fragmentShaderPath", new QVariant(fragmentShaderPath));
 
  QString 		computeShaderPath(settings.value("computeShaderPath").toString());
  if (computeShaderPath.isEmpty())
  {
     settings.setValue("computeShaderPath", QString("nowhere"));
     computeShaderPath = QString("nowhere");
  }
 _panels.at(ShaderExtansions)->getSettings().setSetting("computeShaderPath", new QVariant(computeShaderPath));
 //-->[END]-->SHADEREXTANSIONS
 
 //-->ADD HERE OTHERS SETTINGS
 
 //--> INIT OF ALL SETTING FOR PREFERENCES
 for (std::vector<APreferencePanel*>::iterator it = _panels.begin();
      it != _panels.end(); ++it)
  (*it)->init();
}

void PreferencesWidget::modifyPreferences(bool condition)
{
  QSettings		settings;

  for (std::vector<APreferencePanel*>::iterator it = _panels.begin();
  it != _panels.end(); ++it)
      {
	if ((*it)->isChanged())
	{
	  for (std::map<QString, QVariant*>::const_iterator i_it = (*it)->getSettings().getList().begin();
		i_it != (*it)->getSettings().getList().end(); ++i_it)
		{
		  if (condition)
		    settings.setValue((*i_it).first, *(*i_it).second);
		  else
		    (*it)->getSettings().setSetting((*i_it).first, new QVariant(settings.value((*i_it).first)));
		}
	  (*it)->refresh();
	}
      }
}

void PreferencesWidget::onSelectionChanged(QItemSelection item)
{
  if (item.indexes().count() < 2)
    _panel->setCurrentIndex(item.indexes().first().row());
}

void PreferencesWidget::accept()
{
  modifyPreferences(true);
  _buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
  QDialog::accept();
}

void PreferencesWidget::cancel()
{
  modifyPreferences(false);
  _buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
  QDialog::reject();
}

void PreferencesWidget::apply(QAbstractButton* button)
{
  if (_buttons->standardButton(button) == QDialogButtonBox::Apply)
  {
    modifyPreferences(true);
    _buttons->button(QDialogButtonBox::Apply)->setEnabled(false);
  }
}

