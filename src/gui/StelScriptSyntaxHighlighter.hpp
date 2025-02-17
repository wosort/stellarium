/*
 * Stellarium
 * Copyright (C) 2009 Matthew Gates
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef STELSCRIPTSYNTAXHIGHLIGHTER_HPP
#define STELSCRIPTSYNTAXHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QHash>
#include <QSet>
#include <QString>
#include <QTextCharFormat>
#include <QRegularExpression>

class QTextDocument;

//! This class is used to colorize the ECMAScript syntax elements in the Scripting Console.
//! It marks keywords, function names, literals, etc.
//! All StelModules and public slots from StelModules are colorized.
//! Single non-module objects registered with the StelScriprMgr are not highlighted, but their methods are.
class StelScriptSyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	StelScriptSyntaxHighlighter(QTextDocument*  parent=Q_NULLPTR);
	void setFormats(void);

protected:
	virtual void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
	void locateFunctions( const QMetaObject* metaObject, QString scriptName );
	struct HighlightingRule
	{
		QRegularExpression pattern;
		QTextCharFormat* format;
	};
	QVector<HighlightingRule> highlightingRules;
	
	QHash<QString,QSet<QString>> mod2funcs;
	QString lastModule;

	QTextCharFormat keywordFormat;
	QTextCharFormat literalFormat;
	QTextCharFormat predefFormat;
	QTextCharFormat moduleFormat;
	QTextCharFormat methodFormat;
	QTextCharFormat commentFormat;
	QTextCharFormat functionFormat;
	QTextCharFormat noMethFormat;

	static const QStringList keywords;
	static const QStringList predefineds;
};

#endif // STELSCRIPTSYNTAXHIGHLIGHTER_HPP

