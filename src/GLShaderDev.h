/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef GLSHADERDEV_H
#define GLSHADERDEV_H

#include <QMainWindow>
#include "GL/GLInfo.h"
#include "Preferences/PreferencesWidget.h"

class GLInfoDialog;
class ShaderVisualizationOptions;
class ShaderStagesView;
class OpenGLWidget;
class NewFileDialog;
class BuildOutput;
class CodeEditor;

class GLShaderDev : public QMainWindow
{
  Q_OBJECT
public:
  GLShaderDev();
  ~GLShaderDev();

private:
  void	initializeContext();
  void	initializeActions();
  void	initializeDockWidgets();

  void	updateRecentFiles();
  void	addRecentFile(const QString& filename);
  void	openFile(const QString& filename);

public slots:
  void	closeEvent(QCloseEvent* event);

  void	newProject();
  void	openProject();
  void	clearProjectRecent();
  void	closeProject();

  void	newFile();
  void	openFileDialog();
  void	openRecentFile();
  void	clearFileRecent();
  void	saveFileAs();

  void	buildCurrentProject();

  void	initGLInfo();
  void	showGLInfo();
  
  void 	showPreferences();

  void	about();

private:
  enum { MaxRecentFiles = 9 };

private:
  CodeEditor*		_editor;
  BuildOutput*		_output;
  QDockWidget*		_buildOutputDock;
  OpenGLWidget*		_glview;
  GLInfoDialog*		_glInfoDialog;
  ShaderStagesView*	_shaderStages;
  ShaderVisualizationOptions*	_shaderVis;
  NewFileDialog*	_newFileDialog;
  QAction*		_recentFileActions[MaxRecentFiles + 2];
  GLInfo		_glInfo;
  PreferencesWidget	_preferencesWidget;
};

#endif // GLSHADERDEV_H
