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

#ifndef SHADERPROJECT_H
#define SHADERPROJECT_H

#include <map>

#include <QString>
#include <QStringList>

#include "IInputItemManager.h"
#include "IStagesManager.h"

class ShaderProject : public IInputItemManager, public IStagesManager
{
  static const QString	ShaderProjectExtension;
  static const QString	StageSeparator;
public:
  explicit ShaderProject(); // NOTE may throw ProjectException
  ShaderProject(const QString& fileName); // NOTE may throw ProjectException
  ~ShaderProject();

public:
  const QString&	getName() const;
  const QString&	getProjectFile() const;

  InputItems&		getInputItems(); // inherited from IInputItemManager
  const Stages&		getStages() const; // inherited from IStagesManager
  void			addShaderObject(ShaderObject::ShaderType type, const QString& filename); // inherited from IStagesManager
  void			delShaderObject(ShaderObject::ShaderType type); // inherited from IStagesManager

  void			close();// NOTE may throw ProjectException

private:
  void	save();// NOTE may throw ProjectException
  void	load(const QStringList& stages);// NOTE may throw ProjectException

private:
  QString	_file;
  QString	_name;
  Stages	_shaderObjects;

  InputItems	_inputItems;
};

#endif // SHADERPROJECT_H
