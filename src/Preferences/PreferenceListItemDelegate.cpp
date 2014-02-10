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

#include "PreferenceListItemDelegate.h"

PreferenceListItemDelegate::PreferenceListItemDelegate(QObject* parent)
: QStyledItemDelegate(parent)
{}

PreferenceListItemDelegate::~PreferenceListItemDelegate() {}

void PreferenceListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  painter->save();

  QRect r;
  if (option.state & QStyle::State_Selected)
    painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));

  QString title = index.data(Qt::DisplayRole).toString();
  QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));

  QFont    font = painter->font();
  font.setBold(true);
  painter->setFont(font);

  r = option.rect.adjusted((200 - painter->fontMetrics().width(title)) / 2, 0, 0, -10);
  painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, title, &r);

  QSize iconsize = icon.actualSize(option.decorationSize);
  r = option.rect.adjusted((200 - iconsize.width()) / 2, (37 - iconsize.height()) / 2, 0, 0);
  painter->drawPixmap(QPoint(r.left(),r.top()),icon.pixmap(iconsize.width(),iconsize.height()));
  painter->restore();
}

QSize PreferenceListItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  static_cast<void>(option);
  static_cast<void>(index);

  return QSize(200, 75);
}