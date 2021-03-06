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

#ifndef _DEVICEINFO_H_
#define _DEVICEINFO_H_

#include <QString>
#include <QVariant>
#include <QList>

class DeviceData {

public:
	DeviceData() {};
	DeviceData(QVariant ID, QString desc) { _id = ID; _desc = desc; };
	~DeviceData() {};

	void setID(QVariant ID) { _id = ID; };
	void setDesc(QString desc) { _desc = desc; };

	QVariant ID() { return _id; };
	QString desc() { return _desc; };

private:
	QVariant _id;
	QString _desc;
};


typedef QList<DeviceData> DeviceList;


class DeviceInfo {

public:
	static DeviceList alsaDevices();
	static DeviceList xvAdaptors();
};

#endif

