/*  smplayer, GUI front-end for mplayer.
    Copyright (C) 2006-2015 Ricardo Villalba <rvm@users.sourceforge.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "filesettings.h"
#include "mediasettings.h"
#include <QSettings>
#include <QFileInfo>

FileSettings::FileSettings(QString directory)
{
    output_directory = directory;
    my_settings = new QSettings(directory + "/kylin_video_files.ini", QSettings::IniFormat);
}

FileSettings::~FileSettings() {
	delete my_settings;
}

QString FileSettings::filenameToGroupname(const QString & filename) {
	QString s = filename;
	s = s.replace('/', '_');
	s = s.replace('\\', '_');
	s = s.replace(':', '_');
	s = s.replace('.', '_');
	s = s.replace(' ', '_');

	QFileInfo fi(filename);
	if (fi.exists()) {
		s += "_" + QString::number( fi.size() );
	}

	return s;	
}

bool FileSettings::existSettingsFor(QString filename) {
//	qDebug("FileSettings::existSettingsFor: '%s'", filename.toUtf8().constData());

	QString group_name = filenameToGroupname(filename);

//	qDebug("FileSettings::existSettingsFor: group_name: '%s'", group_name.toUtf8().constData());

	my_settings->beginGroup( group_name );
	bool saved = my_settings->value("saved", false).toBool();
	my_settings->endGroup();

	return saved;
}

void FileSettings::loadSettingsFor(QString filename, MediaSettings & mset, int player) {
//	qDebug("FileSettings::loadSettingsFor: '%s'", filename.toUtf8().constData());

	QString group_name = filenameToGroupname(filename);

//	qDebug("FileSettings::loadSettingsFor: group_name: '%s'", group_name.toUtf8().constData());

	mset.reset();

	my_settings->beginGroup( group_name );
	mset.load(my_settings, player);
	my_settings->endGroup();
}

void FileSettings::saveSettingsFor(QString filename, MediaSettings & mset, int player) {
//	qDebug("FileSettings::saveSettingsFor: '%s'", filename.toUtf8().constData());

	QString group_name = filenameToGroupname(filename);

//	qDebug("FileSettings::saveSettingsFor: group_name: '%s'", group_name.toUtf8().constData());

	my_settings->beginGroup( group_name );
	my_settings->setValue("saved", true);
	mset.save(my_settings, player);
	my_settings->endGroup();
}

